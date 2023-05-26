#include "tee.h"

Tee::Tee(const vector<string>& _order):overwrite(true),Basic(_order,
    "usage: tee [OPTION]... [FILE]... \n"
    "Read from standard input and write to standard output and files \n"
    "Options:\n"
    " -a          append to the given FILEs, do not overwrite\n"
    " --help      display this help and exit\n\n"
    ){}


void Tee::work(){
    vector<string> filename;
    auto size = order.size();
    for (size_t i = 1; i < size; i++) {
        auto arg = order[i];
        if (arg == "--help"){
            output_help();
            return ;
        } else if (arg == "-a"){
            overwrite = false;
        } else {
            filename.push_back(arg);
        }
    }
    if(filename.empty())
        filename.push_back("-");
    auto workdir = gTerm.root / gTerm.wdir;
    vector<string> content;
    for(auto file:filename){
        if(file == "-"){
            gTerm.strout = "";
            continue;
        }
        auto real_path = workdir / fs::path(file);
        char sign;
        if(overwrite)
            sign = 'w';
        else
            sign = 'a';
        write_file(file, content, sign);
        if(fs::is_directory(real_path)){
            error("tee: " + file + ": Is a directory");
            continue;
        }
        if(!write_file(real_path.string(), content)){
            error("tee: failed to open " + file);
            continue;
        }
    }
    if(content.empty()){
        gTerm.strout = "";
        return ;
    }
    gTerm.strout = output;
    return ;
}
