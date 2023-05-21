#pragma once
#ifndef cd_h
#define cd_h

#include "basic.h"

class Cd: public Basic{
public:
    Cd(vector<string> _order);
    void work();
};

#endif