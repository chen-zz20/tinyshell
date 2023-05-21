#pragma once
#ifndef echo_h
#define echo_h
#include "basic.h"

class Echo: public Basic{
private:
    bool newline;

public:
    Echo(vector<string> _order);
    void work();
};

#endif