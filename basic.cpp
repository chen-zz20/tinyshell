#include "basic.h"

Basic::Basic(vector<string> _order, const string& _help):order(_order), help(_help){}


void Basic::output_help(){
    gTerm.strout = help;
}