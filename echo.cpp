#include "echo.h"


Echo::Echo(vector<string> _order):newline(true), interpretation(false), Basic(_order, 
    "echo [-neE] [arg ...]\n"
    "Write arguments to the standard output.\n\n"
    "Display the ARGs, separated by a single space character and followed by a\n"
    "newline, on the standard output.\n\n"
    "Options:\n"
    "  -n        do not append a newline\n"
    "  -e        enable interpretation of the following backslash escapes\n"
    "  -E        disable interpretation of backslash escapes (default)\n"
    "--help      display this help and exit\n\n"
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
        } else if (arg == "-e"){
            interpretation = true;
        } else if (arg == "-E"){
            interpretation = false;
        }
    }
    for (size_t i = 1; i < order.size(); i++) {
        if(order[i] != "-n" && order[i] != "-e" && order[i] != "-E"){
            if (interpretation)
                output += unescape(order[i]);
            else
                output += order[i];
        }
    }
    if(newline)
        output += '\n';
    gTerm.strout = output;
    return ;
}


string Echo::unescape(const string& str) {
    string res;
    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] == '\\') {
            i++;
            if (i >= str.size()) {
                // 在字符串末尾遇到单独的反斜杠，不进行转义
                res += '\\';
                break;
            }
            switch (str[i]) {
                case 'a': res += '\a'; break;
                case 'b': res += '\b'; break;
                case 'c': return res;   // 遇到 \c，停止后续输出
                case 'e': 
                case 'E': res += '\e'; break;
                case 'f': res += '\f'; break;
                case 'n': res += '\n'; break;
                case 'r': res += '\r'; break;
                case 't': res += '\t'; break;
                case 'v': res += '\v'; break;
                case '\\': res += '\\'; break;
                case 'x': {
                    // 转换十六进制
                    if (i + 2 < str.size()) {
                        int val = 0;
                        for (int j = i + 1; j < i + 3; j++) {
                            if (str[j] >= '0' && str[j] <= '9') {
                                val = val * 16 + (str[j] - '0');
                            } else if (str[j] >= 'a' && str[j] <= 'f') {
                                val = val * 16 + (str[j] - 'a' + 10);
                            } else if (str[j] >= 'A' && str[j] <= 'F') {
                                val = val * 16 + (str[j] - 'A' + 10);
                            } else {
                                // 非法的十六进制数值，不进行转义
                                res += '\\';
                                res += 'x';
                                i++;
                                continue;
                            }
                        }
                        res += static_cast<char>(val);
                        i += 2;
                    } else {
                        // 不完整的十六进制转义，不进行转义
                        res += '\\';
                        res += 'x';
                    }
                    break;
                }
                case '0': {
                    // 转换八进制
                    if (i + 3 < str.size()) {
                        int val = 0;
                        for (int j = i + 1; j < i + 4; j++) {
                            if (str[j] >= '0' && str[j] <= '7') {
                                val = val * 8 + (str[j] - '0');
                            } else {
                                // 非法的八进制数值，不进行转义
                                res += '\\';
                                res += '0';
                                i++;
                                continue;
                            }
                        }
                        res += static_cast<char>(val);
                        i += 3;
                    } else {
                        // 不完整的八进制转义，不进行转义
                        res += '\\';
                        res += '0';
                    }
                    break;
                }
                default:
                    // 未知的转义字符，不进行转义
                    res += '\\';
                    res += str[i];
                    break;
            }
        } else {
            res += str[i];
        }
    }
    return res;
}