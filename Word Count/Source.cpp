#include <iostream>
#include <fstream>
#include <string>
#include <tuple>

#include "AllegroDisplay.h"
//#include "CSVFile.h"
#include "Output.h"
//#include "TextFile.h"
#include "Document.h"
#include "SubButtons.h"

std::string getCurrentDate() {
	std::string year, month, day;
	std::cout << "Please enter date. dd/mm/yyyy" << std::endl;
	std::cout << "Please enter the day: ";
	std::cin >> day;
	std::cout << "Please enter the month: ";
	std::cin >> month;
	std::cout << "Please enter the year: ";
	std::cin >> year;
	std::cout << std::endl;

	return (day + "-" + month + "-" + year);
}

int getCurrentVersion() {
	int currentVersion;
	std::cout << "What is the most current version? ";
	std::cin >> currentVersion;
	return currentVersion;
}

std::tuple<std::string, int> getTarget() {
	std::tuple<std::string, int> returnValues;
	int wordTarget;
	std::string dateToFinish;
	std::cout << "How many words do you want to have typed? ";
	std::cin >> wordTarget;
	std::cout << "What date do you want to be finished by? ";
	dateToFinish = getCurrentDate();
	std::get<0>(returnValues) = dateToFinish;
	std::get<1>(returnValues) = wordTarget;

	return returnValues;

}

int main() {
	std::string Entry = "";
	//Edit an entry could take excel grid reference for ease of use

	CreateDisplay();

	/*while (Entry != "QUIT") {
		std::cout << "1)Update" << std::endl << "2)Get Statistics" << std::endl << "3)How far to target" << std::endl << "QUIT to quit" << std::endl;
		std::cin >> Entry;

		while (Entry != "1" && Entry != "2" && Entry != "3" && Entry != "QUIT") {
			std::cout << "Please enter either 1, 2 or QUIT" << std::endl;
			std::cout << "1)Update" << std::endl << "2)Edit an entry" << std::endl << "QUIT to quit" << std::endl;
			std::cin >> Entry;
		}
	
		if (Entry == "1") {

		} 
		else if (Entry == "2") {

		}
		else if (Entry == "3") {
		
		}



		//Update the output.csv file
		/*if (Entry == "1") {
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
			int averageDayWords = 0;
			for (int i = 0; i < dateAverage.size(); i++) {
				std::cout << "On " << std::get<0>(dateAverage[i]) << " you averaged " << std::get<1>(dateAverage[i]) << " words." << std::endl;
				averageDayWords = averageDayWords + std::get<1>(dateAverage[i]);
			}

			averageDayWords = averageDayWords / dateAverage.size();

			std::cout << "On an average day you have " << averageDayWords << " new words." << std::endl;
			std::cout << "You've also typed " << outputCSV.getWordCount() << " words " << std::endl;
			
		}
		else if (Entry == "3") {
			std::tuple<std::string, int> Target = getTarget();
			Output outputCSV = Output("output");
			outputCSV.CSVRead();

			//Non leap-year
			int non_LeapYear[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
			//Leapyears occur ever 
			int leapYear[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

			std::string startDate = outputCSV.getNewestEntryDate();
			//Subtract 48 to turn ascii value into actual decimal value
			int startDay = (startDate[0]-48)*10 + (startDate[1]-48);
			int startMonth = (startDate[3]-48)*10 + (startDate[4]-48);
			int startYear = (startDate[6]-48)*1000 + (startDate[7]-48)*100 + (startDate[8]-48)*10 + (startDate[9]-48);

			int endDay = (std::get<0>(Target)[0]-48)*10 + (std::get<0>(Target)[1]-48);
			int endMonth = (std::get<0>(Target)[3]-48)*10 + (std::get<0>(Target)[4]-48);
			int endYear = (std::get<0>(Target)[6]-48)*1000 + (std::get<0>(Target)[7]-48)*100 + (std::get<0>(Target)[8]-48)*10 + (std::get<0>(Target)[9]-48);

			int totalDays = 0;
			while ((startDay != endDay) || (startMonth != endMonth) || (startYear != endYear)) {
				totalDays = totalDays + 1;
				startDay = startDay + 1;
				if (startYear % 4 == 0 && startYear % 100 == 0 && startYear % 400 == 0) {
					if (startDay == leapYear[startMonth - 1]) {
						startDay = 1;
						startMonth = startMonth + 1;
					}
					if (startMonth > 12) {
						startMonth = 1;
						startYear = startYear + 1;
					}
				}
				else {
					if (startDay == non_LeapYear[startMonth - 1]) {
						startDay = 1;
						startMonth = startMonth + 1;
					}
					if (startMonth > 12) {
						startMonth = 1;
						startYear = startYear + 1;
					}
				}
				
				
			}

			std::cout << "You have " << totalDays << " days to reach your goal of " << std::get<1>(Target) << " words" << std::endl;
			std::cout << "You currently have " << outputCSV.getWordCount() << " words and need " << (std::get<1>(Target) - outputCSV.getWordCount()) << " more words." << std::endl;
			if (totalDays == 0) {
				std::cout << "You have " << (std::get<1>(Target) - outputCSV.getWordCount()) << " words to do today" << std::endl;
			}
			else {
				std::cout << "To reach this you have to type " << (std::get<1>(Target) - outputCSV.getWordCount()) / totalDays << " words per day" << std::endl;
			}

		}

		std::cout << std::endl;


	}*/
	return 1;
}