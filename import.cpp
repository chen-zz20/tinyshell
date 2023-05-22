#include "import.h"


Import::Import(const vector<string>& _order):Basic(_order, 
    "Usage: load [commands]\n"
    "Import new instructions into the shell script.\n"
    "After importing, it is necessary to recompile.\n"
    "Options:\n"
    "  --help      display this help and exit\n\n"
    "Exit status:\n"
        "0  if OK,\n"
    ){}


void Import::work(){
    auto size = order.size();
    vector<string> command;
    for(size_t i=1; i<size; i++){
        if(order[i] == "--help"){
            output_help();
            return ;
        } else {
            command.push_back(order[i]);
        }
    }
    for(auto c:command){
        change_files(c);
    }
    return ;
}


void Import::change_files(const string& command){
    bool h = false, cpp = false;
    string commend_h = command + ".h";
    string commend_cpp = command + ".cpp";
    for (auto& entry : fs::directory_iterator("./")) {
        string name = entry.path().filename().string();
        if(fs::is_regular_file(entry.path())) {
            if(name == commend_h){
                h = true;
                continue;
            }
            if(name == commend_cpp){
                cpp = true;
                continue;
            }
        }
    }
    if(!(h&&cpp)){
        error("import: " + command + " is not exited");
        return ;
    }

    string Command = command;
    Command[0] = toupper(command[0]);

    // 修改command.h文件
    vector<string> command_text;
    if(read_file("./command.h", command_text)){
        string new_line = "#include \"" + command + ".h\"";
        for(auto line:command_text){
            if(line == new_line){
                gTerm.strout = "";
                return ;
            }
        }
        command_text.insert(command_text.end() - 2, new_line);
        write_file("./command.h", command_text);
    } else {
        return;
    }

    // 修改main.cpp文件
    vector<string> main_text;
    if(read_file("./main.cpp", main_text)){
        const string position = "            } else if (order[0] == \"exit\") {";
        // 修改文件内容
        fstream main_cpp_out("./main.cpp", ios::out);
        string new_line = 
        "            } else if (order[0] == \"" + command + "\") {\n"
        "                auto work = " + Command + "(order);\n"
        "                work.work();\n";
        auto size = main_text.size();
        for(size_t i = 0; i < size - 1; i++){
            auto string = main_text[i] + "\n";
            main_cpp_out << string;
            if(main_text[i+1] == position){
                main_cpp_out << new_line;
            }
        }
        main_cpp_out << main_text[size-1] + "\n";
        main_cpp_out.close();
    } else {
        return ;
    }

    // 修改Makefile
    vector<string> makefile_text;
    if(read_file("./Makefile", makefile_text)){
        makefile_text[2].insert(makefile_text[2].size() - 5, " " + command);
        write_file("./Makefile", makefile_text);
    } else {
        return ;
    }
    return ;
}