#include "cat.h"

Cat::Cat(const vector<string>& _order):Basic(_order,
    "cat [OPTION]... [FILE]...\n"
    "concatenate files and print on the standard output\n\n"
    "Options:\n"
    "-n            number all output lines"
    "-b            number nonempty output lines, overrides -n"
    "-s            suppress repeated empty output lines"
    "-E            display $ at end of each line"
    "--help        display this help and exit"
    ){}

void Cat::work(){
    bool numberline = false;
    bool empty = false;
    bool simem = false;
    bool dis$ = false;
    for (const auto& arg : order) {
        if (arg == "--help"){
            output_help();
            return ;
        } else if (arg == "-n"){
            numberline = true;
        } else if (arg == "-b"){
            empty = true;
        } else if (arg == "-s"){
            simem = true;
        }
        else if (arg == "-E"){
            dis$ = true;
        }
    }
    fs::path workdir = order[order.size() - 1];
    workdir = gTerm.wdir / workdir;
    workdir = workdir.make_preferred();
    auto realdir = gTerm.root / workdir;
    if(fs::exists(realdir)){
        if(realdir.extension() == ".txt"){   //判断是否为txt文件
            ifstream file(order[order.size() - 1]);
            if (file) {
                string line;
                string previousLine = "";
                bool isPreviousLineEmpty = false;
                int lineNumber = 1;
                while (getline(file, line)) {
                    // 逐行读取文件内容并输出到标准输出
                    if (numberline){
                        gTerm.strout += static_cast<char>(lineNumber);
                        gTerm.strout += ":";
                        gTerm.strout += line;
                        gTerm.strout += "\n";
                    }
                    if (empty){
                        if (line.empty())
                            gTerm.strout += line;
                    }
                    if (simem){
                        if(line.empty()){
                            if(isPreviousLineEmpty)
                                continue;
                            else
                                gTerm.strout += "\n";
                            isPreviousLineEmpty = true;
                        }
                        else{
                            isPreviousLineEmpty = false;
                            gTerm.strout += line;
                        }
                        lineNumber += 1;
                    }
                }
            }
            else{
                error("cat: " + order[order.size() - 1] + ": Cannot open,please check");
                return ;
            }
        }
        else{
            error("cat: " + order[order.size() - 1] + ": Not a txt document");
            return;
        }
    }
}
