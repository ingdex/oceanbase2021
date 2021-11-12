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
// Created by Wangyunlai on 2021/5/14.
//

#include "sql/executor/execution_node.h"
#include "storage/common/table.h"
#include "sql/executor/tuple.h"
#include "common/log/log.h"
#include <iostream>

SelectExeNode::SelectExeNode() : table_(nullptr) {
}

SelectExeNode::~SelectExeNode() {
  for (DefaultConditionFilter * &filter : condition_filters_) {
    delete filter;
  }
  condition_filters_.clear();
}

RC
SelectExeNode::init(Trx *trx, Table *table, TupleSchema &&tuple_schema, std::vector<DefaultConditionFilter *> &&condition_filters) {
  trx_ = trx;
  table_ = table;
  tuple_schema_ = tuple_schema;
  condition_filters_ = std::move(condition_filters);
  return RC::SUCCESS;
}

void record_reader(const char *data, void *context) {
  TupleRecordConverter *converter = (TupleRecordConverter *)context;
  converter->add_record(data);
}
RC SelectExeNode::execute(TupleSet &tuple_set) {
  CompositeConditionFilter condition_filter;
  condition_filter.init((const ConditionFilter **)condition_filters_.data(), condition_filters_.size());

  tuple_set.clear();
  tuple_set.set_schema(tuple_schema_);
  TupleRecordConverter converter(table_, tuple_set);
  return table_->scan_record(trx_, &condition_filter, -1, (void *)&converter, record_reader);
}


JoinSelectExeNode::JoinSelectExeNode() {
}

JoinSelectExeNode::~JoinSelectExeNode() {
  for (DefaultConditionFilter * &filter : condition_filters_) {
    delete filter;
  }
  condition_filters_.clear();
}

RC
JoinSelectExeNode::init(Trx *trx, std::vector<TupleSet> *tuple_sets, std::unordered_map<std::string,int> *table_map, std::vector<DefaultConditionFilter *> &&condition_filters) {
  trx_ = trx;
  tuple_sets_ = tuple_sets;
  table_map_ = table_map;
  condition_filters_ = std::move(condition_filters);
  return RC::SUCCESS;
}

// void record_reader(const char *data, void *context) {
//   TupleRecordConverter *converter = (TupleRecordConverter *)context;
//   converter->add_record(data);
// }

// RC JoinSelectExeNode::execute(TupleSet &tuple_set) {
//   CompositeConditionFilter condition_filter;
//   condition_filter.init((const ConditionFilter **)condition_filters_.data(), condition_filters_.size());
  
//   tuple_set.clear();
//   tuple_set.set_schema(tuple_set_->get_schema());
//   for (size_t i=0; i<tuple_set_->size(); i++) {
//     const Tuple &tuple = tuple_set_->get(i);
//     if (condition_filter.filter(tuple_set_->get_schema(), tuple)) {
//       Tuple tuple_tmp;
//       for (size_t j=0; j<tuple.size(); j++) {
//         tuple_tmp.add(tuple.get_pointer(j));
//       }
//       tuple_set.add(std::move(tuple_tmp));
//     }
//   }
//   return RC::SUCCESS;
// }

void dfs_helper(std::vector<TupleSet> &tuple_sets, size_t depth, std::vector<std::shared_ptr<TupleValue>> &values, DefaultConditionFilter * condition_filter, TupleSet &join_tuple_set) {
  if (depth == tuple_sets.size()) {
    Tuple tuple;
    for (std::shared_ptr<TupleValue> tuple_value: values) {
      tuple.add(tuple_value);
    }
    if (condition_filter == nullptr || condition_filter->filter(join_tuple_set.get_schema(), tuple)) {
      join_tuple_set.add(std::move(tuple));
    }
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
    dfs_helper(tuple_sets, depth+1, values, condition_filter, join_tuple_set);
    for (size_t j=0; j<tuple_tmp.size(); j++) {
      // tuple_.add(tuple_tmp.get_pointer(j));
      values.pop_back();
    }
  }
}

void tuple_set_filter(TupleSet &tuple_set, TupleSet &re_tuple_set, CompositeConditionFilter *condition_filter) {
  for (size_t i=0; i<tuple_set.size(); i++) {
    const Tuple &tuple_tmp = tuple_set.get(i);
    if (condition_filter == nullptr || condition_filter->filter(tuple_set.get_schema(), tuple_tmp)) {
      Tuple tuple;
      for (size_t i=0; i<tuple_tmp.size(); i++) {
        tuple.add(tuple_tmp.get_pointer(i));
      }
      re_tuple_set.add(std::move(tuple));
    }
  }
}

void inner_join(std::vector<TupleSet> &tuple_sets, TupleSet &join_tuple_set, DefaultConditionFilter * condition_filter) {
  if (tuple_sets.size() == 0) {
    join_tuple_set = std::move(tuple_sets[0]);
    return;
  }
  TupleSchema schema;
  for (TupleSet &tuple_set: tuple_sets) {
    schema.append(tuple_set.get_schema());
  }
  join_tuple_set.set_schema(schema);
  // Tuple tuple;
  std::vector<std::shared_ptr<TupleValue>>  values;
  dfs_helper(tuple_sets, 0, values, condition_filter, join_tuple_set);
}
// step1:
// 遍历所有选择条件，如果要选择的两个关系之前没有都没有出现过，则将选择结果放入新的tuple_set，然后加入re_tuple_sets中
// 如果一个关系之前出现过，一个没出现过，则将连接结果放入之前出现过的关系的tuple_set在re_tuple_sets的对应位置，
// 如果两个关系在re_tuple_sets中出现，且处在一个tuple_set中，则直接根据condition_filter过滤对应集合，将结果替换到原来位置
// 如果两个关系在re_tuple_sets中出现，且不处在一个tuple_set中，则根据condition_filter连接两个集合，连接后的集合替换到原来的较低的位置
// step2:
// 将没有选择过的表格加入re_tuple_sets
// step3:
// 最后，在re_tuple_sets上做笛卡尔积
RC JoinSelectExeNode::execute(TupleSet &re_tuple_set) {
  CompositeConditionFilter condition_filter;
  condition_filter.init((const ConditionFilter **)condition_filters_.data(), condition_filters_.size());
  
  re_tuple_set.clear();
  // tuple_set.set_schema(tuple_set_->get_schema());
  // TupleSet tuple_set;
  int joined[tuple_sets_->size()] = {0, };
  
  std::vector<TupleSet> re_tuple_sets;
  std::unordered_map<int, int> table_index_to_re_tuple_set_index_map;  // 记录下标为index的关系目前在re_tuple_sets的第几个元素中
  std::unordered_map<int, std::vector<int> > re_tuple_set_index_to_table_indexs_map; // 上面map的反向map

  for (DefaultConditionFilter * condition_filter_tmp:condition_filters_) {
    const ConDesc &left = condition_filter_tmp->left();
    const ConDesc &right = condition_filter_tmp->right();
    int index_left = (*table_map_)[left.table_name];
    int index_right = (*table_map_)[right.table_name];
    if (joined[index_left] && joined[index_right]) {
      int re_tuple_set_index_left = table_index_to_re_tuple_set_index_map[index_left];
      int re_tuple_set_index_right = table_index_to_re_tuple_set_index_map[index_right];
      if (re_tuple_set_index_left == re_tuple_set_index_right) {
        TupleSet tuple_set;
        tuple_set_filter(re_tuple_sets[re_tuple_set_index_left], tuple_set, &condition_filter);
        // 修改re_tuple_sets，删除旧集合，放入过滤后的新元组集合
        re_tuple_sets.erase(re_tuple_sets.begin() + re_tuple_set_index_left);
        re_tuple_sets.insert(re_tuple_sets.begin() + re_tuple_set_index_left, std::move(tuple_set));
      } else {
        TupleSet &tuple_set_left = re_tuple_sets[re_tuple_set_index_left];
        TupleSet &tuple_set_right = re_tuple_sets[re_tuple_set_index_right];
        std::vector<TupleSet> tuple_sets_for_join;
        tuple_sets_for_join.push_back(std::move(tuple_set_left));
        tuple_sets_for_join.push_back(std::move(tuple_set_right));
        TupleSet tuple_set;
        inner_join(tuple_sets_for_join, tuple_set, condition_filter_tmp);
        // 修改re_tuple_sets，删除旧集合，放入过滤后的新元组集合
        int index_low = index_left < index_right ? index_left : index_right;
        int index_high = index_left > index_right ? index_left : index_right;
        re_tuple_sets.erase(re_tuple_sets.begin() + index_low);
        re_tuple_sets.erase(re_tuple_sets.begin() + index_high);
        re_tuple_sets.insert(re_tuple_sets.begin() + index_low, std::move(tuple_set));

        // 修改map
        // int index_low = index_left < index_right ? index_left : index_right;
        // int index_up = index_left > index_right ? index_left : index_right;
        std::vector<int> indexs_left = re_tuple_set_index_to_table_indexs_map[re_tuple_set_index_left];
        std::vector<int> indexs_right = re_tuple_set_index_to_table_indexs_map[re_tuple_set_index_left];
        std::unordered_map<int, bool> flag;
        for (int i:indexs_left) {
          flag[i] = true;
        }
        for (int i:indexs_right) {
          if (flag.find(i) != flag.end()) {
            re_tuple_set_index_to_table_indexs_map[index_low].push_back(i);
          }
        }
        std::vector<int> &indexs = re_tuple_set_index_to_table_indexs_map[index_high];
        for (int index : indexs)
        {
          table_index_to_re_tuple_set_index_map[index] = index_low;
        }
        for (int i=index_high+1; i<re_tuple_sets.size(); i++) {
          std::vector<int> &indexs = re_tuple_set_index_to_table_indexs_map[i];
          for (int index : indexs)
          {
            table_index_to_re_tuple_set_index_map[index]--;
          }
          re_tuple_set_index_to_table_indexs_map[i-1] = re_tuple_set_index_to_table_indexs_map[i];
        }
        re_tuple_set_index_to_table_indexs_map.erase(re_tuple_sets.size());
      }
    } else if (!joined[index_left] && !joined[index_right]) {
      TupleSet &tuple_set_left = (*tuple_sets_)[index_left];
      TupleSet &tuple_set_right = (*tuple_sets_)[index_right];
      std::vector<TupleSet> tuple_sets_for_join;
      tuple_sets_for_join.push_back(std::move(tuple_set_left));
      tuple_sets_for_join.push_back(std::move(tuple_set_right));
      TupleSet tuple_set;
      inner_join(tuple_sets_for_join, tuple_set, condition_filter_tmp);
      re_tuple_sets.push_back(std::move(tuple_set));
      int re_tuple_set_index = re_tuple_sets.size() - 1;
      table_index_to_re_tuple_set_index_map[index_left] = re_tuple_set_index;
      table_index_to_re_tuple_set_index_map[index_right] = re_tuple_set_index;
      std::vector<int> tmp{index_left, index_right};
      re_tuple_set_index_to_table_indexs_map[re_tuple_set_index] = tmp;
      joined[index_left] = 1;
      joined[index_right] = 1;
    } else if (joined[index_left] && !joined[index_right]) {
      int re_tuple_set_left_index = table_index_to_re_tuple_set_index_map[index_left];
      TupleSet &tuple_set_left = re_tuple_sets[re_tuple_set_left_index];
      TupleSet &tuple_set_right = (*tuple_sets_)[index_right];
      std::vector<TupleSet> tuple_sets_for_join;
      tuple_sets_for_join.push_back(std::move(tuple_set_left));
      tuple_sets_for_join.push_back(std::move(tuple_set_right));
      TupleSet tuple_set;
      inner_join(tuple_sets_for_join, tuple_set, condition_filter_tmp);
      re_tuple_sets.erase(re_tuple_sets.begin() + re_tuple_set_left_index);
      re_tuple_sets.insert(re_tuple_sets.begin() + re_tuple_set_left_index, std::move(tuple_set));
      table_index_to_re_tuple_set_index_map[index_right] = re_tuple_set_left_index;
      re_tuple_set_index_to_table_indexs_map[re_tuple_set_left_index].push_back(index_right);
      joined[index_right] = 1;
    } else { // !joined[index_left] && joined[index_right]
      int re_tuple_set_right_index = table_index_to_re_tuple_set_index_map[index_right];
      TupleSet &tuple_set_left = (*tuple_sets_)[index_left];
      TupleSet &tuple_set_right = re_tuple_sets[re_tuple_set_right_index];
      std::vector<TupleSet> tuple_sets_for_join;
      tuple_sets_for_join.push_back(std::move(tuple_set_right));
      tuple_sets_for_join.push_back(std::move(tuple_set_left));
      TupleSet tuple_set;
      inner_join(tuple_sets_for_join, tuple_set, condition_filter_tmp);
      re_tuple_sets.erase(re_tuple_sets.begin() + re_tuple_set_right_index);
      re_tuple_sets.insert(re_tuple_sets.begin() + re_tuple_set_right_index, std::move(tuple_set));
      table_index_to_re_tuple_set_index_map[index_right] = re_tuple_set_right_index;
      re_tuple_set_index_to_table_indexs_map[re_tuple_set_right_index].push_back(index_left);
      joined[index_left] = 1;
    }
  }
  for (int i=0; i<tuple_sets_->size(); i++) {
    if (table_index_to_re_tuple_set_index_map.find(i) == table_index_to_re_tuple_set_index_map.end()) {
      re_tuple_sets.push_back(std::move((*tuple_sets_)[i]));
    }
  }
  inner_join(re_tuple_sets, re_tuple_set, nullptr);
  return RC::SUCCESS; 
}