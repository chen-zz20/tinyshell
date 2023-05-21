#include "basic.h"

Basic::Basic(const vector<string>& _order, const string& _help):order(_order), help(_help){}


void Basic::output_help(){
    gTerm.strout = help;
}


void Basic::error(std::string err){
    cerr << err << endl;
    gTerm.strout = "";
    return ;
}