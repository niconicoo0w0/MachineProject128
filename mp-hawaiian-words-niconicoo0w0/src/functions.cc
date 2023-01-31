#include <iostream>
#include <string>
#include <vector>


std::string returnit;

bool NOTHA(std::string word) {
    bool notha = false;
    for (size_t k = 0; k < word.length(); ++k) {
        if (std::tolower(word[k]) == 'z' || std::tolower(word[k]) == 'd') {
            notha = true;
        }
    }
    return notha;
}

bool AADD (std::string word, int i) {
    bool add = false;
    if (std::tolower(word[i + 1]) == 'i' || std::tolower(word[i + 1]) == 'e' || std::tolower(word[i + 1]) == 'o' || std::tolower(word[i + 1]) == 'u') {
        add = true;
    }
    return add;
}

bool EADD (std::string word, int i) {
    bool add = false;
    if (std::tolower(word[i + 1]) == 'i' || std::tolower(word[i + 1]) == 'u') {
        add = true;
    }
    return add;
}

bool IADD (std::string word, int i) {
    bool add = false;
    if (std::tolower(word[i + 1]) == 'u') {
        add = true;
    }
    return add;
}

bool OADD (std::string word, int i) {
    bool add = false;
    if (std::tolower(word[i + 1]) == 'i'|| std::tolower(word[i + 1]) == 'u') {
        add = true;
    }
    return add;
}

bool UADD (std::string word, int i) {
    bool add = false;
    if (std::tolower(word[i + 1]) == 'i') {
        add = true;
    }
    return add;
}

std::string A (std::string word, int placeofa) {
    if (std::tolower(word[placeofa + 1]) == 'i' ||std::tolower(word[placeofa + 1]) == 'e') {
        returnit.append("eye-");
    } else if (std::tolower(word[placeofa + 1]) == 'u' || std::tolower(word[placeofa + 1]) == 'o') {
        returnit.append("ow-");
    } else {
        returnit.append("ah-");
    }
    return returnit;
}

std::string E (std::string word, int placeofe) {
    if (std::tolower(word[placeofe + 1]) == 'i') {
        returnit.append("ay-");
    } else if (std::tolower(word[placeofe + 1]) == 'u') {
        returnit.append("eh-oo-");
    } else {
        returnit.append("eh-");
    }
    return returnit;
}

std::string I (std::string word, int placeofi) {
    if (std::tolower(word[placeofi + 1]) == 'u') {
        returnit.append("ew-");
    } else {
        returnit.append("ee-");
    }
    return returnit;
}

std::string O (std::string word, int placeofo) {
    if (std::tolower(word[placeofo + 1]) == 'i') {
        returnit.append("oy-");
    } else if (std::tolower(word[placeofo + 1]) == 'u') {
        returnit.append("ow-");
    } else {
        returnit.append("oh-");
    }
    return returnit;
}

std::string W (std::string word) {
    int placefw = word.find('w');
    if (std::tolower(word[placefw - 1]) == 'i' || std::tolower(word[placefw - 1]) == 'e') {
        returnit.push_back('v');
    } else {
        returnit.push_back('w');
    }
    return returnit;
}

std::string U (std::string word, int placeofu) {
    if (std::tolower(word[placeofu + 1]) == 'i') {
        returnit.append("ooey-");
    } else {
        returnit.append("oo-");
    }
    return returnit;
}

std::string TRANSLATE(std::string word) {
    if (!NOTHA(word)) {
        for (size_t i = 0; i < word.length(); ++i) {
            if (std::tolower(word[i]) != 'l' && std::tolower(word[i]) != 'h' && std::tolower(word[i]) != 'p' && std::tolower(word[i]) != 'k' && std::tolower(word[i]) != 'm' && std::tolower(word[i]) != 'n' && std::tolower(word[i]) != 'w') {
                if (std::tolower(word[i]) == 'a') {
                    A(word, i);
                    AADD(word, i) ? i += 1 : i;
                } else if (std::tolower(word[i]) == 'e') {
                    E (word, i);
                    EADD(word, i) ? i += 1 : i;
                } else if (std::tolower(word[i]) == 'i') {
                    I (word, i);
                    IADD(word, i) ? i += 1 : i;
                } else if (std::tolower(word[i]) == 'o') {
                    O (word, i);
                    OADD(word, i) ? i += 1 : i;
                } else if (std::tolower(word[i]) == 'u') {
                    U (word, i);
                    UADD(word, i) ? i += 1 : i;
                } else if (word[i] == ' ' || word[i] == '!' || word[i] == '?' || word[i] == '.' || word[i] == '\'') {
                    returnit.push_back(word[i]);
                    if (returnit[returnit.length() - 2] == '-') {
                        returnit.erase(returnit.length() - 2, 1);
                    }
                }
            } else if (std::tolower(word[i]) == 'w'){
                W(word);
            } else {
                returnit.push_back(std::tolower(word[i]));
            }
        }
        if (returnit[returnit.length() - 1] == '-') {
            returnit.erase(returnit.length() - 1 , returnit.length() - 2);
        }
    } else {
        return "contains a character not a part of the Hawaiian language.";
    }
    return returnit;
}

int main()
{
    std::cout << TRANSLATE("stupid") << std::endl; //ah-wah-keh-ah
    // std::cout << TRANSLATE("Aloha awakea") << std::endl; //aj-loh-hah ah-wah-keh-ah
    // std::cout << TRANSLATE("alOHA") << std::endl; //ah-loh-hah
}