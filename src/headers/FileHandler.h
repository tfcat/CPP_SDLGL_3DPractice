#pragma once
#include <fstream>
#include <iostream>
#include <string>

class FileHandler {
public:
	// just loads a text file from the hard drive, and returns it as a string
	static std::string LoadFile(const std::string& filename);
};