#include "cp.hpp"

Cp::Cp(const vector<string>& _order):overwrite(true),Basic(_order,
    "usage: cp [OPTION] source_file destination_file\n"
    "copy files and directories\n"
    "Options:\n"
    " -n          do not overwrite an existing file\n"
    " --help      display this help and exit\n\n"
    ){}

void Cp::work(){
    vector<string> filename;
    auto size = order.size();
    for (size_t i = 1; i < size; i++) {
        auto arg = order[i];
        if (arg == "--help"){
            output_help();
            return ;
        } else if (arg == "-n"){
            overwrite = false;
        } else {
            filename.push_back(arg);
        }
    }
    if(filename.empty() || filename.size() == 1)
        error("cp: Please input both source_file and destination_file");
    auto workdir = gTerm.root / gTerm.wdir;
    string dest_file = filename.back();
    vector<string> content;
    string sourceFile;
    char sign = overwrite ? 'w' : 'a';
    for(auto file:filename){
        auto real_path = workdir / fs::path(file);
        if (file == "-")
            sourceFile = gTerm.strin;
        //如果source_file不存在，直接报错；如果dest_file存在，则直接复制写入，否则创建再写入。
        else if (file != dest_file){
            sourceFile = file;
            if(!fs::exists(real_path)){
                error("cp: " + file + ": No such file or directory");
                continue;
            }
        }
        copyFile(sourceFile, dest_file);
    }
}

void Cp::copyFile(const string& sourceFile, const string& destinationFile) {
    ifstream source(sourceFile, ios::binary);
    ofstream destination(destinationFile, ios::binary);
    
    // 检查目标文件是否存在
    if (!destination) {
        // 目标文件不存在，创建一个新文件
        std::ofstream createFile(destinationFile);
        createFile.close();

        // 重新打开目标文件
        destination.open(destinationFile, std::ios::binary);
    }
    if (source && destination) {
        // 逐个字节复制文件内容
        char ch;
        while (source.get(ch)) {
            destination.put(ch);
        }
        
    } else {
        error("cp: " + sourceFile + "or " + destinationFile + " cannot open.");
    }
    source.close();
    destination.close();
}
