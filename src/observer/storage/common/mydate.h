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
// Created by Wangyunlai on 2021/5/12.
//

#ifndef __OBSERVER_STORAGE_COMMON_DATE_H__
#define __OBSERVER_STORAGE_COMMON_DATE_H__

#include <string>
#include <cstring>
// #include "rc.h"
#include "sql/parser/parse_defs.h"
using namespace std;

class MyDate
{
    // std::string date_str;
    int date_int;
public:
    MyDate() {};
    MyDate(char *date_str);
    MyDate(int date_int);
    ~MyDate() {};
    int toInt();

    // RC date2int(const Value &value, int &date);
    const char *toCStr();
};
#endif // __OBSERVER_STORAGE_COMMON_DATE_H__