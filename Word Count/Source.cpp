#include <iostream>
#include <fstream>
#include <string>
#include <tuple>

//#include "CSVFile.h"
#include "Output.h"
//#include "TextFile.h"
#include "Document.h"

std::string getCurrentDate() {
	std::string year, month, day;
	std::cout << "Please enter date. dd/mm/yyyy" << std::endl;
	std::cout << "Please enter the year: ";
	std::cin >> year;
	std::cout << "Please enter the month: ";
	std::cin >> month;
	std::cout << "Please enter the day: ";
	std::cin >> day;
	std::cout << std::endl;

	return (day + "-" + month + "-" + year);
}

int getCurrentVersion() {
	int currentVersion;
	std::cout << "What is the most current version? ";
	std::cin >> currentVersion;
	return currentVersion;
}

int main() {
	std::string Entry = "";
	//Edit an entry could take excel grid reference for ease of use
	std::cout << "1)Update" << std::endl << "2)Get Statistics" << std::endl << "QUIT to quit" << std::endl;
	std::cin >> Entry;

	//while (Entry != "QUIT") {
		while (Entry != "1" && Entry != "2" && Entry != "QUIT") {
			std::cout << "Please enter either 1, 2 or QUIT" << std::endl;
			std::cout << "1)Update" << std::endl << "2)Edit an entry" << std::endl << "QUIT to quit" << std::endl;
			std::cin >> Entry;
		}
	
		//Update the output.csv file
		if (Entry == "1") {
			//Ask the user for the most recent version number to be bale to loop through multiple versions if necessary
			int currentVersion = getCurrentVersion();

			Output outputCSV = Output("output");
			outputCSV.CSVRead();
			Document inputText = Document("Draft ", outputCSV.getVersion());
			//inputText.ReadTextFile();
			for (int i = outputCSV.getVersion() + 1; i <= currentVersion; i++) {
				inputText.SetTextFilename("Draft ", i);
				inputText.ReadTextFile();
				std::cout << "Please enter the date for Draft " + std::to_string(i) << std::endl;
				outputCSV.setNewRow({ getCurrentDate(), "", std::to_string(inputText.getNumberOfWords() - outputCSV.getWordCount()), std::to_string(inputText.getNumberOfWords()) });

			}

			//outputCSV.setEntry(outputCSV.getVersion(), 3, std::to_string(inputText.getNumberOfWords()));
			outputCSV.CSVWrite();
		}
		//Display all the statistics
		else if (Entry == "2") {

			Output outputCSV = Output("output");
			outputCSV.CSVRead();

			std::vector<std::tuple<std::string, int>> dateAverage = outputCSV.getAverageWordsPerDay();

			std::cout << "This is your average new words per session: " + std::to_string(outputCSV.getAverageWordsPerSession()) << std::endl;
			std::cout << "This is your average new words per day: " << std::endl;
			for (int i = 0; i < dateAverage.size(); i++) {
				std::cout << "On " << std::get<0>(dateAverage[i]) << " you averaged " << std::get<1>(dateAverage[i]) << " words." << std::endl;
			}
			std::cout << "You've also typed " << outputCSV.getWordCount() << " words " << std::endl;
			
		}


	//}
	return 1;
}