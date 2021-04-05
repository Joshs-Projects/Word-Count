#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

class CSVFile {
protected:
	std::string fileName = "";

	std::vector<std::vector< std::string>> data;
	

public:
	//default constructor
	CSVFile() { }

	CSVFile(std::string newFileName) {
		fileName = newFileName;
	}

	int CSVRead() {
		//variables used temporarily
		std::string line;
		std::vector<std::string> splitLine;

		std::ifstream myFile;
		myFile.open(fileName+".csv");

		while (getline(myFile, line)) {
			std::istringstream ss(line);
			std::string token;

			while (getline(ss, token, ',')) {
				splitLine.push_back(token);
			}

			data.push_back(splitLine);
			splitLine = {};

		}
		myFile.close();

		return 1;
	}

	int CSVWrite() {
		std::ofstream myFile;
		myFile.open(fileName+".csv");

		for (int i = 0; i < data.size(); i++) {
			for (int q = 0; q < data[i].size() - 1; q++) {
				myFile << data[i][q] << ",";
			}
			myFile << data[i][data[i].size() - 1];
			if (i < data.size() - 1) {
				myFile << "\n";
			}
		}

		return 1;
	}

	int SetFilename(std::string newFilename) {
		fileName = newFilename;
		return 1;
	}

};

