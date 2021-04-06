#pragma once
#include "CSVFile.h"
#include <tuple>

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

	//This gets the version that the csv file has most recently
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

	int getAverageWordsPerSession() {
		int total = 0;
		for (int i = 1; i < data.size(); i++) {
			total = total + stoi(data[i][2]);
		}
		return (total / getVersion());
	}

	std::vector<std::tuple<std::string, int>> getAverageWordsPerDay() {
		//First entry is the date second is the number of sessions in that day third is the total for the day
		std::vector <std::tuple <std::string, int, int>> daySessionsTotal = {};
		std::tuple <std::string, int, int> tempTuple;
		/*std::get<0>(tempTuple) = data[1][0];
		std::get<1>(tempTuple) = 1;
		std::get<2>(tempTuple) = stoi(data[1][2]);
		daySessionsTotal.push_back(tempTuple);*/

		std::vector<std::tuple <std::string, int>> dateAverage = {};
		std::tuple <std::string, int> tempTupleAverage;
		
		for (int i = 1; i < data.size(); i++) {
			bool found = false;
			for (int q = 0; q < daySessionsTotal.size(); q++) {
				if (data[i][0].compare(std::get<0>(daySessionsTotal[q])) == 0) {
					std::get<1>(daySessionsTotal[q]) = std::get<1>(daySessionsTotal[q]) + 1;
					std::get<2>(daySessionsTotal[q]) = std::get<2>(daySessionsTotal[q]) + stoi(data[i][2]);
					found = true;
				}
			}

			if (found == false) {
				std::get<0>(tempTuple) = data[i][0];
				std::get<1>(tempTuple) = 1;
				std::get<2>(tempTuple) = stoi(data[i][2]);
				daySessionsTotal.push_back(tempTuple);
			}
		}

		/*for (int q = 0; q < daySessionsTotal.size(); q++) {
			for (int i = 1; i < data.size(); i++) {
				if (data[i][0] == std::get<0>(daySessionsTotal[q])) {
					std::get<1>(daySessionsTotal[q]) = std::get<1>(daySessionsTotal[q]) + 1;
					std::get<2>(daySessionsTotal[q]) = std::get<2>(daySessionsTotal[q]) + stoi(data[i][2]);
				}
				else {
					std::get<0>(tempTuple) = data[i][0];
					std::get<1>(tempTuple) = 1;
					std::get<2>(tempTuple) = stoi(data[i][2]);
					daySessionsTotal.push_back(tempTuple);
				}
			}
		}*/

		for (int i = 0; i < daySessionsTotal.size(); i++) {
			std::get<0>(tempTupleAverage) = std::get<0>(daySessionsTotal[i]);
			std::get<1>(tempTupleAverage) = std::get<2>(daySessionsTotal[i])/(std::get<1>(daySessionsTotal[i]));
			dateAverage.push_back(tempTupleAverage);
		}

		return dateAverage;
	}
};
