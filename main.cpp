#include "shell.h"
#include "command.h"

using namespace std;

Terminal gTerm;

//初始化输出
void initial(){
    cout << "Machine Name: ";
    cin >> gTerm.mach;
    cout << "Login: ";
    cin >> gTerm.user;
    while(true){
        cout << "Root Directory: ";
        fs::path root;
        cin >> root;
        if(fs::exists(root)){
            gTerm.root = root;
            break;
        }
        cerr << root.string() << ": No such directory" << endl;
    }
    gTerm.wdir = "/";
    cin.get();
}


int main(int argc, const char * argv[]) {
    initial();
    while(true){
        gTerm.strin = "";
        gTerm.strout = "";
        cout << gTerm.user << "@" << gTerm.mach << ":" << gTerm.wdir.string() << "$ ";
        string user_input;
        vector<string> substrings;
        getline(cin, user_input);
        size_t pos = 0;
        while ((pos = user_input.find("|")) != string::npos) {
            string substring = user_input.substr(0, pos);
            substrings.push_back(substring);
            user_input.erase(0, pos + 1);
        }
        substrings.push_back(user_input);   //分割复合指令
        vector<vector<string>> split_substrings;
            for (const auto& substring : substrings) {
                vector<string> split;
                istringstream iss(substring);
                string word;
                while (iss >> word) {
                    split.push_back(word);
                }
                split_substrings.push_back(split);
            }   //分割每个指令字符串
        for(auto order:split_substrings){
            if (order[0] == "echo") {
                auto work = Echo(order);
                work.work();
            } else if (order[0] == "pwd") {
                auto work = Pwd(order);
                work.work();
            } else if (order[0] == "exit") {
                return 0;
            }
            else {
                cerr << order[0] << ": command not found" << endl;
            }
        }
        cout<<gTerm.strout;
    }
    return 0;
}

