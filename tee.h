#pragma once
#ifndef tee_h
#define tee_h
#include "basic.h"

class Tee: public Basic{
private:
    bool overwrite; //默认为覆盖

public:
    Tee(const vector<string>& _order);
    void work();
};

#endif /* tee_h */
