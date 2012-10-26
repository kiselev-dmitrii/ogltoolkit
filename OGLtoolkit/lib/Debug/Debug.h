#ifndef DEBUG_H
#define DEBUG_H
#include <iostream>
#include "lib/Utils/StreamUtils.h"

using namespace StreamUtils;

#define SHOW(variable)  std::cout << #variable" = " << variable << std::endl;
#define DEBUG(text)     std::cout << text << std::endl;
#define TRACE(text)     std::cout << text << " in" << __FUNCTION__ << ", line " << __LINE__ << ", file" << __FILE__ << std::endl;
#define TODO            std::cout << "Function " << __FUNCTION__ << " is not implemented in " << __FILE__ << " in line " << __LINE__ << std::endl;

#endif // DEBUG_H
