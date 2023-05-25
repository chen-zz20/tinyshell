#include "cat.h"
#include <cmath>

Cat::Cat(const vector<string>& _order):numberline(0), simem(false), dis$(false), Basic(_order,
    "Usage: cat [OPTION]... [FILE]...\n"
    "Concatenate FILE(s) to standard output.\n\n"
    "With no FILE, or when FILE is -, read standard input.\n\n"
    "Options:\n"
    " -n            number all output lines\n"
    " -b            number nonempty output lines, overrides -n\n"
    " -s            suppress repeated empty output lines\n"
    " -E            display $ at end of each line\n"
    " --help        display this help and exit\n"
    ){}

void Cat::work(){
    vector<string> filename;
    auto size = order.size();
    for (size_t i = 1; i < size; i++) {
        auto arg = order[i];
        if (arg == "--help"){
            output_help();
            return ;
        } else if (arg == "-n" && numberline != 2){
            numberline = 1;
        } else if (arg == "-b"){
            numberline = 2;
        } else if (arg == "-s"){
            simem = true;
        } else if (arg == "-E"){
            dis$ = true;
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
            read_file("-", content);
            continue;
        }
        auto real_path = workdir / fs::path(file);
        if(!fs::exists(real_path)){
            error("cat: " + file + ": No such file or directory");
            continue;
        }
        if(fs::is_directory(real_path)){
            error("cat: " + file + ": Is a directory");
            continue;
        }
        if(!read_file(real_path.string(), content)){
            error("cat: failed to open " + file);
            continue;
        }
    }
    if(content.empty()){
        gTerm.strout = "";
        return ;
    }
    const int width = static_cast<int>(log10(content.size()) + 1);
    int n = 1;
    bool blank_before = false;
    for(const auto& line:content){
        bool blank = is_blank_line(line);
        string number = numberline==0 ? "" : ((numberline == 2 && blank) ? string(width+1, ' ') : string(width - static_cast<int>(log10(n) + 1), ' ') + green + to_string(n) + white + " ");
        if(simem){
            if(blank){
                if(blank_before)
                    continue;
                else{
                    blank_before = true;
                }
            } else {
                blank_before = false;
            }
        }
        if(numberline == 1 || (numberline == 2 && !blank))
            n++;
        output += (number + line + (dis$?"$":"") + "\n");
    }
    gTerm.strout = output;
    return ;
}


bool Cat::is_blank_line(const string& line){
    return line.find_first_not_of(" \t\n\v\f\r") == string::npos;
}
