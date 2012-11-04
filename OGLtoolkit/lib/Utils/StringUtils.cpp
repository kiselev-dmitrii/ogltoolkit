#include "StringUtils.h"
#include <sstream>

vector<string> StringUtils::split(const string &str, char delim) {
        vector<string> result;

        istringstream stream(str);
        string elem;
        while(getline(stream, elem, delim)) {
                result.push_back(elem);
        }

        return result;
}

