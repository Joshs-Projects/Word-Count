#include <iostream>
#include <fstream>
#include <string>

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
	std::cout << "1)Update" << std::endl << "2)Edit an entry" << std::endl << "QUIT to quit" << std::endl;
	std::cin >> Entry;

	while (Entry != "1" && Entry != "2" && Entry != "QUIT") {
		std::cout << "Please enter either 1, 2 or QUIT" << std::endl;
		std::cout << "1)Update" << std::endl << "2)Edit an entry" << std::endl << "QUIT to quit" << std::endl;
		std::cin >> Entry;
	}

	if (Entry == "QUIT") {
		return 1;
	}
	else if (Entry == "1") {
		//Ask the user for the most recent version number to be bale to loop through multiple versions if necessary
		int currentVersion = getCurrentVersion();

		Output outputCSV = Output("output");
		outputCSV.CSVRead();
		Document inputText = Document("Draft ", outputCSV.getVersion());
		//inputText.ReadTextFile();
		for (int i = outputCSV.getVersion()+1; i <= currentVersion; i++) {
			inputText.SetTextFilename("Draft ", i);
			inputText.ReadTextFile();
			std::cout << "Please enter the date for Draft " + std::to_string(i) << std::endl;
			outputCSV.setNewRow({ getCurrentDate(), "", std::to_string(inputText.getNumberOfWords()-outputCSV.getWordCount()), std::to_string(inputText.getNumberOfWords()) });
			
		}

		
		//outputCSV.setEntry(outputCSV.getVersion(), 3, std::to_string(inputText.getNumberOfWords()));
		outputCSV.CSVWrite();

	}

	return 1;
}