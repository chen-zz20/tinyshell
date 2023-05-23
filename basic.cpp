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
    istream *input=nullptr;
    if(file_name=="-"){
        input = new stringstream(gTerm.strout);
    } else {
        auto file = new ifstream(file_name);
        if (!file->is_open()) {
            error("Failed to open " + file_name);
            delete file;
            return false;
        }
        input = file;
    }
    content = vector<string>();
    string line;
    while(getline(*input, line)){
        content.push_back(line);
    }
    if(dynamic_cast<ifstream*>(input))
        (*(dynamic_cast<ifstream*>(input))).close();
    delete input;
    return true;
}


bool Basic::write_file(const string &file_name, const vector<string> &content, const char mode){
    ostream *output=nullptr;
    if(file_name=="-"){
        output = new stringstream(gTerm.strout);
    } else {
        ofstream *file=nullptr;
        if(mode == 'w')
            file = new ofstream(file_name, ios::out);
        else if (mode == 'a')
            file = new ofstream(file_name, ios::app);
        else
            return false;
        if (!file->is_open()) {
            error("Failed to open " + file_name);
            delete file;
            return false;
        }
        output = file;
    }
    auto size = content.size();
    for(size_t i = 0; i < size - 1; i++){
        *output << content[i] << "\n";
    }
    *output << content[size-1];
    if(dynamic_cast<ofstream*>(output))
        (*(dynamic_cast<ofstream*>(output))).close();
    return true;
}