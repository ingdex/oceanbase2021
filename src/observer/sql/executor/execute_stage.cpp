/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Longda on 2021/4/13.
//

#include <string>
#include <sstream>
#include <unordered_map>

#include "execute_stage.h"

#include "common/io/io.h"
#include "common/log/log.h"
#include "common/seda/timer_stage.h"
#include "common/lang/string.h"
#include "session/session.h"
#include "event/storage_event.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "event/execution_plan_event.h"
#include "sql/executor/execution_node.h"
#include "sql/executor/tuple.h"
#include "storage/common/table.h"
#include "storage/default/default_handler.h"
#include "storage/common/condition_filter.h"
#include "storage/trx/trx.h"

using namespace common;

RC create_selection_executor(Trx *trx, const Selects &selects, const char *db, const char *table_name, SelectExeNode &select_node);
RC create_join_selection_executor(Trx *trx, const Selects &selects, const char *db, std::vector<TupleSet> *tuple_sets, std::unordered_map<std::string,int> *table_map, JoinSelectExeNode &join_select_node);
//! Constructor
ExecuteStage::ExecuteStage(const char *tag) : Stage(tag) {}

//! Destructor
ExecuteStage::~ExecuteStage() {}

//! Parse properties, instantiate a stage object
Stage *ExecuteStage::make_stage(const std::string &tag) {
  ExecuteStage *stage = new (std::nothrow) ExecuteStage(tag.c_str());
  if (stage == nullptr) {
    LOG_ERROR("new ExecuteStage failed");
    return nullptr;
  }
  stage->set_properties();
  return stage;
}

//! Set properties for this object set in stage specific properties
bool ExecuteStage::set_properties() {
  //  std::string stageNameStr(stageName);
  //  std::map<std::string, std::string> section = theGlobalProperties()->get(
  //    stageNameStr);
  //
  //  std::map<std::string, std::string>::iterator it;
  //
  //  std::string key;

  return true;
}

//! Initialize stage params and validate outputs
bool ExecuteStage::initialize() {
  LOG_TRACE("Enter");

  std::list<Stage *>::iterator stgp = next_stage_list_.begin();
  default_storage_stage_ = *(stgp++);
  mem_storage_stage_ = *(stgp++);

  LOG_TRACE("Exit");
  return true;
}

//! Cleanup after disconnection
void ExecuteStage::cleanup() {
  LOG_TRACE("Enter");

  LOG_TRACE("Exit");
}

void ExecuteStage::handle_event(StageEvent *event) {
  LOG_TRACE("Enter\n");

  handle_request(event);

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::callback_event(StageEvent *event, CallbackContext *context) {
  LOG_TRACE("Enter\n");

  // here finish read all data from disk or network, but do nothing here.
  ExecutionPlanEvent *exe_event = static_cast<ExecutionPlanEvent *>(event);
  SQLStageEvent *sql_event = exe_event->sql_event();
  sql_event->done_immediate();

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::handle_request(common::StageEvent *event) {
  ExecutionPlanEvent *exe_event = static_cast<ExecutionPlanEvent *>(event);
  SessionEvent *session_event = exe_event->sql_event()->session_event();
  Query *sql = exe_event->sqls();
  const char *current_db = session_event->get_client()->session->get_current_db().c_str();

  CompletionCallback *cb = new (std::nothrow) CompletionCallback(this, nullptr);
  if (cb == nullptr) {
    LOG_ERROR("Failed to new callback for ExecutionPlanEvent");
    exe_event->done_immediate();
    return;
  }
  exe_event->push_callback(cb);

  switch (sql->flag) {
    case SCF_SELECT: { // select
      do_select(current_db, sql, exe_event->sql_event()->session_event());
      exe_event->done_immediate();
    }
    break;

    case SCF_INSERT:
    case SCF_UPDATE:
    case SCF_DELETE:
    case SCF_CREATE_TABLE:
    case SCF_SHOW_TABLES:
    case SCF_DESC_TABLE:
    case SCF_DROP_TABLE:
    case SCF_CREATE_INDEX:
    case SCF_DROP_INDEX: 
    case SCF_LOAD_DATA: {
      StorageEvent *storage_event = new (std::nothrow) StorageEvent(exe_event);
      if (storage_event == nullptr) {
        LOG_ERROR("Failed to new StorageEvent");
        event->done_immediate();
        return;
      }

      default_storage_stage_->handle_event(storage_event);
    }
    break;
    case SCF_SYNC: {
      RC rc = DefaultHandler::get_default().sync();
      session_event->set_response(strrc(rc));
      exe_event->done_immediate();
    }
    break;
    case SCF_BEGIN: {
      session_event->get_client()->session->set_trx_multi_operation_mode(true);
      session_event->set_response(strrc(RC::SUCCESS));
      exe_event->done_immediate();
    }
    break;
    case SCF_COMMIT: {
      Trx *trx = session_event->get_client()->session->current_trx();
      RC rc = trx->commit();
      session_event->get_client()->session->set_trx_multi_operation_mode(false);
      session_event->set_response(strrc(rc));
      exe_event->done_immediate();
    }
    break;
    case SCF_ROLLBACK: {
      Trx *trx = session_event->get_client()->session->current_trx();
      RC rc = trx->rollback();
      session_event->get_client()->session->set_trx_multi_operation_mode(false);
      session_event->set_response(strrc(rc));
      exe_event->done_immediate();
    }
    break;
    case SCF_HELP: {
      const char *response = "show tables;\n"
          "desc `table name`;\n"
          "create table `table name` (`column name` `column type`, ...);\n"
          "create index `index name` on `table` (`column`);\n"
          "insert into `table` values(`value1`,`value2`);\n"
          "update `table` set column=value [where `column`=`value`];\n"
          "delete from `table` [where `column`=`value`];\n"
          "select [ * | `columns` ] from `table`;\n";
      session_event->set_response(response);
      exe_event->done_immediate();
    }
    break;
    case SCF_EXIT: {
      // do nothing
      const char *response = "Unsupported\n";
      session_event->set_response(response);
      exe_event->done_immediate();
    }
    break;
    default: {
      exe_event->done_immediate();
      LOG_ERROR("Unsupported command=%d\n", sql->flag);
    }
  }
}

void end_trx_if_need(Session *session, Trx *trx, bool all_right) {
  if (!session->is_trx_multi_operation_mode()) {
    if (all_right) {
      trx->commit();
    } else {
      trx->rollback();
    }
  }
}

// 这里没有对输入的某些信息做合法性校验，比如查询的列名、where条件中的列名等，没有做必要的合法性校验
// 需要补充上这一部分. 校验部分也可以放在resolve，不过跟execution放一起也没有关系
RC ExecuteStage::do_select2(const char *db, Query *sql, SessionEvent *session_event) {

  RC rc = RC::SUCCESS;
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();
  const Selects &selects = sql->sstr.selection;
  // 把所有的表和只跟这张表关联的condition都拿出来，生成最底层的select 执行节点
  std::vector<SelectExeNode *> select_nodes;
  for (size_t i = 0; i < selects.relation_num; i++) {
    const char *table_name = selects.relations[i];
    SelectExeNode *select_node = new SelectExeNode;
    rc = create_selection_executor(trx, selects, db, table_name, *select_node);
    if (rc != RC::SUCCESS) {
      delete select_node;
      for (SelectExeNode *& tmp_node: select_nodes) {
        delete tmp_node;
      }
      end_trx_if_need(session, trx, false);
      char response[256];
      snprintf(response, sizeof(response), "%s\n", rc == RC::SUCCESS ? "SUCCESS" : "FAILURE");
      session_event->set_response(response);
      return rc;
    }
    select_nodes.push_back(select_node);
  }

  if (select_nodes.empty()) {
    LOG_ERROR("No table given");
    end_trx_if_need(session, trx, false);
    return RC::SQL_SYNTAX;
  }

  std::vector<TupleSet> tuple_sets;
  for (SelectExeNode *&node: select_nodes) {
    TupleSet tuple_set;
    rc = node->execute(tuple_set);
    if (rc != RC::SUCCESS) {
      for (SelectExeNode *& tmp_node: select_nodes) {
        delete tmp_node;
      }
      end_trx_if_need(session, trx, false);
      return rc;
    } else {
      tuple_sets.push_back(std::move(tuple_set));
    }
  }

  std::stringstream ss;
  if (tuple_sets.size() > 1) {
    // 本次查询了多张表，需要做join操作
  } else {
    // 当前只查询一张表，直接返回结果即可
    tuple_sets.front().print(ss);
  }

  for (SelectExeNode *& tmp_node: select_nodes) {
    delete tmp_node;
  }
  session_event->set_response(ss.str());
  end_trx_if_need(session, trx, true);
  return rc;
}

void dfs_helper(std::vector<TupleSet> &tuple_sets, size_t depth, std::string str, std::vector<std::string> &result) {
  if (depth == tuple_sets.size()) {
    
    result.push_back(str);
    return;
  }
  if (depth != 0) {
    str += " | ";
  }
  TupleSet &tuple_set = tuple_sets[depth];
  for (size_t i=0; i<tuple_set.size(); i++) {
    std::string tuple_str = str + tuple_set.to_string(i);
    dfs_helper(tuple_sets, depth+1, tuple_str, result);
  }
}


void dfs(std::vector<TupleSet> &tuple_sets, std::vector<std::string> &result) {
  dfs_helper(tuple_sets, 0, "", result);
}


void dfs_helper(std::vector<TupleSet> &tuple_sets, size_t depth, Tuple &tuple, TupleSet &join_tuple_set) {
  if (depth == tuple_sets.size()) {
    join_tuple_set.add(std::move(tuple));
    return;
  }
  TupleSet &tuple_set = tuple_sets[depth];
  for (size_t i=0; i<tuple_set.size(); i++) {
    Tuple tuple_(std::move(tuple));
    const Tuple &tuple_tmp = tuple_set.get(i);
    for (size_t j=0; j<tuple_tmp.size(); j++) {
      tuple_.add(tuple_tmp.get_pointer(j));
    }
    dfs_helper(tuple_sets, depth+1, tuple_, join_tuple_set);
  }
}

void dfs(std::vector<TupleSet> &tuple_sets, TupleSet &join_tuple_set) {
  TupleSchema schema;
  for (TupleSet &tuple_set: tuple_sets) {
    schema.append(tuple_set.get_schema());
  }
  join_tuple_set.set_schema(schema);
  Tuple tuple;
  dfs_helper(tuple_sets, 0, tuple, join_tuple_set);
}

void dfs_helper(std::vector<TupleSet> &tuple_sets, size_t depth, std::vector<std::shared_ptr<TupleValue>> &values, TupleSet &join_tuple_set) {
  if (depth == tuple_sets.size()) {
    Tuple tuple;
    for (std::shared_ptr<TupleValue> tuple_value: values) {
      tuple.add(tuple_value);
    }
    join_tuple_set.add(std::move(tuple));
    return;
  }
  TupleSet &tuple_set = tuple_sets[depth];
  for (size_t i=0; i<tuple_set.size(); i++) {
    // Tuple tuple_(std::move(tuple));
    const Tuple &tuple_tmp = tuple_set.get(i);
    for (size_t j=0; j<tuple_tmp.size(); j++) {
      // tuple_.add(tuple_tmp.get_pointer(j));
      values.push_back(tuple_tmp.get_pointer(j));
    }
    dfs_helper(tuple_sets, depth+1, values, join_tuple_set);
    for (size_t j=0; j<tuple_tmp.size(); j++) {
      // tuple_.add(tuple_tmp.get_pointer(j));
      values.pop_back();
    }
  }
}

void dfs2(std::vector<TupleSet> &tuple_sets, TupleSet &join_tuple_set) {
  TupleSchema schema;
  for (TupleSet &tuple_set: tuple_sets) {
    schema.append(tuple_set.get_schema());
  }
  join_tuple_set.set_schema(schema);
  std::vector<std::shared_ptr<TupleValue>>  values;
  dfs_helper(tuple_sets, 0, values, join_tuple_set);
}

std::string create_header(std::vector<TupleSet> tuple_sets, bool printTableName) {
  std::string header;

  for (const TupleSet &tuple_set: tuple_sets) {
    header += tuple_set.header_to_string(printTableName);
  }
}

enum AGGREGATION_TYPE {
  MAX, MIN, COUNT, AVG, NOT_KNOWN
};

AGGREGATION_TYPE is_aggregation_select(const char * attribute_name, char * &real_attribute_name) {
  if (attribute_name == nullptr) {
    return NOT_KNOWN;
  }
  if (attribute_name[0] == 'M' || attribute_name[0] == 'm') {
    if ((attribute_name[1] == 'A' || attribute_name[1] == 'a') 
      && (attribute_name[2] == 'X' || attribute_name[2] == 'x') 
      && attribute_name[3] == '(') {
      size_t len = strlen(attribute_name) + 1 - 4;
      real_attribute_name = new char[len];
      strcpy(real_attribute_name, attribute_name+4);
      real_attribute_name[len-2] = '\0';
      return MAX;
    }
    if ((attribute_name[1] == 'I' || attribute_name[1] == 'i') 
      && (attribute_name[2] == 'N' || attribute_name[2] == 'n') 
      && attribute_name[3] == '(') {
      size_t len = strlen(attribute_name) + 1 - 4;
      real_attribute_name = new char[len];
      strcpy(real_attribute_name, attribute_name+4);
      real_attribute_name[len-2] = '\0';
      return MIN;
    }
    return NOT_KNOWN;
  } else if ((attribute_name[0] == 'C' || attribute_name[0] == 'c') 
      && (attribute_name[1] == 'O' || attribute_name[1] == 'o') 
      && (attribute_name[2] == 'U' || attribute_name[2] == 'u')
      && (attribute_name[3] == 'N' || attribute_name[3] == 'n') 
      && (attribute_name[4] == 'T' || attribute_name[4] == 't') 
      && attribute_name[5] == '(') {
    size_t len = strlen(attribute_name) + 1 - 6;
    real_attribute_name = new char[len];
    strcpy(real_attribute_name, attribute_name+6);
    real_attribute_name[len-2] = '\0';
    return COUNT;
  } else if ((attribute_name[0] == 'A' || attribute_name[0] == 'a') 
      && (attribute_name[1] == 'V' || attribute_name[1] == 'v')
      && (attribute_name[2] == 'G' || attribute_name[2] == 'g') 
      && attribute_name[3] == '(') {
    size_t len = strlen(attribute_name) + 1 - 4;
    real_attribute_name = new char[len];
    strcpy(real_attribute_name, attribute_name+4);
    real_attribute_name[len-2] = '\0';
    return AVG;
  }
  return NOT_KNOWN;
}

void get_tuple_value(TupleSet &tuple_set, Tuple &tuple, AGGREGATION_TYPE type, int index) {
  // const TupleValue &value_
  
  if (type == MAX) {
    const std::shared_ptr<TupleValue> *p_value = nullptr;
    for (size_t i=0; i<tuple_set.size(); i++) {
      const Tuple &tuple_ = tuple_set.get(i);
      const std::shared_ptr<TupleValue> &value_ = tuple_.get_pointer(index);
      if (p_value == nullptr) {
        p_value = &value_;
        continue;
      }
      int cmp = (*p_value)->compare(*value_);
      if (cmp < 0) {
        p_value = &value_;
      }
    }
    if (p_value == nullptr) {
      // todo: 使用null类型
    } else {
      tuple.add(*p_value);
    }
  } else if (type == MIN) {
    const std::shared_ptr<TupleValue> *p_value = nullptr;
    for (size_t i=0; i<tuple_set.size(); i++) {
      const Tuple &tuple_ = tuple_set.get(i);
      const std::shared_ptr<TupleValue> &value_ = tuple_.get_pointer(index);
      if (p_value == nullptr) {
        p_value = &value_;
        continue;
      }
      int cmp = (*p_value)->compare(*value_);
      if (cmp > 0) {
        p_value = &value_;
      }
    }
    if (p_value == nullptr) {
      // todo: 使用null类型
    } else {
      tuple.add(*p_value);
    }
  } else if (type == COUNT) {
    const std::shared_ptr<TupleValue> *p_value = nullptr;
    std::unordered_map<std::string, bool> value_exist_map;
    int count = 0;
    if (index == -1) {
      count = tuple_set.size();
    } else {
      for (size_t i=0; i<tuple_set.size(); i++) {
        const Tuple &tuple_ = tuple_set.get(i);
        const std::shared_ptr<TupleValue> &value_ = tuple_.get_pointer(index);
        std::string str = value_->to_string();
        // if (value_exist_map.find(str) == value_exist_map.end()) {
        //   count++;
        // }
        count++;
        value_exist_map[str] = true;
      }
    }
    tuple.add(new IntValue(count));
  } else if (type == AVG) {
    if (tuple_set.size() == 0) {
      // todo: 使用null类型
      return;
    }
    const std::shared_ptr<TupleValue> *p_value = &(tuple_set.get(0).get_pointer(index));
    AttrType type = (*p_value)->type();
    float avg = 0;
    if (type == INTS) {
      avg = std::stof((*p_value)->to_string());
    }
    for (size_t i=1; i<tuple_set.size(); i++) {
      const Tuple &tuple_ = tuple_set.get(i);
      const std::shared_ptr<TupleValue> &value_ = tuple_.get_pointer(index);
      if (type == INTS) {
        avg += std::stof(value_->to_string());
      } else {
        (*p_value)->add(*value_);
      }
    }
    if (type == INTS) {
      avg /= tuple_set.size();
      tuple.add(new FloatValue(avg));
    } else {
      (*p_value)->divide(tuple_set.size());
      tuple.add(*p_value);
    }
  }
}

RC projection(const char *db, TupleSet &tuple_set, const Selects &selects, TupleSet &re_tuple_set) {
  re_tuple_set.clear();
  TupleSchema schema;
  const TupleSchema &schema_all = tuple_set.get_schema();
  std::map<std::string, bool> skip_flag;
  std::vector <size_t> indexs; // 需要取出的属性下标集合
  bool aggregation_flag = false;
  std::vector <AGGREGATION_TYPE> aggreations;
  if (selects.relation_num == 1) {
    char *table_name = selects.relations[0];
    Table * table = DefaultHandler::get_default().find_table(db, table_name);
    for (int i = selects.attr_num - 1; i >= 0; i--) {
      const RelAttr &attr = selects.attributes[i];
      if (attr.relation_name != nullptr && 0 != strcmp(attr.relation_name, table_name)) {
        return RC::SCHEMA_TABLE_NOT_EXIST;
      }
      
      auto search = skip_flag.find(table_name);
      if (search != skip_flag.end() && search->second == true) {
        continue;
      }
      char *real_relation_name;
      AGGREGATION_TYPE aggreation = is_aggregation_select(attr.attribute_name, real_relation_name);
      if (aggreation != NOT_KNOWN) {
        aggregation_flag = true;
        aggreations.push_back(aggreation);
        if (strcmp(real_relation_name, "*") == 0) {
          indexs.push_back(-1);
          schema.add_if_not_exists(INTS, "*", attr.attribute_name);
        } else {
          const FieldMeta *field_meta = table->table_meta().field(real_relation_name);
          if (nullptr == field_meta) {
            LOG_WARN("No such field. %s.%s", table->name(), real_relation_name);
            return RC::SCHEMA_FIELD_MISSING;
          }
          indexs.push_back(schema_all.index_of_field(table_name, real_relation_name));
          schema.add_if_not_exists(field_meta->type(), table_name, attr.attribute_name);
        }
        
        continue;
      }
      if (strcmp(attr.attribute_name, "*") == 0) {
        skip_flag[table_name] = true;
        const TableMeta &table_meta = table->table_meta();
        for (int i=table_meta.sys_field_num(); i<table_meta.field_num(); i++) {
          const FieldMeta * field_meta = table_meta.field(i);
          indexs.push_back(schema_all.index_of_field(table->name(), field_meta->name()));
          schema.add_if_not_exists(field_meta->type(), table->name(), field_meta->name());
        }
      } else {
        const FieldMeta *field_meta = table->table_meta().field(attr.attribute_name);
        if (nullptr == field_meta) {
          LOG_WARN("No such field. %s.%s", table->name(), attr.attribute_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        indexs.push_back(schema_all.index_of_field(table_name, attr.attribute_name));
        schema.add_if_not_exists(field_meta->type(), table->name(), field_meta->name());
      }
      
    }
  } else {
    for (int i = selects.attr_num - 1; i >= 0; i--) {
      const RelAttr &attr = selects.attributes[i];
      if (attr.relation_name == nullptr) {
        if (0 != strcmp(attr.attribute_name, "*")) {
          return RC::GENERIC_ERROR;
        }
        schema.clear();
        schema = tuple_set.get_schema();
        for (size_t i=0; i<schema.fields().size(); i++) {
          indexs.push_back(i);
        }
        // re_tuple_set.set_schema(tuple_set.get_schema());
        break;
      }
      Table * table = DefaultHandler::get_default().find_table(db, attr.relation_name);
      auto search = skip_flag.find(attr.relation_name);
      if (search != skip_flag.end() && search->second == true) {
        continue;
      }
      if (strcmp(attr.attribute_name, "*") == 0) {
        skip_flag[attr.relation_name] = true;
        const TableMeta &table_meta = table->table_meta();
        for (int i=0; i<table_meta.field_num()-table_meta.sys_field_num(); i++) {
          const FieldMeta * field_meta = table_meta.field(i);
          indexs.push_back(schema_all.index_of_field(table->name(), field_meta->name()));
          schema.add_if_not_exists(field_meta->type(), table->name(), field_meta->name());
        }
      } else {
        const FieldMeta *field_meta = table->table_meta().field(attr.attribute_name);
        if (nullptr == field_meta) {
          LOG_WARN("No such field. %s.%s", table->name(), attr.attribute_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        indexs.push_back(schema_all.index_of_field(attr.relation_name, attr.attribute_name));
        schema.add_if_not_exists(field_meta->type(), table->name(), field_meta->name());
      }
      
    }
  }
  if (aggregation_flag) {
    Tuple tuple_;
    for (size_t i=0; i<indexs.size(); i++) {
      int index = indexs[i];
      AGGREGATION_TYPE type = aggreations[i];
      get_tuple_value(tuple_set, tuple_, type, index);
    }
    re_tuple_set.set_schema(schema);
    // re_tuple_set.set_aggregation_flag();
    re_tuple_set.add(std::move(tuple_));
    return RC::SUCCESS;
  }
  re_tuple_set.set_schema(schema);
  const std::vector<Tuple> &tuples = tuple_set.tuples();
  for (const Tuple &tuple: tuples) {
    Tuple tuple_;
    for (int index:indexs) {
      tuple_.add(tuple.get_pointer(index));
    }
    re_tuple_set.add(std::move(tuple_));
  }
  return RC::SUCCESS;
}

bool has_order_by(const Selects &selects) {
  for (size_t i = 0; i < selects.condition_num; i++) {
    const Condition &condition = selects.conditions[i];
    CompOp compop = condition.comp;

    if (compop == ORDER_BY_ASC || compop == ORDER_BY_DESC) {
      return true;
    } 

  }
  return false;

}

// 这里没有对输入的某些信息做合法性校验，比如查询的列名、where条件中的列名等，没有做必要的合法性校验
// 需要补充上这一部分. 校验部分也可以放在resolve，不过跟execution放一起也没有关系
RC ExecuteStage::do_select(const char *db, Query *sql, SessionEvent *session_event) {

  RC rc = RC::SUCCESS;
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();
  const Selects &selects = sql->sstr.selection;
  // 把所有的表和只跟这张表关联的condition都拿出来，生成最底层的select 执行节点
  std::vector<SelectExeNode *> select_nodes;
  std::unordered_map<std::string,int> table_map;
  for (size_t i = 0; i < selects.relation_num; i++) {
    const char *table_name = selects.relations[i];
    Table * table = DefaultHandler::get_default().find_table(db, table_name);
    if (nullptr == table) {
      LOG_WARN("No such table [%s] in db [%s]", table_name, db);
      end_trx_if_need(session, trx, false);
      char response[256];
      snprintf(response, sizeof(response), "%s\n", "FAILURE");
      session_event->set_response(response);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    SelectExeNode *select_node = new SelectExeNode;
    rc = create_selection_executor(trx, selects, db, table_name, *select_node);
    if (rc != RC::SUCCESS) {
      delete select_node;
      for (SelectExeNode *& tmp_node: select_nodes) {
        delete tmp_node;
      }
      end_trx_if_need(session, trx, false);
      char response[256];
      snprintf(response, sizeof(response), "%s\n", "FAILURE");
      session_event->set_response(response);
      return rc;
    }
    select_nodes.push_back(select_node);
    table_map[table_name] = selects.relation_num - 1 - i;
  }
  if (table_map.empty()) {
    LOG_ERROR("No table given");
    end_trx_if_need(session, trx, false);
    return RC::SQL_SYNTAX;
  }

  std::vector<TupleSet> tuple_sets;
  for (std::vector<SelectExeNode *>::reverse_iterator iter=select_nodes.rbegin(); iter!=select_nodes.rend(); iter++) {
    SelectExeNode *&node = *iter;
    TupleSet tuple_set;
    rc = node->execute(tuple_set);
    if (rc != RC::SUCCESS) {
      for (SelectExeNode *& tmp_node: select_nodes) {
        delete tmp_node;
      }
      end_trx_if_need(session, trx, false);
      char response[256];
      snprintf(response, sizeof(response), "%s\n", "FAILURE");
      session_event->set_response(response);
      return rc;
    } else {
      tuple_sets.push_back(std::move(tuple_set));
    }
  }

  std::stringstream ss;
  if (tuple_sets.size() > 1) {
    // 本次查询了多张表，需要做join操作
    TupleSet join_tuple_set;
    TupleSet re_tuple_set, re_tuple_set_;
    // dfs2(tuple_sets, join_tuple_set);
    JoinSelectExeNode join_select_node;
    rc = create_join_selection_executor(trx, selects, db, &tuple_sets, &table_map, join_select_node);
    join_select_node.execute(re_tuple_set);
    if (has_order_by(selects)) {
      session_event->set_response(session_event->get_request_buf());
      return RC::GENERIC_ERROR;
      rc = re_tuple_set.sort(selects);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("sort error");
        char response[256];
        snprintf(response, sizeof(response), "%s\n", "FAILURE");
        session_event->set_response(response);
        return RC::GENERIC_ERROR;
      }
    }
    // re_tuple_set.sort(selects);
    rc = projection(db, re_tuple_set, selects, re_tuple_set_);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("projection error");
      // end_trx_if_need(session, trx, false);
      char response[256];
      snprintf(response, sizeof(response), "%s\n", "FAILURE");
      session_event->set_response(response);
      return RC::GENERIC_ERROR;
    }
    re_tuple_set_.print(ss, true);
  } else {
    // 当前只查询一张表，直接返回结果即可
    TupleSet re_tuple_set;
    TupleSet &tuple_set = tuple_sets.front();
    if (has_order_by(selects)) {
      rc = re_tuple_set.sort(selects);
      if (rc != RC::SUCCESS) {
        session_event->set_response(session_event->get_request_buf());
        return RC::GENERIC_ERROR;
        LOG_ERROR("sort error");
        char response[256];
        snprintf(response, sizeof(response), "%s\n", "FAILURE");
        session_event->set_response(response);
        return RC::GENERIC_ERROR;
      }
    }
    
    rc = projection(db, tuple_set, selects, re_tuple_set);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("projection error");
      char response[256];
      snprintf(response, sizeof(response), "%s\n", "FAILURE");
      session_event->set_response(response);
      return RC::GENERIC_ERROR;
    }
    re_tuple_set.print(ss);
  }

  for (SelectExeNode *& tmp_node: select_nodes) {
    delete tmp_node;
  }
  session_event->set_response(ss.str());
  end_trx_if_need(session, trx, true);
  return rc;
}

bool match_table(const Selects &selects, const char *table_name_in_condition, const char *table_name_to_match) {
  if (table_name_in_condition != nullptr) {
    return 0 == strcmp(table_name_in_condition, table_name_to_match);
  }

  return selects.relation_num == 1;
}

static RC schema_add_field(Table *table, const char *field_name, TupleSchema &schema) {
  const FieldMeta *field_meta = table->table_meta().field(field_name);
  if (nullptr == field_meta) {
    LOG_WARN("No such field. %s.%s", table->name(), field_name);
    return RC::SCHEMA_FIELD_MISSING;
  }

  schema.add_if_not_exists(field_meta->type(), table->name(), field_meta->name());
  return RC::SUCCESS;
}

// 把所有的表和只跟这张表关联的condition都拿出来，生成最底层的select 执行节点
RC create_selection_executor(Trx *trx, const Selects &selects, const char *db, const char *table_name, SelectExeNode &select_node) {
  // 列出跟这张表关联的Attr
  TupleSchema schema;
  Table * table = DefaultHandler::get_default().find_table(db, table_name);
  if (nullptr == table) {
    LOG_WARN("No such table [%s] in db [%s]", table_name, db);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  TupleSchema::from_table(table, schema);

  // 找出仅与此表相关的过滤条件, 或者都是值的过滤条件
  std::vector<DefaultConditionFilter *> condition_filters;
  for (size_t i = 0; i < selects.condition_num; i++) {
    const Condition &condition = selects.conditions[i];
    if ((condition.left_is_attr == 0 && condition.right_is_attr == 0) || // 两边都是值
        (condition.left_is_attr == 1 && condition.right_is_attr == 0 && match_table(selects, condition.left_attr.relation_name, table_name)) ||  // 左边是属性右边是值
        (condition.left_is_attr == 0 && condition.right_is_attr == 1 && match_table(selects, condition.right_attr.relation_name, table_name)) ||  // 左边是值，右边是属性名
        (condition.left_is_attr == 1 && condition.right_is_attr == 1 &&
            match_table(selects, condition.left_attr.relation_name, table_name) && match_table(selects, condition.right_attr.relation_name, table_name)
            && condition.comp != ORDER_BY_ASC &&  condition.comp != ORDER_BY_DESC) // 左右都是属性名，并且表名都符合
        ) {
      DefaultConditionFilter *condition_filter = new DefaultConditionFilter();
      RC rc = condition_filter->init(*table, condition);
      if (rc != RC::SUCCESS) {
        delete condition_filter;
        for (DefaultConditionFilter * &filter : condition_filters) {
          delete filter;
        }
        return rc;
      }
      condition_filters.push_back(condition_filter);
    }
  }

  return select_node.init(trx, table, std::move(schema), std::move(condition_filters));
}

bool same_table(char *left_table_name, char * right_table_name) {
  if (left_table_name != nullptr && right_table_name != nullptr) {
    return 0 == strcmp(left_table_name, right_table_name);
  }

  return false;
}

// 把所有的表和只跟这张表关联的condition都拿出来，生成最底层的select 执行节点
RC create_join_selection_executor(Trx *trx, const Selects &selects, const char *db, std::vector<TupleSet> *tuple_sets, std::unordered_map<std::string,int> *table_map, JoinSelectExeNode &join_select_node) {
  // 列出跟这张表关联的Attr
  TupleSchema schema;

  // 找出与两个表相关的过滤条件
  std::vector<DefaultConditionFilter *> condition_filters;
  for (size_t i = 0; i < selects.condition_num; i++) {
    const Condition &condition = selects.conditions[i];
    if (
        (condition.left_is_attr == 1 && condition.right_is_attr == 1 &&
            !same_table(condition.left_attr.relation_name, condition.right_attr.relation_name)) // 左右都是属性名，并且表名都符合
        ) {
      Table * table_left = DefaultHandler::get_default().find_table(db, condition.left_attr.relation_name);
      const TableMeta &table_meta_left = table_left->table_meta();
      Table * table_right = DefaultHandler::get_default().find_table(db, condition.right_attr.relation_name);
      const TableMeta &table_meta_right = table_right->table_meta();
      ConDesc left;
      ConDesc right;
      AttrType type_left = UNDEFINED;
      AttrType type_right = UNDEFINED;
      const FieldMeta *field_left = table_meta_left.field(condition.left_attr.attribute_name);
      if (nullptr == field_left) {
        LOG_WARN("No such field in condition. %s.%s", table_left->name(), condition.left_attr.attribute_name);
        return RC::SCHEMA_FIELD_MISSING;
      }
      left.attr_length = field_left->len();
      left.attr_offset = field_left->offset();
      left.is_attr = true;
      type_left = field_left->type();
      left.value = nullptr;
      left.table_name = new char[strlen(condition.left_attr.relation_name) + 1];
      strcpy(left.table_name, condition.left_attr.relation_name);
      left.attr_name = new char[strlen(condition.left_attr.attribute_name) + 1];
      strcpy(left.attr_name, condition.left_attr.attribute_name);
      
      const FieldMeta *field_right = table_meta_right.field(condition.right_attr.attribute_name);
      if (nullptr == field_right)
      {
        LOG_WARN("No such field in condition. %s.%s", table_right->name(), condition.right_attr.attribute_name);
        return RC::SCHEMA_FIELD_MISSING;
      }
      right.attr_length = field_right->len();
      right.attr_offset = field_right->offset();
      right.is_attr = true;
      type_right = field_right->type();
      right.value = nullptr;
      right.table_name = new char[strlen(condition.right_attr.relation_name) + 1];
      strcpy(right.table_name, condition.right_attr.relation_name);
      right.attr_name = new char[strlen(condition.right_attr.attribute_name) + 1];
      strcpy(right.attr_name, condition.right_attr.attribute_name);
      if (type_left != type_right)
      {
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }

      DefaultConditionFilter *condition_filter = new DefaultConditionFilter();
      

      RC rc = condition_filter->init(left, right, type_left, condition.comp);
      if (rc != RC::SUCCESS) {
        delete condition_filter;
        for (DefaultConditionFilter * &filter : condition_filters) {
          delete filter;
        }
        return rc;
      }
      condition_filters.push_back(condition_filter);
    }
  }

  return join_select_node.init(trx, tuple_sets, table_map, std::move(condition_filters));
}
