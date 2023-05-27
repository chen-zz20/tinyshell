#include "cp.h"

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
    if(filename.size() <= 1)
        error("cp: Please input both source_file and destination_file");
    auto workdir = gTerm.root / gTerm.wdir;
    string dest_file = filename.back();
    auto destinationFile = workdir / fs::path(dest_file);
    for(auto file:filename){
        auto real_path = workdir / fs::path(file);
        if (file == "-")
            real_path = workdir / gTerm.strin;
        //如果source_file不存在，直接报错；如果dest_file存在，则直接复制写入，否则创建再写入。
        else if (file != dest_file){
            if(!fs::exists(real_path)){
                error("cp: " + file + ": No such file or directory");
                continue;
            }
            bool hasSameFileName = false;
            if (std::filesystem::is_directory(destinationFile)) {
                for (const auto& entry : std::filesystem::directory_iterator(destinationFile)) {
                    if (entry.is_regular_file()) {
                        std::filesystem::path fileName = entry.path().filename();
                        if (real_path.filename() == fileName){
                            hasSameFileName = true;
                            break;
                    }
                }
            }
            
                // 如果存在相同文件名的文件，则跳过复制操作
                if (!overwrite && hasSameFileName ) {
                    fs::copy(real_path, destinationFile, fs::copy_options::skip_existing);
                } else {
                    fs::copy(real_path, destinationFile, fs::copy_options::overwrite_existing);
                }
             }
        }
    }
}
