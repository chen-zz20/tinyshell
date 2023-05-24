#pragma once
#ifndef echo_h
#define echo_h
#include "basic.h"

class Echo: public Basic{
private:
    bool newline;
    bool interpretation; // 反斜杠转义
    string unescape(const string& str); // 处理//转译问题

public:
    Echo(const vector<string>& _order);
    void work();
};

#endif