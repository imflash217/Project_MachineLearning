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
	int &totalCount = my_Node->totalCount;			// total no of instances that are input for this node
	type_vi countArray;				// stores the counts (int) for each label at this node 

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

// create nodes for the Decision Tree

void f_generateDecisionTree(type_vvs &X, type_vvn &decisionTree){

	// <featureVector> = <X_i[4]...., X_i[9]>

	// type_vvn decisionTree;		// a 2D matrix of nodes, each row is level in DT
	std::cout << "DT.size() = " << decisionTree.size() << std::endl;

	if(decisionTree.size() == 0){
		// create a root node
		// create nodes *********************************

		type_vn level0;
		Node rootNode;				// creating a root node: default initialized
		level0.push_back(rootNode);
		decisionTree.push_back(level0);
		std::cout << "DT.size() = " << decisionTree.size() << std::endl;

		rootNode.parent = nullptr;	// setting the parent of rootNode as NULL

		// check if the decisionTree is empty...if YES, then calculate the Global Entropy H_S
		auto &H_S = rootNode.entropy;
		auto &indicesArray = rootNode.sampleIndices;
		auto &classifiedLabelCounts = rootNode.classifiedLabelCounts;
		auto &totalCount = rootNode.totalCount;
		type_vi labelCountArray;

		for (int i = 0; i < X.size(); i++){
			indicesArray.push_back(i);
		}

		std::cout << "rus" << indicesArray[0] << std::endl;

		for (int i = 0; i < indicesArray.size(); i++){
			// counting the total no samples for each label
			bool newLabelFound = true;
			for(int j = 0; j < classifiedLabelCounts.size(); j++){
				if(classifiedLabelCounts[j][0] == X[i][0]){
					labelCountArray[j]++;
					newLabelFound = false;
					// std::cout << "rusX" << labelCountArray[j] << std::endl;
					break;
				}
			}
			// std::cout << "rusPot" << newLabelFound << i << std::endl;

			if(newLabelFound){
				type_vs temp = {X[i][0], "1"};	// when encountering a new label
				classifiedLabelCounts.push_back(temp);
				labelCountArray.push_back(1);			// created a new holder for a new label
			}
		}

		for(int i = 0; i < classifiedLabelCounts.size(); i++){
			totalCount += labelCountArray[i];
			classifiedLabelCounts[i][1] = std::to_string(labelCountArray[i]);
			// std::cout << classifiedLabelCounts[i][0] <<"(" << classifiedLabelCounts[i][1] << ")" << std::endl;
		}

		f_calculateEntropy(&rootNode);
		std::cout << H_S << "  $$$$  " << totalCount << std::endl;

		std::cout << rootNode.nodeID << ", " 
				<< rootNode.parentValue << ", " 
				<< rootNode.splitOn_feature << ", "
				<< rootNode.isLeaf << ", " 
				<< rootNode.label << ", " 
				<< rootNode.totalCount << ", " 
				<< rootNode.entropy << ", " 
				<< std::endl;

		/*
			// pick a splitOn_feature
				for (i : X[4] to X[9]){
					rootNode.splitOn_feature = i;
					rootNode.feature_values.push_back('0');
					rootNode.feature_values.push_back('1');
					// create level;
					create nodes;
					for(int j = 0; j < nodes.size(); j++){
						nodes[j].parent = rootNode;
						nodes[j].parentValue = rootNode.feature_values[j];
					}



				}

			// find the children of the node
					// find their entropies


			// find the Information Gain

			// finalize the splitOn_feature

		*/





	}else{
		std::cout << decisionTree[0][1].entropy << std::endl;
		
	}

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


}









