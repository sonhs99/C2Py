#pragma once
#include <string>
#include <ParseTree.h>

class Parser{
private:
	std::string File;
	bool showPT;
	bool showAST;
public:
	Parser(std::string f, bool pt, bool ast):
		File(f), showPT(pt), showAST(ast) {};
	ParseTree * parse();
};