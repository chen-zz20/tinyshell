#include "shell.h"
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
    cout << gTerm.user << "@" << gTerm.mach << ":" << gTerm.wdir << "$ ";
}


//分割命令，存在字符数组里
/*vector<string> order_pro(){
    string order;
    cin.get();
    getline(cin,order);
    vector<string> s1;
    istringstream Str1(order);
    string temp;
    while (Str1 >> temp) {
            s1.push_back(temp);
        }
    return s1;
    
}*/
int Process(char * s) {
    static char * p[MAXLINE];
    static char * argv[MAXLINE];
    int len = 0;
    for (int i = 0; s[i] && s[i] != '\n'; i ++) {
        if (s[i] == ' ') {
            s[i] = 0;
        }   //将空格替换为'\0'，就可以将每个参数独立出来，存储到p数组中
        else if (!i || !s[i - 1]) {
            p[len ++] = s + i;  //指针数组p中存储的就是字符串s中所有单词的起始地址, s + i 指向字符串 s 中第 i 个字符的地址
        }
    }
    gTerm.strin[0] = 0;
    gTerm.strout[0] = 0;
    for (int i = 0; i < len; ) {
        char * op = p[i ++];    //使用 op 可以避免改变 p[i] 的值
        if (op[0] == '|') {
            continue;
            swap(gTerm.strout, gTerm.strin);}
        gTerm.strout[0] = 0;
        int argc = 0;
        argv[argc ++] = op;
        for (; i < len && p[i][0] != '|'; i ++) {
            argv[argc ++] = p[i];
        }
        if (!strcmp(op, "diff")) {
            doDiff(argc, argv);
        }
        else if (!strcmp(op, "grep")) {
            doGrep(argc, argv);
        }
        else if (!strcmp(op, "tee")) {
            doTee(argc, argv);
        }
        else if (!strcmp(op, "cat")) {
            doCat(argc, argv);
        }
        else if (!strcmp(op, "cp")) {
            doCp(argc, argv);
        }
        else if (!strcmp(op, "cd")) {
            doCd(argc, argv);
        }
        else if (!strcmp(op, "pwd")) {
            doPwd(argc, argv);
        }
        else if (!strcmp(op, "echo")) {
            doEcho(argc, argv);
        }
        else if (!strcmp(op, "exit")) {
            return 0;
        }
        else {
            Red("Error: ");
            cout << "Command '" << op << "' not found" << endl;
        }
    }
    cout << gTerm.strout;
    return 1;
}


int main(int argc, const char * argv[]) {
    initial();
    return 0;
}
