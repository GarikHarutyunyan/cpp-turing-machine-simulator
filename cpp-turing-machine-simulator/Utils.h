#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace Utils {
	std::string to_unary(int);
	int to_int(std::string);
	std::string remove_spaces(std::string);
};

#endif // UTILS_H