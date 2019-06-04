#include "FileHandler.h"

std::string FileHandler::LoadFile(const std::string& filename)
{
	std::ifstream file;
	file.open(filename.c_str());
	
	std::string output;
	std::string line;

	if(file.is_open())
	{
		while(file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load file: " << filename << std::endl;
	}
	return output;
}
