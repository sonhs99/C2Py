#include <cstdio>
#include <cstdlib>
#include <ParseTree.h>
#include "Parser.h"

int main(){
	Parser parser("input.txt", true, false);
	auto head = parser.parse();
	DeletePT(head);
	return 0;
}