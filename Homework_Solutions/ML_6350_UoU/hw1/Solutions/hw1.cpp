#include "header.h"

// Functions

// Using the training data to segregate the {First Name, Middle Name, Last Name, <feature Vector>, Label}
void f_parseData(string& m_row, vvs& m_dataMatrix){

}



int main(int argc, char const *argv[])
{
	// parsing the training and test data as Vector<Vector>
	std::string singleDataInstance;
	std::ifstream trainDataFile;
	std::ifstream testDataFile;
	vvs trainDataTable
	vvs testDataTable;

	// take the 1st argument while running the executable and parse the train/test data stored in it
	trainDataFile.open(argv[1]);
	if(!trainDataFile){
		std::cerr << "Error: The input training data file is Empty!!" << std::endl;
		return(-1);
	}
	while(std::getline(trainDataFile, singleDataInstance)){
		f_parseData(singleDataInstance, trainDataTable);
	}
	trainDataFile.close();





}