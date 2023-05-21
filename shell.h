#pragma once
#ifndef shell_h
#define shell_h
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <sstream>
#include <vector>
using namespace std;

const int MAXLINE = 1 << 16;
const int MAXFILE = 1 << 20;

class Terminal {
public:
    string user;    //用户名
    string mach;    //计算机名
    string root;    //根目录
    string wdir;    //工作目录
    string strin;   //重定向标准输入
    string strout;  //重定向标准输出
    void output(){cout<<strout<<endl;}
};

extern Terminal gTerm;

#endif
