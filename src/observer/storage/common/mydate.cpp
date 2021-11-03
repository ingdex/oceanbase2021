#include "mydate.h"
// #include <iostream>
#include <string>
using namespace std;
MyDate::MyDate(char *date_str)
{
    int y, m, d;
    const char *y_str, *m_str, *d_str;
    int a[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // 读取data数据void*转换
    char data_str[16] = {
        0,
    };
    std::memcpy(data_str, date_str, 10);

    // 字符串分割
    std::string str = data_str;
    size_t pos = str.find('-');
    y_str = str.substr(0, pos).c_str();
    y = atoi(y_str);
    str = str.substr(pos + 1);
    pos = str.find('-');
    m_str = str.substr(0, pos).c_str();
    m = atoi(m_str);
    str = str.substr(pos + 1);
    pos = str.find('-');
    d_str = str.substr(0, pos).c_str();
    d = atoi(d_str);

    // 日期合法性判断

    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
    { //如果是闰年
        a[1] = 29;
        if (0 < d && d <= a[m - 1] && m > 0 && m <= 12)
        {
            if (y < 1970 || (y >= 2038 && m >= 2))
            {
                // 越过区间
                date_int = -1;
                return;
            }
        }
        else
        {
            date_int = -1;
            return;
        }
    }
    else
    {
        if (0 < d && d <= a[m - 1] && 0 < m && 12 >= m)
        {
            if (y < 1970 || (y >= 2038 && m >= 2))
            {
                // 越过区间
                date_int = -1;
                return;
            }
        }
        else
        {
            date_int = -1;
            return;
        }
    }
    date_int = d + m * 100 + y * 10000;
    // date_str = string(date_int);
    return;
}

MyDate::MyDate(int date_int):date_int(date_int) {

}

int MyDate::toInt()
{
    return date_int;
}

// RC date2int(const Value &value, int &date);
const char *MyDate::toCStr()
{
    char *str = new char[11];
    int x;
    int date = date_int;
    for (int i = 9; i >= 0; i--)
    {
        if (i == 7 || i == 4)
        {
            str[i] = '-';
            continue;
        }
        x = date % 10;
        date /= 10;
        str[i] = x + '0';
    }
    str[10] = '\0';
    return str;
}