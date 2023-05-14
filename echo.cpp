#include "shell.h"
#include "basic.h"

void doEcho(const vector<string> order){
    bool no_newline = false;
    for (const auto& arg : order) {
        if (arg == "--help") {
            cout << "echo: echo [STRING]\n"
                    "    Display a line of text\n";
            break;
        }
        if (arg == "-n") {
            no_newline = true;
            break;
        }
    }
    for (size_t i = 1; i < order.size(); i++) {
        if(order[i]!="--help" && order[i]!="-n"){
            gTerm.strout += order[i];
        }
    }
    if(!no_newline)
        cout<<gTerm.strout<<endl;
    else
        cout<<gTerm.strout;
}
