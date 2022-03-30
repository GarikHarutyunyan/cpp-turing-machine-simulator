#include "Utils.h"
#include <string>
#include <fstream>

int Utils::to_int(std::string unaryValue) {
	for (int i = 0; i < unaryValue.length(); i++) {
		if (unaryValue[i] != '1') {
			throw std::invalid_argument("Unary number must contain only '1' symbol. '" + std::string(1,unaryValue[i]) +"' is not equal to 1.");
		}
	}

	return unaryValue.length() - 1;
}

std::string Utils::to_unary(int value) {
	if (value<0) {
		throw std::invalid_argument("Negative numbers can't be presented as unary numbers");
	}

	return std::string(value+1,'1');
}

std::string Utils::remove_spaces(std::string str) {
	str.erase(remove(str.begin(), str.end(), ' '), str.end());

	return str;
}