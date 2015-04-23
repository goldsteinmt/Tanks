#include "ReadFile.h"

// AUTHOR: MATTHEW GOLDSTEIN

ReadFile::ReadFile(){
	numCommands = getNumLines(); // get the number of commands from the file
	numWalls = 0;
	numAiTanks = 0;
	FILENAME = "level1.txt";
	commandArray = new int*[numCommands]; // initialize array of <numCommands> arrays
	for (int i = 0; i < numCommands; i++){ // for every array in commandArray...
		commandArray[i] = new int[3];	   // ...create an array of 3 ints
	}
}

int ReadFile::getNumLines(){
	inputFile.open(FILENAME); // open file
	int numLines = 0; // holds number of lines
	char c;
	while (inputFile.get(c)){ // while there are more lines
		if (c == '\n'){
			numLines++; // increment numlines
		}
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

int ReadFile::getNumCommands(){
	return numCommands;
}

int** ReadFile::parseCommandFile(){
	std::string currentLine; // buffer for reading lines and parsing
	std::string words[3]; // array of words for current line to be parsed
	std::string currentWord; // current word being read
	inputFile.open(FILENAME); // open input file

	int k = 0;
	while (std::getline(inputFile, currentLine)){
		std::transform(currentLine.begin(), currentLine.end(), currentLine.begin(), ::tolower);
		std::stringstream sstream(currentLine);  // allows to parse string into array of words
		int i = 0;
		while (sstream.good() && i < 3){
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
			commandArray[k][0] = 0;
			commandArray[k][1] = std::stoi(words[1]);
			commandArray[k][2] = std::stoi(words[2]);
			k++;
		}
		else if (currentWord == "player"){
			commandArray[k][0] = 1;
			commandArray[k][1] = std::stoi(words[1]);
			commandArray[k][2] = std::stoi(words[2]);
			k++;
		}
		else if (currentWord == "ai"){
			numAiTanks++;
			commandArray[k][0] = 2;
			commandArray[k][1] = std::stoi(words[1]);
			commandArray[k][2] = std::stoi(words[2]);
			k++;
		}
		
	}
	inputFile.close();
	return commandArray;
}

void ReadFile::setFileName(std::string newFileName){
	FILENAME = newFileName;
}