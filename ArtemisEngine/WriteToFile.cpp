#include <iostream>
#include <fstream>
#include <string>


void WriteToFile(std::ofstream &outputFile, std::string msg)
{
	outputFile << msg << std::endl;
}

