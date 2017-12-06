// header file for the Decision Tree algorithm

#include <iostream>		// std::cout, std::endl
#include <string>		// std::string
#include <vector>		// std::vector
#include <fstream>		// std::ifstream,
#include <cstddef>		// std::size_t 

typedef std::vector<std::string> type_vs;
typedef std::vector<type_vs> type_vvs;
typedef std::vector<int> type_vi;

void f_parseData(std::string&, type_vvs&, int, std::string&);
void f_generateFeatureVector(type_vvs&);
void f_printDataTable(type_vvs&);