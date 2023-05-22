#pragma once
#ifndef ls_h
#define ls_h

#include "basic.h"

class Ls: public Basic{
public:
    Ls(const vector<string>& _order);
    void work();
};

#endif