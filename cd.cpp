#include "cd.h"


Cd::Cd(const vector<string>& _order):Basic(_order, 
    "cd: cd [dir]\n"
    "Change the shell working directory.\n\n"
    "Change the current directory to DIR.  The default DIR is the value of the\n"
    "HOME shell variable.\n\n"
    "The variable CDPATH defines the search path for the directory containing\n"
    "DIR.  Alternative directory names in CDPATH are separated by a colon (:).\n"
    "A null directory name is the same as the current directory.  If DIR begins\n"
    "with a slash (/), then CDPATH is not used.\n\n"
    "If the directory is not found, and the shell option `cdable_vars' is set,\n"
    "the word is assumed to be  a variable name.  If that variable has a value,\n"
    "its value is used for DIR.\n\n"
    "Options:\n"
    "  --help      display this help and exit\n\n"
    "The default is to follow symbolic links, as if `-L' were specified.\n"
    "`..' is processed by removing the immediately previous pathname component\n"
    "back to a slash or the beginning of DIR.\n\n"
    "Exit Status:\n"
    "Returns 0 if the directory is changed, and if $PWD is set successfully when\n"
    "-P is used; non-zero otherwise.\n"
    ){}


void Cd::work(){
    auto size = order.size();
    if(size > 2){
        error("cd: too many arguments");
        return ;
    } else if (size == 1){
        gTerm.strout = "\n";
        return ;
    }
    if (order[1] == "--help"){
        output_help();
        return ;
    }
    fs::path workdir = order[1];
    workdir = gTerm.wdir / workdir;
    workdir = workdir.make_preferred();
    auto realdir = gTerm.root / workdir;
    if(fs::exists(realdir)){
        if(fs::is_directory(realdir)) {
            gTerm.wdir = fs::relative(realdir, gTerm.root).lexically_normal().make_preferred();
        } else {
            error("cd: " + order[1] + ": Not a directory");
            return ;
        }
    } else {
        error("cd: " + order[1] + ": No such file or directory");
        return ;
    }
    return ;
}
