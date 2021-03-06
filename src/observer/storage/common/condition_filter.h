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
// Created by Wangyunlai on 2021/5/7.
//

#ifndef __OBSERVER_STORAGE_COMMON_CONDITION_FILTER_H_
#define __OBSERVER_STORAGE_COMMON_CONDITION_FILTER_H_

#include "rc.h"
#include "sql/parser/parse.h"
#include "sql/executor/tuple.h"

struct Record;
class Table;

struct ConDesc {
  bool   is_text;
  bool   is_attr;     // 是否属性，false 表示是值
  int    attr_length; // 如果是属性，表示属性值长度
  int    attr_offset; // 如果是属性，表示在记录中的偏移量
  // bool  nullable;     // 是否可为null
  void * value;       // 如果是值类型，这里记录值的数据
  char * attr_name;
  char * table_name;
  AttrType type;
  ConDesc()
  {
  };
  ConDesc(bool is_attr, int attr_length, int attr_offset, void *value):is_attr(is_attr), attr_length(attr_length), attr_offset(attr_offset), value(value)
  {
  };
  
};

class ConditionFilter {
public:
  virtual ~ConditionFilter();

  /**
   * Filter one record
   * @param rec
   * @return true means match condition, false means failed to match.
   */
  virtual bool filter(const Record &rec) const = 0;
  virtual bool filter(const TupleSchema &schema_, const Tuple &tuple) const = 0;
};

class DefaultConditionFilter : public ConditionFilter {
public:
  DefaultConditionFilter();
  virtual ~DefaultConditionFilter();

  RC init(const ConDesc &left, const ConDesc &right, AttrType attr_type, CompOp comp_op, TupleSet *tuple_set, TupleSet *tuple_set_left);
  RC init(Table &table, const Condition &condition);

  virtual bool filter(const Record &rec) const;
  virtual bool filter(const TupleSchema &schema_, const Tuple &tuple) const;

public:
  const ConDesc &left() const {
    return left_;
  }

  const ConDesc &right() const {
    return right_;
  }

  CompOp comp_op() const {
    return comp_op_;
  }

private:
  ConDesc  left_;
  ConDesc  right_;
  AttrType attr_type_ = UNDEFINED;
  CompOp   comp_op_ = NO_OP;
  TupleSet *tuple_set_ = nullptr;
  TupleSet *tuple_set_left_ = nullptr;
};

class CompositeConditionFilter : public ConditionFilter {
public:
  CompositeConditionFilter() = default;
  virtual ~CompositeConditionFilter();

  RC init(const ConditionFilter *filters[], int filter_num);
  RC init(Table &table, const Condition *conditions, int condition_num);
  virtual bool filter(const Record &rec) const;
  virtual bool filter(const TupleSchema &schema_, const Tuple &tuple) const;

public:
  int filter_num() const {
    return filter_num_;
  }
  const ConditionFilter &filter(int index) const {
    return *filters_[index];
  }

private:
  RC init(const ConditionFilter *filters[], int filter_num, bool own_memory);
private:
  const ConditionFilter **      filters_ = nullptr;
  int                           filter_num_ = 0;
  bool                          memory_owner_ = false; // filters_的内存是否由自己来控制
};

#endif // __OBSERVER_STORAGE_COMMON_CONDITION_FILTER_H_