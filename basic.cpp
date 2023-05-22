#include "basic.h"

Basic::Basic(const vector<string>& _order, const string& _help):order(_order), help(_help){}


void Basic::output_help(){
    gTerm.strout = help;
}


void Basic::error(string err){
    cerr << err << endl;
    gTerm.strout = "";
    return ;
}


bool Basic::read_file(const string& file_name, vector<string>& content){
    fstream file(file_name, ios::in);
    if (!file.is_open()) {
        error("Failed to open " + file_name);
        return false;
    }
    content = vector<string>();
    string line;
    while(getline(file, line)){
        content.push_back(line);
    }
    file.close();
    return true;
}


bool Basic::write_file(const string &file_name, const vector<string> &content){
    fstream file(file_name, ios::out);
    if (!file.is_open()) {
        error("Failed to open " + file_name);
        return false;
    }
    for(auto line:content){
        file<<line<<"\n";
    }
    return true;
}