//
//  main.cpp
//  HelloWorld1
//
//  Created by skyplan on 2020/6/30.
//  Copyright © 2020 skyplan. All rights reserved.
//
#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <stdio.h>
#include <iostream>
using namespace std;

class String
{
public:
    String(const char *str = NULL);    //通用构造函数
    String(const String &str);        //拷贝构造函数
    ~String();                        //析构函数

    String operator+(const String &str) const;    //重载+
    String& operator=(const String &str);        //重载=
    bool operator==(const String &str) const;    //重载==
    
    size_t size() const;
    const char* c_str() const;    //获取C字符串
    
    friend istream& operator>>(istream &is, String &str);//输入
    friend ostream& operator<<(ostream &os, String &str);//输出
private:
    char *data;
    size_t length;
};

String::String(const char *str)
{
    if (!str) {
        length = 0;
        data = new char[1];
        *data = '\0';
    }
    else {
        length = strlen(str);
        data = new char [length + 1];
        strcpy(data, str);
    }
}

String::String(const String &str)
{
    length = str.size();
    data = new char[length + 1];
    strcpy(data, str.c_str());
}

String::~String()
{
    delete []data;
    length = 0;
}

String String::operator+(const String &str) const//重载+
{
    String newString;
    newString.length = length + str.size();
    newString.data = new char[newString.length + 1];
    strcpy(newString.data, data);
    strcat(newString.data, str.data);
    return newString;
}

String& String::operator=(const String &str)//重载=
{
    if (this == &str) {
        return *this;
    }

    delete []data;
    length = str.length;
    data = new char[length + 1];
    strcpy(data, str.c_str());
    
    return *this;
}

inline bool String::operator==(const String &str) const//重载==
{
    if (length != str.length)    return false;
    return strcmp(data, str.data) ? false : true;
}

inline size_t String::size() const//获取长度
{
    return length;
}

inline const char* String::c_str() const//获取C字符串
{
    return data;
}

istream& operator>>(istream &is, String &str)//输入
{
    char tem[1000];  //简单的申请一块内存
    is >> tem;
    str.length = strlen(tem);
    str.data = new char[str.length + 1];
    strcpy(str.data, tem);
    return is;
}

ostream& operator<<(ostream &os, String &str)//输出
{
    os << str.data;
    return os;
}

int main()
{
    String s;
    cin >> s;
    cout << s << ": " << s.size() << endl;
    
    char a[] = "Hello", b[] = "World!";
    String s1(a), s2(b);
    cout << s1;
    cout << " + ";
    cout << s2 ;
    cout << " = ";
    String ss = s1 + s2;
    cout << ss;
    cout << endl;
    
    String s3 = s1 + s2;
    if (s1 == s3)    cout << "First: s1 == s3" << endl;
    
    return 0;
}

