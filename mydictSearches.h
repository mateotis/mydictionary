#include <iostream>
#include <string>
#include <vector>

void fullwordSearch(std::vector<std::string>, int, int, std::string);
void prefixSearch(std::vector<std::string>, int, int, std::string, int, int);
void wildcardSearch(std::vector<std::string>, int, int, std::string, int, std::string::size_type, int);