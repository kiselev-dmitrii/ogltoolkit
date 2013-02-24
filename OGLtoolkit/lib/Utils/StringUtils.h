#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>
#include <vector>
#include <sstream>
#include "lib/Utils/Debug.h"

using std::string;
using std::vector;
using namespace std;

/** Утилиты, для работы со строками
  */
namespace StringUtils {
        // Разбивает строку на подстроки, разделенные символом delim
        vector<string>  split(const string &str, char delim);

        // Конвертирует строку в число типа NumType
        template <typename NumType>
        NumType         strToNum(const string &str);

        // Конвертирует число в строку
        template <typename NumType>
        string          numToStr(NumType num);
}

/*******************************************************************************************/
/** Реализация шаблонных функций */

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

template <typename NumType>
string StringUtils::numToStr(NumType num) {
        string result;
        stringstream stream;

        stream << num;
        stream >> result;
        return result;
}

#endif // STRINGUTILS_H
