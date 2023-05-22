#pragma once
#ifndef import_h
#define import_h

#include "basic.h"

class Import: public Basic{
public:
    Import(const vector<string>& _order);
    void work();
    void change_files(const string& command);
};

#endif