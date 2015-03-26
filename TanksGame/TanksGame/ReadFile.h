#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

// AUTHOR: MATTHEW GOLDSTEIN

class ReadFile {
private:
	char **commandArray; // array holding commands
	std::ifstream inputFile; // instream to read file
	std::string FILENAME = "level1.txt"; // filename of commands text file
	int numCommands; // number of commands for array
public:
	ReadFile(); // constructor
	void setFileName(std::string); // changes name of current file
	int getNumLines(); // inputs file and gets number of lines in the file
	char** parseCommandFile(); // parses individual lines and adds commands to the array
	int getNumCommands(); // returns numCommands
};