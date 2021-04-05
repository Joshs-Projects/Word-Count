#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

class CSVFile {
private:
	std::string fileName = "";

	std::vector<std::vector< std::string>> data;
	

public:
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

	std::string getEntry(int row, int column) {
		return data[row+1][column];
	}

	int setEntry(int row, int column, std::string entry) {
		data[row+1][column] = entry;
		return 1;
	}

	int setNewRow(std::vector <std::string> newRow) {
		data.push_back(newRow);
		return 1;
	}

	int getVersion() {
		return data.size()-1;
	}

	int getWordCount() {
		if (getVersion() == 0) {
			return 0;
		}
		else {
			return stoi(data[getVersion()][2]);
		}
		
	}

};

