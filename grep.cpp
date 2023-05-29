#include "grep.h"

Grep::Grep(const vector<string>& _order):c(false),outname(true),i(false),numberline(false),after(false), before(false), afnu(0), benu(0), afsign(0), bfsign(0), Basic(_order,
    "usage: grep [options] pattern [file...] \n"
    "print lines that match patterns \n\n"
    "Options:\n"
    " -c    Suppress normal output; instead print a count of matching lines for each input file. \n"    //只计算行数不输出内容
    " -h    Suppress the prefixing of file names on output. \n"
                                               // 不显示文件名
    " -H    Print the file name for each match. \n"
                                               //显示文件名
    " -i    Ignore case distinctions in patterns and input data.\n"
                                               //忽略字符大小写的差别
    " -n    Prefix each line of output with the 1-based line number within its input file.\n"                     //标示出该行的编号
    " -A    Print NUM lines of trailing context after matching lines.\n"
                  //除了显示符合范本样式的那一列之外，同时显示该行之后的[行数]行内容
    " -B    Print NUM lines of leading context before matching lines.\n"
                  //除了显示符合样式的那一行之外，同时显示该行之前的[行数]内容
    " --help      display this help and exit\n\n"
    ){}

void Grep::work(){
    vector<string> filename;
    string object="";
    auto size = order.size();
    for (size_t i = 1; i < size; i++) {
        auto arg = order[i];
        if(afsign == 1){
            afnu = stoi(arg);
            afsign = 0;
        }
        if(bfsign == 1){
            benu = stoi(arg);
            bfsign = 0;
        }
        if (arg == "--help"){
            output_help();
            return ;
        } else if (arg == "-c"){
            c = true;
        } else if (arg == "-h"){
            outname = false;
        } else if (arg == "-H"){
            outname = true;
        } else if (arg == "-i"){
            i = true;
        } else if (arg == "-n"){
            numberline = true;
        } else if (arg == "-A"){
            after = true;
            afsign = 1;
        } else if (arg == "-B"){
            before = true;
            bfsign = 1;
        } else {
            auto workdir = gTerm.root / gTerm.wdir;
            auto real_path = workdir / fs::path(arg);
            if(!fs::exists(real_path))
                object = arg;
            else
                filename.push_back(arg);    //查找字符串放到object中，待查文件放到了filename中
        }
    }
        if(object == "")
            error("Please input the object string.");
        if(filename.empty())
            filename.push_back("-");
        // 替换成你的查找模式
        for(auto file:filename){
            int account = 1;
            string line;
            smatch matches;
            regex pattern;
            if (i){
                pattern = regex("object", regex_constants::icase);
            } else {
                pattern = regex("object");
            }
            auto workdir = gTerm.root / gTerm.wdir;
            string filepath = workdir / fs::path(file);
            ifstream obfile(filepath);
            if (!obfile)
                error("grep: " + file + " cannot open");
            //顺序：文件名 编号
            while (getline(obfile, line)) {
                account ++;
                if (regex_search(line, matches, pattern)) {
                    int start = account - afnu;
                    int end = account + benu;
                    obfile.close();
                    printLines(file, start, end, account);
                }
            }
        }
           
    }

void Grep::printLines(const string& filename, int m, int n, int numberline) {
    ifstream file(filename);
    string line;
    int lineCount = numberline;
    
    // 逐行读取文件
    while (getline(file, line)) {
        lineCount++;
        if(c){
            output += (to_string(lineCount) + "\n");
            break;
        }
        if(outname)
            output += (filename + ": " );
        // 当行数在范围内时打印输出
        if(numberline)
            output += lineCount;
        if (lineCount >= m && lineCount <= n) {
            output += (line + "\n");
        }
        
        // 当达到指定行数后停止读取
        if (lineCount >= n) {
            break;
        }
    }
    gTerm.strout += output;
    file.close();
}
