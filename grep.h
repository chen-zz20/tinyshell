#pragma once
#ifndef grep_h
#define grep_h
#include "basic.h"

class Grep: public Basic{
private:
    bool c,outname,i,numberline,after,before;
    int afnu,benu,afsign,bfsign;
public:
    Grep(const vector<string>& _order);
    void work();
    void printLines(const std::string& filename, int m, int n, int numberline);
};
#endif 
