#pragma once
#include <string>
#include <ParseTree.h>

class Parser{
private:
	std::string File;
	
public:
	Parser(std::string f):
		File(f) {};
	ParseTree * parse();
};