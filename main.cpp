#include "shell.h"
#include "command.h"

using namespace std;

Terminal gTerm;

//初始化输出
void initial(){
    cout << "Machine Name: ";
    cin >> gTerm.mach;
    cout << "Root Directory: ";
    cin >> gTerm.root;
    cout << "Login: ";
    cin >> gTerm.user;
    gTerm.wdir = "/";
    cin.get();
}


int main(int argc, const char * argv[]) {
    initial();
    while(true){
        gTerm.strin = "";
        gTerm.strout = "";
        cout << gTerm.user << "@" << gTerm.mach << ":" << gTerm.wdir << "$ ";
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
            //cout<<order[0]<<" "<<order[1]<<endl;
            /*if (order[0].compare("diff") == 0) {
                doDiff(argc, argv);
            }
            else if (order[0].compare("grep") == 0) {
                doGrep(argc, argv);
            }
            else if (order[0].compare("tee") == 0) {
                doTee(argc, argv);
            }
            else if (order[0].compare("cat") == 0) {
                doCat(argc, argv);
            }
            else if (order[0].compare("cp") == 0) {
                doCp(argc, argv);
            }
            else if (order[0].compare("cd") == 0) {
                doCd(argc, argv);
            }
            else if (order[0].compare("pwd") == 0) {
                doPwd(argc, argv);
            }*/
            if (order[0] == "echo") {
                auto work = Echo(order);
                work.work();
            }
            else if (order[0] == "exit") {
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

