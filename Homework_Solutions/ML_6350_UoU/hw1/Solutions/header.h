// header file for the Decision Tree algorithm

#include <iostream>		// std::cout, std::endl
#include <string>		// std::string
#include <vector>		// std::vector
#include <fstream>		// std::ifstream,
#include <cstddef>		// std::size_t 

typedef std::vector<std::string> type_vs;
typedef std::vector<type_vs> type_vvs;
typedef std::vector<int> type_vi;

class node{
public:
	std::string nodeID;
	node* parentNode;								// parent node
	std::string parentValue;						// The value of the parent node of which this node is a child
	std::string splitOn_feature;					// feature on which the node is split
	std::vector<std::string> feature_values;		// values that the node's feature can take
	bool isLeaf;									// if the node is a leaf node then TRUE else FALSE
	std::string label;								// The LABEL if the node isLeaf
	type_vvs classifiedLabelsCount;					// count of each classified labels input to the node
	double nodeEntropy;								// entropy of the node
	std::vector<node*> children;					// the children nodes
}

void f_parseData(std::string&, type_vvs&, int, std::string&);
void f_generateFeatureVector(type_vvs&);
void f_printDataTable(type_vvs&);
void f_calculateEntropy(node*);






