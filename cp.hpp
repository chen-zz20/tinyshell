#pragma once
#ifndef cp_hpp
#define cp_hpp
#include "basic.h"

class Cp: public Basic{
private:
    bool overwrite; //默认为覆盖
    void copyFile(const string& sourceFile, const string& destinationFile);
public:
    Cp(const vector<string>& _order);
    void work();
};

#endif /* cp_hpp */
