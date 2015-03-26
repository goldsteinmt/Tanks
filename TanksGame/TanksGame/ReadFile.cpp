#include "ReadFile.h"

// AUTHOR: MATTHEW GOLDSTEIN

ReadFile::ReadFile(){
	numCommands = getNumLines(); // get the number of lines from the file
	commandArray = new char*[numCommands]; // initialize array of <numCommands> arrays
	for (int i = 0; i < numCommands; i++){ // for every array in commandArray...
		commandArray[i] = new char[5];	   // ...create an array of 5 characters
	}
}

int ReadFile::getNumLines(){
	inputFile.open(FILENAME); // open file
	int numLines = 0; // holds number of lines
	std::string tempHolder; // allows getline to be used
	while (std::getline(inputFile, tempHolder)){ // while there are more lines
		numLines++; // increment numlines
	}

	inputFile.close(); // close file

	return numLines;
}

int ReadFile::getNumCommands(){
	return numCommands;
}

char** ReadFile::parseCommandFile(){
	std::string currentLine; // buffer for reading lines and parsing
	std::string words[5]; // array of words for current line to be parsed
	std::string currentWord; // current word being read
	inputFile.open(FILENAME); // open input file

	int l = 0;
	while (std::getline(inputFile, currentLine)){
		std::transform(currentLine.begin(), currentLine.end(), currentLine.begin(), ::tolower);
		std::stringstream sstream(currentLine);  // allows to parse string into array of words
		int i = 0;
		while (sstream.good() && i < 5){
			sstream >> words[i];
			i++;
		}
		// different command options below
		currentWord = words[0];
		if (currentWord == "world"){
			commandArray[l][0] = 'w';
			commandArray[l][1] = words[1][0];
			commandArray[l][2] = words[2][0];
		}


		// TODO: DIFFERENT TEXT FILE CASES

		l++;
	}
	inputFile.close();
	return commandArray;
}

void ReadFile::setFileName(std::string newFileName){
	FILENAME = newFileName;
}