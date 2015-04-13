#include "ReadFile.h"

// AUTHOR: MATTHEW GOLDSTEIN

ReadFile::ReadFile(){
	numCommands = getNumCommandsFromFile(); // get the number of commands from the file
	numWalls = 0;
	numAiTanks = 0;
	FILENAME = "level1.txt";
	commandArray = new int*[numCommands]; // initialize array of <numCommands> arrays
	for (int i = 0; i < numCommands; i++){ // for every array in commandArray...
		commandArray[i] = new int[3];	   // ...create an array of 5 characters
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

int ReadFile::getNumWalls(){
	return numWalls;
}

int ReadFile::getNumAITanks(){
	return numAiTanks;
}

int ReadFile::getNumCommandsFromFile(){
	inputFile.open(FILENAME); // open file
	int numCmds = 0; // holds number of lines
	std::string tempHolder; // allows getline to be used
	while (std::getline(inputFile, tempHolder)){ // while there are more lines
		if (tempHolder[0] != '#'){ // if the line doesn't have a comment
			numCmds++; // increment numlines
		}
	}

	inputFile.close(); // close file

	return numCmds;
}

int ReadFile::getNumCommands(){
	return numCommands;
}

int** ReadFile::parseCommandFile(){
	std::string currentLine; // buffer for reading lines and parsing
	std::string words[3]; // array of words for current line to be parsed
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

		/* Commands are as follows :
		 *	wall <xPos> <yPos>
		 *	player <xPos> <yPos>
		 *	ai <xPos> <yPos>
		 */
		currentWord = words[0];
		if (currentWord == "wall"){
			numWalls++;
			commandArray[l][0] = 0;
			commandArray[l][1] = std::stoi(words[1]);
			commandArray[l][2] = std::stoi(words[2]);
		}
		else if (currentWord == "player"){
			commandArray[l][0] = 1;
			commandArray[l][1] = std::stoi(words[1]);
			commandArray[l][2] = std::stoi(words[2]);
		}
		else if (currentWord == "ai"){
			numAiTanks++;
			commandArray[l][0] = 2;
			commandArray[l][1] = std::stoi(words[1]);
			commandArray[l][2] = std::stoi(words[2]);
		}
		l++;
	}
	inputFile.close();
	return commandArray;
}

void ReadFile::setFileName(std::string newFileName){
	FILENAME = newFileName;
}