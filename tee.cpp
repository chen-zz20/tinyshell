#include "tee.h"

Tee::Tee(const vector<string>& _order):overwrite(true),Basic(_order,
    "usage: tee [OPTION]... [FILE]... \n"
    "Read from standard input and write to standard output and files \n\n"
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
    auto workdir = gTerm.root / gTerm.wdir;
    vector<string> content;
    read_file("-", content);
    char sign = overwrite ? 'w' : 'a';
    for(auto file:filename){
        if(file == "-"){
            continue;
        }
        auto real_path = workdir / fs::path(file);
        if(fs::is_directory(real_path)){
            error("tee: " + file + ": Is a directory");
            continue;
        }
        if(!write_file(real_path.string(), content, sign)){
            error("tee: failed to open " + file);
            continue;
        }
    }
    gTerm.strout = gTerm.strin;
    return ;
}
