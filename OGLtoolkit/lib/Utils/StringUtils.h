#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>
#include <vector>

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
}

#endif // STRINGUTILS_H
