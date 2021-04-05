#pragma once
#include "TextFile.h"

#include <string>

class Document : public TextFile {

public:
	Document(std::string newFileName, int VersionNumber) {
		SetFileName(newFileName + std::to_string(VersionNumber));
	}

	int SetTextFilename(std::string newFileName, int VersionNumber) {
		SetFileName(newFileName + std::to_string(VersionNumber));
		return 1;
	}

	int getNumberOfWords() {
		wordCount = 0;
		for (int i = 0; i < contentsOfFile.size(); i++) {
			wordCount = wordCount + contentsOfFile[i].size();
		}
		return wordCount;
	}

};
