#pragma once
#ifndef cat_h
#define cat_h

#include "basic.h"

class Cat: public Basic{
public:
    Cat(const vector<string>& _order);
    void work();
};

#endif

