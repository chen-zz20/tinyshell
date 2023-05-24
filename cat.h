#pragma once
#ifndef cat_h
#define cat_h

#include "basic.h"

class Cat: public Basic{
private:
    int numberline; //默认为0表示不需要加编号，为1表示-n，为2表示-b，-n, -b 冲突优先-b
    bool simem;     //-s
    bool dis$;      //-E
    bool is_blank_line(const string& line); //判断是否是空行

public:
    Cat(const vector<string>& _order);
    void work();
};

#endif

