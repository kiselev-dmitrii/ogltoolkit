#include "StringUtils.h"
#include <sstream>
#include "../Debug/Debug.h"

vector<string> StringUtils::split(const string &str, char delim) {
        vector<string> result;

        istringstream stream(str);
        string elem;
        while(getline(stream, elem, delim)) {
                result.push_back(elem);
        }

        return result;
}

template <typename NumType>
NumType StringUtils::strToNum(const string &str) {
        NumType result;

        istringstream stream(str);

        try {
                stream >> result;
        } catch (...) {
                DEBUG("Cannot convert string " << str << " to float");
        }

        return result;
}
