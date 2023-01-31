#include "functions.hpp"

#include <iostream>
#include <string>
#include <vector>

int FIND(const std::string& dna, const std::string& subdna) {
    int returnit = 0;
    int count = 0;
    for (size_t i = 0; i < (dna.length() - subdna.length() + 1); i++) {
        if (dna.substr(i, subdna.length()) == subdna) {
            count++;
            if (count > returnit) {
                returnit = count;
            }
            i += subdna.length() - 1;
        } else {
            count = 0;
        }
    }
    return returnit;
}

std::string RESULT(const std::string& dnaline, std::vector<std::string> filebyline) {
    std::vector<std::string> requirement;   //"ATTA,TATA,TATC"
    std::vector<std::string> name_and_num;  // Casey,5,2,8
    std::vector<int> sequence;              //“2,3,1“
    for (size_t s = 1; s < (utilities::GetSubstrs(filebyline[0], ',')).size(); s++) {
        requirement.push_back(utilities::GetSubstrs(filebyline[0], ',')[s]);
    }
    for (size_t i = 1; i < filebyline.size(); i++) {
        for (size_t j = 0; j < (utilities::GetSubstrs(filebyline[i], ',')).size(); j++) {
            name_and_num.push_back(utilities::GetSubstrs(filebyline[i], ',')[j]);
        }
    }
    for (size_t j = 0; j < requirement.size(); j++) {
        int result = FIND(dnaline, requirement[j]);
        sequence.push_back(result);
    }
    for (size_t i = 0; i < name_and_num.size() - 3; i += 4) {
        int match = 0;
        if (sequence[0] == std::stoi(name_and_num[i + 1])) {
            match++;
        }
        if (sequence[1] == std::stoi(name_and_num[i + 2])) {
            match++;
        }
        if (sequence[2] == std::stoi(name_and_num[i + 3])) {
            match++;
        }
        if (match == 3) {
            return name_and_num[i];
            match = 0;
        }
    }
    return "No MATCH";
}