#pragma once
#ifndef basic_h
#define basic_h

#include "shell.h"


class Basic{
public:
    const string green = "";  //\e[92;1m
    const string blue = "";   //\e[94;1m
    const string red = "";    //\e[91;1m
    const string white = "";    //\e[0m
    const string help;
    vector<string> order;
    string output;
    virtual void work() = 0;

    Basic(const vector<string>& _order, const string& _help);
    void output_help();
    void error(string err);
    bool read_file(const string& file_name, vector<string>& content);
    bool write_file(const string& file_name, const vector<string>& content, const char mode='w');
};



#endif
