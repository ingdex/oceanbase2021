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
// Created by wangyunlai.wyl on 2021/5/19.
//

#include "storage/common/bplus_tree_index.h"
#include "common/log/log.h"

BplusTreeIndex::~BplusTreeIndex() noexcept {
  close();
}

RC BplusTreeIndex::create(const char *file_name, const IndexMeta &index_meta, const FieldMeta * field_meta[], const bool unique) {
  if (inited_) {
    return RC::RECORD_OPENNED;
  }

  RC rc = Index::init(index_meta, field_meta);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  rc = Index::init_unique(unique);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  //rc = index_handler_.create(file_name, field_meta.type(), field_meta.len());
  rc = index_handler_.create(file_name, field_meta, index_meta.file_num());
  if (RC::SUCCESS == rc) {
    inited_ = true;
  }
  return rc;
}

RC BplusTreeIndex::open(const char *file_name, const IndexMeta &index_meta, const FieldMeta * field_meta[]) {
  if (inited_) {
    return RC::RECORD_OPENNED;
  }
  RC rc = Index::init(index_meta, field_meta);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  rc = index_handler_.open(file_name);
  if (RC::SUCCESS == rc) {
    inited_ = true;
  }
  return rc;
}

RC BplusTreeIndex::close() {
  if (inited_) {
    index_handler_.close();
    inited_ = false;
  }
  return RC::SUCCESS;
}

RC BplusTreeIndex::insert_entry(const char *record, const RID *rid) {
  std::string key_str = "";
  int field_num = index_meta_.file_num();
  const char *keys[field_num];
  int total_len = 0;
  for(int i =0; i < field_num; i++) {
    total_len += field_meta_[i].len();
    keys[i] = record + field_meta_[i].offset();
    // key_str += (record + field_meta_[i].offset());
  }
  char * key = new char[total_len];
  size_t offset = 0;
  for (int i=0; i<field_num; i++) {
    memcpy(key + offset, keys[i], field_meta_[i].len());
    offset += field_meta_[i].len();
  }
  //const char * key = key_str.c_str();
  
  if(unique_) {
    RID * search_rid = new RID[1];
    RC rc = index_handler_.search_key(key, search_rid);
    delete [] search_rid;
    if(rc == RC::SUCCESS)
      return RC::INVALID_ARGUMENT;
  }

  return index_handler_.insert_entry(key, rid);
}

RC BplusTreeIndex::delete_entry(const char *record, const RID *rid) {
  std::string key_str = "";
  int field_num = index_meta_.file_num();
  for(int i =0; i < field_num; i++) {
    key_str += (record + field_meta_[i].offset());
  }
  const char * key = key_str.c_str();

  return index_handler_.delete_entry(key, rid);
}

RC BplusTreeIndex::update_entry(const char *record, const RID *rid) {
  std::string key_str = "";
  int field_num = index_meta_.file_num();
  for(int i =0; i < field_num; i++) {
    key_str += (record + field_meta_[i].offset());
  }
  const char * key = key_str.c_str();

  return index_handler_.insert_entry(key, rid);
}

IndexScanner *BplusTreeIndex::create_scanner(CompOp comp_op, const char *value) {
  BplusTreeScanner *bplus_tree_scanner = new BplusTreeScanner(index_handler_);
  RC rc = bplus_tree_scanner->open(comp_op, value);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open index scanner. rc=%d:%s", rc, strrc(rc));
    delete bplus_tree_scanner;
    return nullptr;
  }

  BplusTreeIndexScanner *index_scanner = new BplusTreeIndexScanner(bplus_tree_scanner);
  return index_scanner;
}

RC BplusTreeIndex::sync() {
  return index_handler_.sync();
}

////////////////////////////////////////////////////////////////////////////////
BplusTreeIndexScanner::BplusTreeIndexScanner(BplusTreeScanner *tree_scanner) :
    tree_scanner_(tree_scanner) {
}

BplusTreeIndexScanner::~BplusTreeIndexScanner() noexcept {
  tree_scanner_->close();
  delete tree_scanner_;
}

RC BplusTreeIndexScanner::next_entry(RID *rid) {
  return tree_scanner_->next_entry(rid);
}

RC BplusTreeIndexScanner::destroy() {
  delete this;
  return RC::SUCCESS;
}