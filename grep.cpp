#include "grep.h"
#include <regex>

Grep::Grep(const vector<string>& _order):ifc(false), ifh(false), ifi(false), ifn(false), A(0), B(0), Basic(_order,
    "Usage: grep [OPTION]... PATTERNS [FILE]...\n"
    "Search for PATTERNS in each FILE.\n"
    "Example: grep -i 'hello world' menu.h main.c\n"
    "PATTERNS can contain multiple patterns separated by newlines.\n\n"
    "Pattern selection and interpretation:\n"
    "  -i, --ignore-case         ignore case distinctions in patterns and data\n"
    "      --no-ignore-case      do not ignore case distinctions (default)\n\n"
    "Miscellaneous:\n"
    "--help                display this help text and exit\n\n"
    "Output control:\n"
    "  -n, --line-number         print line number with output lines\n"
    "  -H, --with-filename       print file name with output lines\n"
    "  -h, --no-filename         suppress the file name prefix on output\n"
    "  -c, --count               print only a count of selected lines per FILE\n\n"
    "Context control:\n"
    "  -B, --before-context=NUM  print NUM lines of leading context\n"
    "  -A, --after-context=NUM   print NUM lines of trailing context\n\n"
    "When FILE is '-', read standard input.  With no FILE, read '.' if\n"
    "recursive, '-' otherwise.  With fewer than two FILEs, assume -h.\n"
    "Exit status is 0 if any line (or file if -L) is selected, 1 otherwise;\n"
    "if any error occurs and -q is not given, the exit status is 2.\n"
    ){}

void Grep::work(){
    //初始化参数
    int h=0;//因为默认是否加文件名规则是如果有2个文件默认加文件名，1个不加。
    //而有几个文件需要后面才知道，所以在初始化判断有无-h或-H的时候用h过度一下。
    vector<string> filename; // 第一个位置应该是模式串的位置
    for (size_t i=1; i<order.size(); i++) {
        auto arg = order[i];
        if (arg == "--help"){
            output_help();
            return ;
        } else if (arg == "-c"){
            ifc = true;
        } else if (arg == "-h"){
            h = -1;
        } else if (arg == "-H"){
            h = 1;
        } else if (arg == "-i"){
            ifi = true;
        } else if (arg == "-n"){
            ifn = true;
        } else if (arg.substr(0, 2) == "-A"){
            A = stoi(arg.substr(2));
            if(A == 0){
                error("grep: A: invalid context length argument.");
                return ;
            }
        } else if (arg.substr(0, 2) == "-B"){
            B = stoi(arg.substr(2));
            if(B == 0){
                error("grep: B: invalid context length argument.");
                return ;
            }
        } else {
            filename.push_back(arg);
        }
    }
    if(filename.size()<2){
        error("Usage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep --help' for more information.");
        return ;
    }
    //模式串处理
    string pattern=Initialization_mode_string(filename[0]);
    regex x;
    //如果有-i，那么忽略大小写
    if(ifi){
        x = regex(pattern, regex::icase);
    } else{
        x = regex(pattern);
    }
    //文档位置处理
    const size_t number_of_document = filename.size() - 1;
    //用文件个数判断ifh的值：
    if(h == 0) {
        if(number_of_document == 1)
            ifh=false;
        else
            ifh=true;
    } else if(h==1)
        ifh=true;
    else
        ifh=false;//ifh=true时候加文件头名
    //文件读取、处理
    auto workdir = gTerm.root / gTerm.wdir;
    for(size_t i=1; i<=number_of_document; i++){
        string file = filename[i];
        auto real_path = workdir / fs::path(file);
        vector<string> content;
        if(file == "-"){
            read_file("-", content);
        } else {
            auto real_path = workdir / fs::path(file);
            if(!fs::exists(real_path)){
                error("grep: " + file + ": No such file or directory");
                continue;
            }
            if(fs::is_directory(real_path)){
                error("grep: " + file + ": Is a directory");
                continue;
            }
            if(!read_file(real_path.string(), content)){
                error("grep: failed to open " + file);
                continue;
            }
        }
        int c=0;//统计符合通配符的行数
        smatch m;
        vector<GrepLine> grep_lines;//存放匹配后要输出的字符串信息
        size_t size = content.size();
        for(size_t i=0; i<size; i++){
            auto line = content[i];
            string number_of_line = green + to_string(i + 1);
            GrepLine grep_line;
            if(!regex_search(line, m, x)){
                if(ifn)
                    grep_line.t = number_of_line + blue + "-"+ white + line + "\n";
                else
                    grep_line.t = white + line + "\n";
                grep_lines.push_back(grep_line);
                continue;
            }
            grep_line.fit = true;
            int n = 0;
            if(ifn)
                grep_line.t = number_of_line + blue + ":";
            while(regex_search(line, m, x)){
                grep_line.t += white;
                n = line.find(m[0]);
                grep_line.t.append(line, 0, n);
                string b = m[0];
                grep_line.t += red + b;
                line.erase(0, n+b.length());
            }
            grep_line.t += white + line + "\n";
            c++;
            grep_lines.push_back(grep_line);
        }
        string txtname;
        if(ifh)
            txtname = magenta + file + blue + ":";//如果要输出文件头，则写入文件头。否则保持空白
        if(ifc){
            output += txtname + white + to_string(c) + "\n";
            continue;//打开下一个文件
        }
        for(size_t j=0; j<size; j++)
            if(grep_lines[j].fit)
                for(int k = ((j - B) > 0) ? (j - B) : 0; k<=(j+A); k++)
                    grep_lines[k].output=true;
        for(size_t j=0; j<size; j++)
            if(grep_lines[j].output)
                output += txtname + grep_lines[j].t;
    }
    gTerm.strout = output;
    return ;
}


string Grep::Initialization_mode_string(const string &pattern){
    string t=pattern;
    int n=0;
    while(n!=-1)
    {
        n=t.find('*', n);
        if(n!=-1)
        {
            t.insert(n,".");
            n+=2;
        }
    }
    return t;
}