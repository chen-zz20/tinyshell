#include "echo.h"

Echo::Echo(vector<string> _order):newline(true), Basic(_order, 
    "echo [-neE] [arg ...]\n"
    "Write arguments to the standard output.\n\n"
    "Display the ARGs, separated by a single space character and followed by a\n"
    "newline, on the standard output.\n\n"
    "Options:\n"
    "  -n        do not append a newline\n\n"
    "`echo' interprets the following backslash-escaped characters:\n"
    "  \\a        alert (bell)\n"
    "  \\b        backspace\n"
    "  \\c        suppress further output\n"
    "  \\e        escape character\n"
    "  \\E        escape character\n"
    "  \\f        form feed\n"
    "  \\n        new line\n"
    "  \\r        carriage return\n"
    "  \\t        horizontal tab\n"
    "  \\v        vertical tab\n"
    "  \\\\        backslash\n"
    "  \\0nnn     the character whose ASCII code is NNN (octal).  NNN can be\n"
    "              0 to 3 octal digits\n"
    "  \\xHH      the eight-bit character whose value is HH (hexadecimal).  HH\n"
    "              can be one or two hex digits\n\n"
    "Exit Status:\n"
    "Returns success unless a write error occurs.\n"
    ){}


void Echo::work(){
    for (const auto& arg : order) {
        if (arg == "--help"){
            output_help();
            return ;
        } else if (arg == "-n"){
            newline = false;
        }
    }
    for (size_t i = 1; i < order.size(); i++) {
        if(order[i] != "-n"){
            output += order[i];
        }
    }
    if(newline)
        output += '\n';
    gTerm.strout = output;
    return ;
}
