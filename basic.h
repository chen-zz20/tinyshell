#pragma once

#ifndef basic_h
#define basic_h
class basic{
public:
    vector<vector<string>> splitCommands(const vector<string> substrings);
private:
};

vector<vector<string>> basic::splitCommands(const vector<string> substrings){
    vector<vector<string>> split_substrings;
    for (const auto& substring : substrings) {
        vector<string> split;
        istringstream iss(substring);
        string word;
        while (iss >> word) {
            //cout<<"word:  "<<word<<endl;
            split.push_back(word);
        }
        split_substrings.push_back(split);
    }
    return split_substrings;
}

#endif
