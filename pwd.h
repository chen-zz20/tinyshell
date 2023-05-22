#pragma once
#ifndef pwd_h
#define pwd_h

#include "basic.h"

class Pwd: public Basic{
public:
    Pwd(const vector<string>& _order);
    void work();
};

#endif