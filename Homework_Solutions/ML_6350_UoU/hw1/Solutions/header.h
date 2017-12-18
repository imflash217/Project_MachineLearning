// header file for the Decision Tree algorithm

#include <iostream>		// std::cout, std::endl
#include <string>		// std::string
#include <vector>		// std::vector
#include <fstream>		// std::ifstream,
#include <cstddef>		// std::size_t 

typedef std::vector<std::string> type_vs;
typedef std::vector<type_vs> type_vvs;
typedef std::vector<int> type_vi;
typedef std::vector<double> type_vd;

class Node{
public:
	Node() = default;						// default constructor

	std::string nodeID;
	Node* parent;						// parent node
	std::string parentValue;				// The value of the parent node of which this node is a child
	std::string splitOn_feature;			// feature on which the node is split
	type_vs feature_values;					// values that the node's feature can take
	bool isLeaf;							// if the node is a leaf node then TRUE else FALSE
	std::string label;						// The LABEL if the node isLeaf
	type_vi sampleIndices;					// indices of the samples(subset of the train/test data) that are input to the node
	type_vvs classifiedLabelCounts;			// count of each classified labels input to the node
	unsigned int totalCount = 0;							// total number of labelled examples for the node
	double entropy = 0.0;							// entropy of the node
	std::vector<Node*> children;			// the children nodes
};

typedef std::vector<Node> type_vn;
typedef std::vector<type_vn> type_vvn;

void f_parseData(std::string&, type_vvs&, int, std::string&);
void f_generateFeatureVector(type_vvs&);
void f_printDataTable(type_vvs&);
void f_calculateEntropy(Node*);
void f_countClassifiedLabels(Node*, type_vvs&);
double f_calculateInformationGain(Node*);
void f_nodeBranching(Node*, type_vvs&);






