#include "header.h"
#include <cstddef>		// std::size_t

// Functions

// Using the training data to segregate the {First Name, Middle Name, Last Name, <feature Vector>, Label}
void f_parseData(std::string& singleInstance, vvs& dataMatrix, int rowIndex, std::string& attrDelim){
	// parsing the training and test data as Vector<Vector>
	int attr_count = 0;
	std::string my_substring;
	std::size_t delimIndex = singleInstance.find_first_of(attrDelim);
	my_substring = singleInstance.substr(delimIndex+1, std::string::npos);
	// std::cout << delimIndex ;
	while(delimIndex != std::string::npos){
		attr_count += 1;
		std::cout << delimIndex << ", " ;
		// std::cout << "[" << my_substring << "] ";
		delimIndex = my_substring.find_first_of(attrDelim);
		my_substring = my_substring.substr(delimIndex+1, std::string::npos);
		

	}
	std::cout << " #" << attr_count << std::endl;
	std::cout << std::endl;
	
}



int main(int argc, char const *argv[])
{
	// parsing the training and test data as Vector<Vector>
	std::string my_attrDelim = " ";
	std::string singleDataInstance;
	std::ifstream trainDataFile;
	std::ifstream testDataFile;
	vvs trainDataTable;
	vvs testDataTable;
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