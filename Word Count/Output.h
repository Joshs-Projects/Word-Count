#pragma once
#include "CSVFile.h"

class Output : public CSVFile {


public:
	Output(std::string newFilename) {
		SetFilename(newFilename);
	}

	std::string getEntry(int row, int column) {
		return data[row + 1][column];
	}

	int setEntry(int row, int column, std::string entry) {
		data[row + 1][column] = entry;
		return 1;
	}

	int setNewRow(std::vector <std::string> newRow) {
		data.push_back(newRow);
		return 1;
	}

	int getVersion() {
		return data.size() - 1;
	}

	int getWordCount() {
		if (getVersion() == 0) {
			return 0;
		}
		else {
			return stoi(data[getVersion()][3]);
		}

	}
};
