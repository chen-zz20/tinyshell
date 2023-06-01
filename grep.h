#pragma once
#ifndef grep_h
#define grep_h
#include "basic.h"

class Grep: public Basic{
private:
    string Initialization_mode_string(const string& pattern);
    bool ifc, ifh, ifi, ifn;
    int A, B;
    //处理后结构体定义
    struct GrepLine{
        string t;//处理后的结构体
        bool fit=false;//记录这一行是否有变动
        bool output=false;//记录这一行是否输出
    };

public:
    Grep(const vector<string>& _order);
    void work();
    
};
#endif 
