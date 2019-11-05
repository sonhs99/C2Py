#include <ParseTree.h>
#include "Parser.h"
#include "AST.h"
#include "PrintAST.h"

int main(){
	Parser parser("input.txt");
	auto head = parser.parse();
	auto AST = ASTGenerate(head);
	//	PrintPT(head, 0);
	PrintAST printer;
	DeletePT(head);
	AST->accept(*dynamic_cast<Visitor*>(&printer));
	delete AST;
	return 0;
}