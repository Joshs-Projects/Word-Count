#pragma once
#include "Button.h"

class UpdateButton : public Button {
public:
	UpdateButton(int ButtonLocationX, int ButtonLocationY, int ButtonSizeX, int ButtonSizeY, const char* NameOfButton, const char* ClickedButtonName, int ScaledSizeX, int ScaledSizeY) {
		this->SetPos(ButtonLocationX, ButtonLocationY);
		this->SetSize(ButtonSizeX, ButtonSizeY, ScaledSizeX, ScaledSizeY);
		this->SetButtonPicture(NameOfButton, ClickedButtonName);

		this->buttonPicture = al_load_bitmap(NameOfButton);
		this->clickedButtonPicture = al_load_bitmap(ClickedButtonName);

	}

	int WhenHit() {
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
};

class GetStatistics : public Button {
	GetStatistics (int ButtonLocationX, int ButtonLocationY, int ButtonSizeX, int ButtonSizeY, const char* NameOfButton, const char* ClickedButtonName, int ScaledSizeX, int ScaledSizeY) {
		this->SetPos(ButtonLocationX, ButtonLocationY);
		this->SetSize(ButtonSizeX, ButtonSizeY, ScaledSizeX, ScaledSizeY);
		this->SetButtonPicture(NameOfButton, ClickedButtonName);

		this->buttonPicture = al_load_bitmap(NameOfButton);
		this->clickedButtonPicture = al_load_bitmap(ClickedButtonName);

	}

	int WhenHit() {
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
};

class HowFarToTarget : public Button {
	HowFarToTarget(int ButtonLocationX, int ButtonLocationY, int ButtonSizeX, int ButtonSizeY, const char* NameOfButton, const char* ClickedButtonName, int ScaledSizeX, int ScaledSizeY) {
		this->SetPos(ButtonLocationX, ButtonLocationY);
		this->SetSize(ButtonSizeX, ButtonSizeY, ScaledSizeX, ScaledSizeY);
		this->SetButtonPicture(NameOfButton, ClickedButtonName);

		this->buttonPicture = al_load_bitmap(NameOfButton);
		this->clickedButtonPicture = al_load_bitmap(ClickedButtonName);

	}

	int WhenHit() {
		std::tuple<std::string, int> Target = getTarget();
		Output outputCSV = Output("output");
		outputCSV.CSVRead();

		//Non leap-year
		int non_LeapYear[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		//Leapyears occur ever 
		int leapYear[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

		std::string startDate = outputCSV.getNewestEntryDate();
		//Subtract 48 to turn ascii value into actual decimal value
		int startDay = (startDate[0] - 48) * 10 + (startDate[1] - 48);
		int startMonth = (startDate[3] - 48) * 10 + (startDate[4] - 48);
		int startYear = (startDate[6] - 48) * 1000 + (startDate[7] - 48) * 100 + (startDate[8] - 48) * 10 + (startDate[9] - 48);

		int endDay = (std::get<0>(Target)[0] - 48) * 10 + (std::get<0>(Target)[1] - 48);
		int endMonth = (std::get<0>(Target)[3] - 48) * 10 + (std::get<0>(Target)[4] - 48);
		int endYear = (std::get<0>(Target)[6] - 48) * 1000 + (std::get<0>(Target)[7] - 48) * 100 + (std::get<0>(Target)[8] - 48) * 10 + (std::get<0>(Target)[9] - 48);

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
	}

};