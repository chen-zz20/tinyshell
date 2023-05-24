#pragma once
#ifndef import_h
#define import_h

#include "basic.h"

class Import: public Basic{
private:
    void change_files(const string& command);

public:
    Import(const vector<string>& _order);
    void work();
};

#endif