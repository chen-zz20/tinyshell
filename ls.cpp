#include "ls.h"


Ls::Ls(const vector<string>& _order):Basic(_order, 
    "Usage: ls\n"
    "List information about the FILEs (the current directory by default).\n"
    "Sort entries alphabetically.\n\n"
    "Options:\n"
    "  --help      display this help and exit\n\n"
    "Exit status:\n"
        "0  if OK,\n"
        "1  if minor problems (e.g., cannot access subdirectory),\n"
        "2  if serious trouble (e.g., cannot access command-line argument).\n"
    ){}


void Ls::work(){
    auto size = order.size();
    fs::path p = "./";
    if(size > 1 && order[1] == "--help"){
        output_help();
        return ;
    } else if (size > 2) {
        error("ls: too many arguments");
        return ;
    } else if (size == 2) {
        p = order[1];
    }

    auto realdir = ((gTerm.root / gTerm.wdir) / p).make_preferred().lexically_normal();
    if(!fs::exists(realdir)){
        error("ls: cannot access '" + order[1] + "': No such file or directory");
        return ;
    }
    if(!fs::is_directory(realdir)){
        gTerm.strout = green + order[1] + white + "\n";
        return ;
    }

    for (const auto& entry:fs::directory_iterator(realdir)) {
        if (fs::is_directory(entry.path())) {
            output = output + blue + entry.path().filename().string() + " ";
        } else if (fs::is_regular_file(entry.path())) {
            output = output + green + entry.path().filename().string() + " ";
        } else {
            output = output + white + entry.path().filename().string() + " ";
        }
    }
    gTerm.strout = output + white + "\n";
    return ;
}
