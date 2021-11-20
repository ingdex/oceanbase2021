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
// Created by wangyunlai.wyl on 2021/5/18.
//

#include "storage/common/index_meta.h"
#include "storage/common/field_meta.h"
#include "storage/common/table_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "rc.h"
#include "json/json.h"
#include <iostream>
#include <sstream>
#include <vector>

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString FIELD_FIELD_NAME("field_name");

RC IndexMeta::init(const char *name, const FieldMeta * field[], const int file_num) {
  if (nullptr == name || common::is_blank(name)) {
    return RC::INVALID_ARGUMENT;
  }

  file_num_ = file_num;
  name_ = name;
  field_ = new std::string[file_num];
  //field_ = field.name();
  for(int i = 0; i < file_num; i++) {
    field_[i] = field[i]->name();
  }

  return RC::SUCCESS;
}

void IndexMeta::to_json(Json::Value &json_value) const {
  json_value[FIELD_NAME] = name_;
  std::string all;
  int num = file_num();
  for(int i = 0; i < num; i++) {
    all += field_[i];
    all += ' ';
  }

  json_value[FIELD_FIELD_NAME] = all;
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index) {
  const Json::Value &name_value = json_value[FIELD_NAME];
  const Json::Value &field_value = json_value[FIELD_FIELD_NAME];
  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }

  if (!field_value.isString()) {
    LOG_ERROR("Field name of index [%s] is not a string. json value=%s",
              name_value.asCString(), field_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }

  int file_num = 0;
  std::string all = field_value.asString();
  std::istringstream str(all);
  std::string out;
  std::vector<std::string> temp_str;
  while (str >> out) {
    temp_str.push_back(out);
    file_num++;
  }

  const FieldMeta* field[file_num];
  //FieldMeta *field = new FieldMeta[file_num];
  for(int i = 0; i < file_num; i++) {
    field[i] = table.field(temp_str[i].c_str());
  }

  //const FieldMeta *field = table.field(field_value.asCString());
  if (nullptr == field) {
    LOG_ERROR("Deserialize index [%s]: no such field: %s", name_value.asCString(), field_value.asCString());
    return RC::SCHEMA_FIELD_MISSING;
  }

  return index.init(name_value.asCString(), field, file_num);
}

const char *IndexMeta::name() const {
  return name_.c_str();
}

const char *IndexMeta::field(int &index) const {
  int num = file_num();
  if(index<= num)
    return field_[index].c_str();
  else 
    return NULL;
}

const int IndexMeta::file_num() const {
  return file_num_;
}

void IndexMeta::desc(std::ostream &os) const {
  os << "index name=" << name_
      << ", field=" << field_;
}