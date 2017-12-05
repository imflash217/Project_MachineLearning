#include "header.h"
#include <cstddef>		// std::size_t

// Functions

// Using the training data to segregate the {First Name, Middle Name, Last Name, <feature Vector>, Label}
void f_parseData(std::string& singleInstance, type_vvs& dataMatrix, int rowIndex, std::string& attrDelim){
	// parsing the training and test data as Vector<Vector>
	int attr_count = 0;
	type_vs tempStorage;				// storing the first/middle/last names
	type_vi tempIndex;					// storing the indices of the delim in each substrings
	std::string my_substring;
	// auto itr = tempStorage.begin();
	int x =1;
	// std::string tempSubsubstring;
	
	std::size_t delimIndex = singleInstance.find_first_of(attrDelim);
	my_substring = singleInstance.substr(delimIndex+1, std::string::npos);
	// std::cout << delimIndex ;
	while(delimIndex != std::string::npos){
		attr_count += 1;
		std::cout << delimIndex << ", " ;
		// std::cout << "[" << my_substring << "] ";
		delimIndex = my_substring.find_first_of(attrDelim);
		// tempSubsubstring = my_substring.substr(0, delimIndex);
		tempStorage.push_back(my_substring.substr(0, delimIndex));
		my_substring = my_substring.substr(delimIndex+1, std::string::npos);
		std::cout << tempStorage[attr_count-1] << ", "  << std::endl;
	}
	std::cout << " #" << attr_count << std::endl;
	std::cout << std::endl;

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
			for(int i = 3; i < tempStorage.size()-1; i++){
				// tempStorage[tempStorage.begin()+1] += " ";
				tempStorage[2] += " " + tempStorage[i];
				i++;
			}
			tempStorage.erase(tempStorage.begin()+3, tempStorage.end()-1);
			dataMatrix.push_back(tempStorage);
			break;
	}

	// tempStorage[0] += tempStorage[2];

	// std::cout << "@@@@@@@@@@@@@@@@@" << tempStorage[0] << std::endl;

	std::cout << "****** " << dataMatrix[rowIndex][0] << ", "
							<< dataMatrix[rowIndex][1] << ", "
							<< dataMatrix[rowIndex][2] << ", "
							<< dataMatrix[rowIndex][3] << "\n" << std::endl;
							// << dataMatrix[rowIndex][2] << std::endl;

	// filling the data Matrix with the attributes
	/*
	 * <feature vector> :  <(firstName > lastName | Y/N), 
	 *						(middleName == EMPTY | Y/N),
	 *						(firstName[0] == firstName[firstName.length()-1] | Y/N),
	 *						(firstName > lastName | Y/N),
	 *						(firstName[1] == {a,e,i,o,u} | Y/N),
	 *						(lastName.length() % 2 == 0 | Y/N)>
	 */
	
}



int main(int argc, char const *argv[])
{
	// parsing the training and test data as Vector<Vector>
	std::string my_attrDelim = " ";
	std::string singleDataInstance;
	std::ifstream trainDataFile;
	std::ifstream testDataFile;
	type_vvs trainDataTable;
	type_vvs testDataTable;
	int noOfTrainSamples = 0;
	int noOfTestSamples = 0;

	// take the 1st argument while running the executable and parse the train/test data stored in it
	
	// pruning training Data
	trainDataFile.open(argv[1]);
	if(!trainDataFile){
		std::cerr << "ERROR: The input training data file is Empty!! Exiting the code." << std::endl;
		return(-1);
	}
	while(std::getline(trainDataFile, singleDataInstance)){
		std::cout << singleDataInstance << std::endl;
		f_parseData(singleDataInstance, trainDataTable, noOfTrainSamples, my_attrDelim);
		noOfTrainSamples++;
	}
	trainDataFile.close();

	// pruning test data
	testDataFile.open(argv[2]);
	if(!testDataFile){
		std::cerr << "WARINING: The 'test data' is empty!!! Exiting the code." << std::endl;
		return(0);		// successfully built the tree but failed to evaluate on NULL test data
	}
	while(std::getline(testDataFile, singleDataInstance)){
		std::cout << singleDataInstance << std::endl;
		f_parseData(singleDataInstance, testDataTable, noOfTestSamples, my_attrDelim);
		noOfTestSamples++;
		// std::cout << singleDataInstance[0] << std::endl;
		// std::cout << singleDataInstance.find_first_of(" ") << std::endl;

	}

	// // std::cout << trainDataTable[0][0] << std::endl;
	std::cout << noOfTrainSamples << "," << noOfTestSamples << std::endl;
	// // std::cout << 



}