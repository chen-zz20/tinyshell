#pragma once
#ifndef cp_h
#define cp_h
#include "basic.h"

class Cp: public Basic{
private:
    bool overwrite; //默认为覆盖
    void copyFile(const string& sourceFile, const string& destinationFile, bool overwrite);

public:
    Cp(const vector<string>& _order);
    void work();
};

#endif
