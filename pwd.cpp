#include "pwd.h"


Pwd::Pwd(vector<string> _order):Basic(_order, 
    "pwd: pwd [-LP]\n"
    "Print the name of the current working directory.\n\n"
    "Options:\n"
    "  --help      display this help and exit\n\n"
    "By default, `pwd' behaves as if `-L' were specified.\n\n"
    "Exit Status:\n"
    "Returns 0 unless an invalid option is given or the current directory\n"
    "cannot be read.\n"
    ){}


void Pwd::work(){
    auto size = order.size();
    if(size >1){
        if(order[1] == "--help"){
            output_help();
            return ;
        }
        error("pwd: "+ order[1] + ": invalid option");
        return ;
    }
    gTerm.strout = (gTerm.root / gTerm.wdir).make_preferred().lexically_normal().string() + "\n";
    return ;
}