#pragma once
#ifndef tee_h
#define tee_h
#include "basic.h"

class Tee: public Basic{
public:
    Tee(const vector<string>& _order);
    void work();
private:
    bool overwrite; //默认为覆盖
};

#endif /* tee_h */
