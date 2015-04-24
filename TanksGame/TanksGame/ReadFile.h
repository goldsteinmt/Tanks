#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

// AUTHOR: MATTHEW GOLDSTEIN

class ReadFile {
private:
	int **commandArray; // array holding commands
	std::ifstream inputFile; // instream to read file
	std::string FILENAME; // filename of commands text file
	int numCommands; // number of commands for array
	int numAiTanks; // number of ai tanks for array in other class
	int numWalls; // number of walls for array in other class
	int getNumLines(); // inputs file and gets number of lines in the file
public:
	ReadFile(); // constructor
	void setFileName(std::string); // changes name of current file
	int** parseCommandFile(); // parses individual lines and adds commands to the array
	int getNumCommands(); // returns numCommands
	int getNumWalls(); // returns number of walls
	int getNumAITanks(); // returns number of ai tanks
};