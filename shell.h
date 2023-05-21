#pragma once
#ifndef shell_h
#define shell_h
#include <iostream>
#include <cstring>
#include <filesystem>
#include <stdio.h>
#include <sstream>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

class Terminal {
public:
    string user;    //用户名
    string mach;    //计算机名
    fs::path root;    //根目录
    fs::path wdir;    //工作目录
    string strin;   //重定向标准输入
    string strout;  //重定向标准输出
    void output(){cout<<strout<<endl;}
};

extern Terminal gTerm;

#endif
