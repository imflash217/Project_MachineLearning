#include "header.h"
#include <cstddef>		// std::size_t
#include <cmath>		// log2()

// Functions

// Using the training data to segregate the {First Name, Middle Name, Last Name, <feature Vector>, Label}
void f_parseData(std::string& singleInstance, type_vvs& dataMatrix, int rowIndex, std::string& attrDelim){
	// parsing the training and test data as Vector<Vector>
	int attr_count = 0;
	type_vs tempStorage;				// storing the first/middle/last names
	std::string my_substring;
	
	std::size_t delimIndex = singleInstance.find_first_of(attrDelim);
	my_substring = singleInstance.substr(delimIndex+1, std::string::npos);
	// std::cout << delimIndex ;
	while(delimIndex != std::string::npos){
		attr_count += 1;
		// std::cout << delimIndex << ", " ;
		// std::cout << "[" << my_substring << "] ";
		delimIndex = my_substring.find_first_of(attrDelim);
		tempStorage.push_back(my_substring.substr(0, delimIndex));
		my_substring = my_substring.substr(delimIndex+1, std::string::npos);
		// std::cout << tempStorage[attr_count-1] << ", "  << std::endl;
	}
	// std::cout << " #" << attr_count << std::endl;
	// std::cout << std::endl;

	switch(attr_count){
		case 1:
			tempStorage.insert(tempStorage.begin(), singleInstance.substr(0,1));
			tempStorage.push_back("");		// for empty MiddleName
			tempStorage.push_back("");		// for empty LastName
			dataMatrix.push_back(tempStorage);
			break;
		case 2:
			tempStorage.insert(tempStorage.begin(), singleInstance.substr(0,1));
			tempStorage.insert(tempStorage.begin()+2, "");		// for empty MiddleName
			dataMatrix.push_back(tempStorage);
			break;
		case 3:
			tempStorage.insert(tempStorage.begin(), singleInstance.substr(0,1));
			dataMatrix.push_back(tempStorage);
			break;
		default:	// for (attr_count > 3)
			tempStorage.insert(tempStorage.begin(), singleInstance.substr(0,1));
			
			// creating the Full MiddleName
			for(int i = 3; i < tempStorage.size()-1; i++){
				tempStorage[2] += " " + tempStorage[i];
				i++;
			}

			tempStorage.erase(tempStorage.begin()+3, tempStorage.end()-1);
			dataMatrix.push_back(tempStorage);
			break;
	}

	// tempStorage[0] += tempStorage[2];
	// std::cout << "@@@@@@@@@@@@@@@@@" << tempStorage[0] << std::endl;
	/*
		std::cout << "****** " << dataMatrix[rowIndex][0] << ", "
								<< dataMatrix[rowIndex][1] << ", "
								<< dataMatrix[rowIndex][2] << ", "
								<< dataMatrix[rowIndex][3] << "\n" 
								<< std::endl;
	*/

}

void f_generateFeatureVector(type_vvs& X){

	/*
	 * Y =1, N = 0
	 * <X[i][4:9] = feature vector> :  <
	 *			X[i][4] = x0 = (firstName.size() > lastName.size() | Y/N), 
	 *			X[i][5] = x1 = (middleName != EMPTY | Y/N),
	 *			X[i][6] = x2 = (firstName[0] == firstName[firstName.length()-1] | Y/N),
	 *			X[i][7] = x3 = (firstName > lastName | Y/N),
	 *			X[i][8] = x4 = (firstName[1] == {a,e,i,o,u} | Y/N),
	 *			X[i][9] = x5 = (lastName.length() % 2 == 0 | Y/N) >
	 */

	// auto totalRows = X.size();
	// std::cout << totalRows << std::endl;

	for(auto& X_i : X){

		// calculating x0 = (firstName.size() > lastName.size() | Y/N)

		if(X_i[1].size() > X_i[3].size()){
			X_i.push_back("1");
			// std::cout << "greater" << X_i[4] << std::endl;
		}else{
			X_i.push_back("0");
			// std::cout << "smaller" << X_i[4] << std::endl;
		}

		// calculating x1 = (middleName != EMPTY | Y/N)

		if(X_i[2] == ""){
			X_i.push_back("0");			// don't have a middleName
		}else{
			X_i.push_back("1");			// have a middleName
		}

		// calculating x2 = (firstName[0] == firstName[firstName.length()-1] | Y/N)
		if(std::tolower((X_i[1][0]), std::locale()) == std::tolower((X_i[1][X_i[1].size()-1]), std::locale())){
			// std::cout << "wow!!!!!!!!!!!!!!!" << std::endl;
			X_i.push_back("1");
		}else{
			// std::cout << "Nope!!!!!!!!!!!!!!!" << std::endl;
			X_i.push_back("0");
		}

		// calculating x3 = (firstName > lastName | Y/N)
		auto firstName = X_i[1];
		auto lastName = X_i[3];

			// converting firstName & lastName into lowercase
		for(auto& itr : firstName){
			itr = std::tolower(itr, std::locale());
		}

		for(auto& itr : lastName){
			itr = std::tolower(itr, std::locale());
		}
			// comparing the firstName and lastName
		if(firstName.compare(lastName) < 0){
			// firstName comes alphabetically before lastName
			X_i.push_back("1");
		}else{
			// firstName comes alphabetically after lastName
			X_i.push_back("0");
		}
		// std::cout << firstName.compare(lastName) << " : " << firstName << " : " << lastName << "//////////////////" << std::endl;
		// std::cout << firstName << "//////////////////" << std::endl;
		// std::cout << X_i[1] << "//////////////////" << std::endl;

		// calculating x4 = (firstName[1] == {a,e,i,o,u} | Y/N)
		std::string vowels = "aeiou";
		if(vowels.find_first_of(firstName[1]) == std::string::npos){
			X_i.push_back("0");			// 2nd letter of firstName NOT a vowel
			// std::cout << "ohNo~~~" ;
		}else{
			X_i.push_back("1");			// 2nd letter of firstName IS a vowel
			// std::cout << "yup~~~";
		}

		// calculating x5 = (lastName.length() % 2 == 0 | Y/N)

		if(X_i[3].size() % 2 == 0){
			X_i.push_back("1");			// size of lastName is EVEN
		}else{
			X_i.push_back("0");			// size of lastName is ODD
		}

		/*
			std::cout << X_i[0] << " | " 
					<< X_i[1] << ", " << X_i[2] << ", " << X_i[3] << " | "
					<< X_i[4] << " | "
					<< X_i[5] << " | "
					<< X_i[6] << " | "
					<< X_i[7] << " | "
					<< X_i[8] << " | "
					<< X_i[9] << " | "
					<< std::endl;
		*/
	}

}

// print the post-processed data table(input, feature vector, labels)
void f_printDataTable(type_vvs& inputTable){
	for(auto itr : inputTable){
		for(auto x : itr){
			std::cout << x << " | ";
		}
		std::cout << std::endl;
	}
}

// calculating the entropy for each node
void f_calculateEntropy(Node* my_Node){
	
	double &entropy = my_Node->entropy;
	type_vvs &labelCounts = my_Node->classifiedLabelCounts;
	auto &totalCount = my_Node->totalCount;			// total no of instances that are input for this node
	// type_vi countArray;				// stores the counts (int) for each label at this node 

	for(auto itrLabel : labelCounts){
		double cnt = std::stoi(itrLabel[1]);
		entropy -= (cnt/totalCount) * log2(cnt/totalCount);
		std::cout << "entropy += " << entropy << std::endl;

		// int itrCount = std::stoi(itrLabel[1]);
		// countArray.push_back(itrCount);
		// totalInstances += itrCount;
		// std::cout << itrCount << "*/*/*" << totalInstances << std::endl;
	}
	// for(auto cnt : countArray){
	// 	// H(S) = - sum(p_i * log2(p_i));
	// 	// std::cout << cnt/totalInstances << std::endl;
	// 	// entropy -= ((double)cnt/totalInstances) * log2((double)cnt/totalInstances);
	// 	// std::cout << "entropy = " << entropy << std::endl;
	// }
}


// calculate the classified label counts
void f_countClassifiedLabels(Node* node, type_vvs &X){
	// std::cout << node->totalCount << "###############" << std::endl;
	type_vi temp_countArray;
	for(int i = 0; i < node->sampleIndices.size(); i++){

		if(node->sampleIndices.size() == 0){
			// std::cout << "node->sampleIndices.size() = " << node->sampleIndices.size() << std::endl;
			break;
		}


		// std::cout << "a###############" << node->classifiedLabelCounts.size()<< std::endl;
		bool newLabel = true;
		for(int j = 0; j < node->classifiedLabelCounts.size(); j++){
			// std::cout << "b###############" << std::endl;
			if(node->classifiedLabelCounts[j][0] == X[i][0]){
				// std::cout << "c###############" << temp_countArray[j] << std::endl;
				temp_countArray[j]++;
				// std::cout << "c1###############" << std::endl;
				newLabel = false;
				// std::cout << "c2###############" << std::endl;
				// break;
			}
		}
		// std::cout << "d###############" << std::endl;

		if(newLabel){		// if a new label is encountered
			// std::cout << "e###############" << std::endl;
			temp_countArray.push_back(1);	// creates a new holder for a new label
			type_vs temp = {X[i][0], "1"};
			(node->classifiedLabelCounts).push_back(temp);
			// std::cout << "f###############" << std::endl;
		}
	}
	node->totalCount = node->sampleIndices.size();
	// std::cout << node->totalCount << "############### done" << std::endl;

	int temp_maxCount = 0;
	int temp_maxCountIndex = 0;

	for(int i = 0; i < node->classifiedLabelCounts.size(); i++){

		if(node->totalCount == 0){
			std::cout << "zznode->totalCount = " << node->totalCount << std::endl;
			break;
		}
		// totalCount += labelCountArray[i];
		node->classifiedLabelCounts[i][1] = std::to_string(temp_countArray[i]);
		std::cout << node->classifiedLabelCounts[i][0] <<"(" << node->classifiedLabelCounts[i][1] << ")" << std::endl;
		// std::cout << totalCount<< std::endl;
		// std::cout << indicesArray.size()<< std::endl;

		if(temp_countArray[i] > temp_maxCount){
			temp_maxCount = temp_countArray[i];
			temp_maxCountIndex = i;
		}
	}

	if(node->totalCount != 0){
		node->label = &(node->classifiedLabelCounts[temp_maxCountIndex][0]);
		std::cout << "xxnode->totalCount = " << node->totalCount << std::endl;
		
		std::cout << *(node->label) << "[label with max classified samples @ this node]" << std::endl;

	}

}



// calculating the Information gain of a node wrt. its children
double f_calculateInformationGain(Node* node){
	double informationGain = node->entropy;

	std::cout << "## : " << node->children.size() << std::endl;

	for(int i = 0; i < node->children.size(); i++){
		informationGain += -((double) (node->children[i]->totalCount)/(node->totalCount))*((node->children[i])->entropy);
		std::cout << node->totalCount << "@#: " << informationGain << std::endl;
		
	}
	return informationGain;
}


// finding the right feature for a node and then creating its branches

void f_nodeBranching(Node* node, type_vvs &X, type_vvn &decisionTree){

	// feature selection
	type_vd temp_IGvec;
	type_vn temp_parent_vn;
	type_vvn temp_vvn;
	type_vvs temp_vvs;
	for(int i = 4; i < 10; i++){	// 4 to 9 are the indices of feature vectors in X[]
		std::cout << i << "-#a" << std::endl;
		type_vn temp_vn;		// to hold children of node
		type_vs temp_vs;		// to hold feature values

		std::cout << "#b" << std::endl;
		Node parentNode = *node;
		std::cout << "#c" << std::endl;
		temp_parent_vn.push_back(parentNode);

		temp_vs.push_back("0");
		temp_vs.push_back("1");
		temp_vvs.push_back(temp_vs);

		for(int j = 0; j < temp_vs.size(); j++){
			Node temp_node;					// children nodes
			temp_node.parent = &(*node);
			temp_node.parentValue = temp_vs[j];			// feature value for the parent's feature

			for(int k = 0; k < node->sampleIndices.size(); k++){
				if(temp_node.parentValue == X[k][i]){
					(temp_node.sampleIndices).push_back(k);
				}
			}

			f_countClassifiedLabels(&temp_node, X);
			f_calculateEntropy(&temp_node);
			temp_vn.push_back(temp_node);
			temp_parent_vn[i-4].children.push_back(&(temp_vn[j]));
		}

		std::cout << (temp_vn[0].isLeaf) << "/////////////////////////////////////" << std::endl;


		temp_vvn.push_back(temp_vn);

		temp_IGvec.push_back(f_calculateInformationGain(&(temp_parent_vn[i-4])));
		// std::cout << i << " -@@@@@@@@@@@@@- "<< f_calculateInformationGain(&(temp_parent_vn[i-4])) << "/*/*/*/*/*/*" << std::endl;

	}

	// finding the max IG & deciding the splitOn_feature, splitOn_feature_index
	std::cout << "\nIG for each feature : " << std::endl;
	double max_IG = -INFINITE_DOUBLE;
	for(int t = 0; t < temp_IGvec.size(); t++){
		if(temp_IGvec[t] > max_IG){
			max_IG = temp_IGvec[t];
			node->splitOn_feature = std::to_string(t);
			node->splitOn_feature_index = t;
		}
		std::cout << temp_IGvec[t] << ", ";
	}

	std::cout << "\nmax_IG = " << max_IG 
				<< " & splitOn_feature : " << node->splitOn_feature 
				<< std::endl;

		std::cout << "$$$$: decisionTree.size(): " << decisionTree.size() << std::endl;
	if((decisionTree.size() - 1) == node->treeLevel){
		std::cout << "$$$$: treeLevel_node : " << node->treeLevel << std::endl;
		// create a type_vn and insert all children into it and then push that into DT
		decisionTree.push_back(temp_vvn[node->splitOn_feature_index]);
		
		for(auto u = 0; u < decisionTree[decisionTree.size() - 1].size(); u++){

			if(decisionTree[decisionTree.size() - 1][u].entropy == 0.0){
				decisionTree[decisionTree.size() - 1][u].isLeaf = true;
				decisionTree[decisionTree.size() - 1][u].treeLevel = decisionTree[decisionTree.size() - 1][u].parent->treeLevel + 1;
				
				std::cout << "$$$$: isLeaf_if: " << decisionTree[decisionTree.size() - 1][u].isLeaf << std::endl;
				std::cout << "$$$$: treeLevel_if: " << decisionTree[decisionTree.size() - 1][u].treeLevel << std::endl;

			}else{
				decisionTree[decisionTree.size() - 1][u].isLeaf = false;
				decisionTree[decisionTree.size() - 1][u].treeLevel = decisionTree[decisionTree.size() - 1][u].parent->treeLevel + 1;

				std::cout << "$$$$: isLeaf_else: " << decisionTree[decisionTree.size() - 1][u].isLeaf << std::endl;
				std::cout << "$$$$: treeLevel_else: " << decisionTree[decisionTree.size() - 1][u].treeLevel << std::endl;

			}

			node->children.push_back(&(decisionTree[decisionTree.size() - 1][u]));
		}
	}else if((decisionTree.size() - 2) == node->treeLevel){
		auto DT_lastRow_size = decisionTree[decisionTree.size() - 1].size();
		auto temp_size = temp_vvn[node->splitOn_feature_index].size();
		for(auto v = DT_lastRow_size; v < (DT_lastRow_size + temp_size); v++){
			
			decisionTree[decisionTree.size() - 1].push_back(temp_vvn[node->splitOn_feature_index][v - DT_lastRow_size]);
			node->children.push_back(&(decisionTree[decisionTree.size() - 1][v]));
			
			if(decisionTree[decisionTree.size() - 1][v].entropy == 0.0){
				decisionTree[decisionTree.size() - 1][v].isLeaf = true;
				decisionTree[decisionTree.size() - 1][v].treeLevel = decisionTree[decisionTree.size() - 1][v].parent->treeLevel + 1;
				std::cout << "$$$$: isLeaf_elseif_if: " << decisionTree[decisionTree.size() - 1][v].isLeaf << std::endl;
				std::cout << "$$$$: treeLevel_elseif_if: " << decisionTree[decisionTree.size() - 1][v].treeLevel << std::endl;
				// std::cout << "$$$$: treeLevel_elseif_if: ";
				
			}else{
				decisionTree[decisionTree.size() - 1][v].isLeaf = false;
				decisionTree[decisionTree.size() - 1][v].treeLevel = decisionTree[decisionTree.size() - 1][v].parent->treeLevel + 1;
				std::cout << "$$$$: isLeaf_elseif_else: " << decisionTree[decisionTree.size() - 1][v].isLeaf << std::endl;
				std::cout << "$$$$: treeLevel_elseif_else: " << decisionTree[decisionTree.size() - 1][v].treeLevel << std::endl;

			}
		}
	}
}


// create nodes for the Decision Tree
void f_generateDecisionTree(type_vvs &X, type_vvn &decisionTree){

	// <featureVector> = <X_i[4]...., X_i[9]>

	// type_vvn decisionTree;		// a 2D matrix of nodes, each row is level in DT
	std::cout << "DT.size() = " << decisionTree.size() << std::endl;

	if(decisionTree.size() == 0){

		// create a root node
		// type_vn level0;
		Node rootNode;						// creating a root node: default initialized
		// level0.push_back(rootNode);
		// decisionTree.push_back(level0);
		std::cout << "DT.size() = " << decisionTree.size() << std::endl;

		rootNode.parent = nullptr;	// setting the parent of rootNode as NULL

		for (int i = 0; i < X.size(); i++){
			rootNode.sampleIndices.push_back(i);
		}

		if(rootNode.sampleIndices.size() != 0){

			// this is a one-time process for root node
			f_countClassifiedLabels(&rootNode, X);
			f_calculateEntropy(&rootNode);

			// pushing the root node into decisionTree array
			type_vn level0;
			level0.push_back(rootNode);
			std::cout << "**********1" << std::endl;

			decisionTree.push_back(level0);
			std::cout << "**********2" << std::endl;

			// 1st iteration: branching the root node and adding children into another level
			f_nodeBranching(&(decisionTree[decisionTree.size()-1][0]), X, decisionTree);				// this will set the splitOn feature, set children , isLeaf, label
			std::cout << decisionTree[decisionTree.size()-2][0].children.size() << "x----------" << std::endl;
			// std::cout << "rootNode.children.size() : " << rootNode.children.size() << std::endl;

			std::cout << rootNode.entropy << "  ~~~~~  "
						<< f_calculateInformationGain(&rootNode) 
						<< std::endl;

			std::cout << rootNode.nodeID << ", " 
					<< rootNode.parentValue << ", " 
					<< rootNode.splitOn_feature << ", "
					<< rootNode.isLeaf << ", " 
					<< rootNode.label << ", " 
					<< rootNode.totalCount << ", " 
					<< rootNode.entropy
					<< std::endl;


			// for(int u = 0; u < rootNode.children.size(); u++){
			// 	std::cout << "**********3" << std::endl;
			// 	// childLevel.push_back(*rootNode.children[u]);
			// 	std::cout << "**********4" << std::endl;
			// 	// std::cout << ((rootNode.children[u])->label) << std::endl;
			// }

			// decisionTree.push_back(childLevel);

			std::cout << "before" << std::endl;
			f_generateDecisionTree(X, decisionTree);
			std::cout << "after" << std::endl;
		}else{
			std::cerr << "The input data is empty" << std::endl;
		}

	}else{

		// std::cout << decisionTree[0][0].children.size() << "vinay" << std::endl;
		// std::cout << std::to_string(*(decisionTree[1][1]->label)) << std::endl;
		// std::cout << decisionTree[1].size() << std::endl;
		// std::cout << "vinay_decisionTree.size(): " << decisionTree.size() << std::endl;

		bool DT_finished = false;
		while(DT_finished == false){
			bool temp_levelController = true;

			// type_vn temp_vn;
			auto treeSize = decisionTree.size();
			auto opLevelSize = decisionTree[treeSize - 1].size();

			// Breadth First Search Implementation
			for(int j = 0; j < opLevelSize ; j++){

				// std::cout << "..........................." << std::endl;
				auto &activeNode = decisionTree[treeSize - 1][j];
				// std::cout << "x..........................." << j << std::endl;

				if(decisionTree[treeSize - 1][j].entropy != 0.0){
					f_nodeBranching(&(decisionTree[treeSize - 1][j]), X, decisionTree);
				}
			}
			
			// double temp_netEntropy = 0.0;
			for(auto itr : decisionTree[decisionTree.size() - 1]){
				temp_levelController *= itr.isLeaf;
				// temp_netEntropy += itr.entropy;
				// std::cout << itr.isLeaf << " netEntropy : " << temp_netEntropy  <<", " << decisionTree[decisionTree.size() - 1].size() << std::endl;
			}

			if(temp_levelController == true){
				DT_finished = true;
				// std::cout << "Harry Potter*-------------------*-*-*-*--*-*--*-*" << std::endl;
				// f_generateDecisionTree(X, decisionTree);
			}
			
			std::cout << "Harry Potter*-------------------*-*-*-*--*-*--*-*" << std::endl;
			// f_generateDecisionTree(X, decisionTree);
		}



	}

	std::cout << "xxxxxxxxxxxxxxDT.size() = " << decisionTree.size() << std::endl;

}



int main(int argc, char const *argv[])
{
	// parsing the training and test data as Vector<Vector>
	std::string my_attrDelim = " ";
	std::string singleDataInstance;
	std::ifstream trainFile;
	std::ifstream testFile;
	type_vvs trainDataTable;
	type_vvs testDataTable;
	int noOfTrainSamples = 0;
	int noOfTestSamples = 0;

	// pruning training Data
	trainFile.open(argv[1]);
	if(!trainFile){
		std::cerr << "ERROR: The input training data file is Empty!! Exiting the code." << std::endl;
		return(-1);
	}
	while(std::getline(trainFile, singleDataInstance)){
		// std::cout << singleDataInstance << std::endl;
		f_parseData(singleDataInstance, trainDataTable, noOfTrainSamples, my_attrDelim);
		noOfTrainSamples++;
	}
	trainFile.close();

	// pruning test data
	testFile.open(argv[2]);
	if(!testFile){
		std::cerr << "WARINING: The 'test data' is empty!!! Exiting the code." << std::endl;
		return(0);		// successfully built the tree but failed to evaluate on NULL test data
	}
	while(std::getline(testFile, singleDataInstance)){
		// std::cout << singleDataInstance << std::endl;
		f_parseData(singleDataInstance, testDataTable, noOfTestSamples, my_attrDelim);
		noOfTestSamples++;
		// std::cout << singleDataInstance[0] << std::endl;
		// std::cout << singleDataInstance.find_first_of(" ") << std::endl;

	}

	// // std::cout << trainDataTable[0][0] << std::endl;
	// std::cout << noOfTrainSamples << ", " << noOfTestSamples << std::endl;
	std::cout << trainDataTable.size() << ", " << testDataTable.size() << std::endl;

	// Generating the feature vector for each instance training and test data
	f_generateFeatureVector(trainDataTable);
	f_generateFeatureVector(testDataTable);

	// f_printDataTable(trainDataTable);

	// f_printDataTable(testDataTable);

	// Decision Tree generation
	type_vvn decisionTree;
	f_generateDecisionTree(trainDataTable, decisionTree);
	// f_generateDecisionTree(testDataTable, test_decisionTree);


}









