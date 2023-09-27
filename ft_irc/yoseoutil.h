#ifndef YOSEO_UTIL_H
#define YOSEO_UTIL_H

#include <string>
#include <vector>

void splitString(const std::string& param, char op, std::vector<std::string>* out);
bool _isValidNickname(const std::string& selectName);
int _isspecial(char c);

#endif


