#include "Basic class.h"
#include "shell.h"

using namespace std;
Terminal gTerm;

int basic::work(char * s){
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
}
   
