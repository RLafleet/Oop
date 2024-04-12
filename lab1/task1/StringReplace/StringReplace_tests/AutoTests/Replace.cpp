#include "Replace.h"

std::string Replace(std::string str, const std::string& strToFind, const std::string& strToChange) {
    if (str.empty() || strToFind.empty() || strToChange.empty()) {
        return str;
    }

    size_t foundPosition = str.find(strToFind);
    while (foundPosition != std::string::npos) {
        str.replace(foundPosition, strToFind.length(), strToChange);
        foundPosition = str.find(strToFind, foundPosition + strToChange.length());
    }
    return str;
}
