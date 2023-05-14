#ifndef shell_h
#define shell_h
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <vector>
using namespace std;

const int MAXLINE = 1 << 16;
const int MAXFILE = 1 << 20;

struct Terminal {
    string user;    //用户名
    string mach;    //计算机名
    string root;    //根目录
    string wdir;    //工作目录
    string strin;   //重定向标准输入
    string strout;  //重定向标准输出
};

void doDiff(int argc, char * argv[]);
void doGrep(int argc, char * argv[]);
void doTee(int argc, char * argv[]);
void doCat(int argc, char * argv[]);
void doCp(int argc, char * argv[]);
void doCd(int argc, char * argv[]);
void doPwd(int argc, char * argv[]);
void doEcho(int argc, char * argv[]);
void Green(const char * s);
void Blue(const char * s);
void Red(const char * s);

#endif /* shell_h */
