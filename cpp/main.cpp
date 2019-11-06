#include <ParseTree.h>
#include "Parser.h"
#include "AST.h"
#include "PrintAST.h"

int main(int argc, char *argv[]){
	if(argc < 2) {
		printf("Usage : <executable> <filename> <option>\n");
		return 0;
	}
	fflush(stdout);
	Parser parser(argv[1]);
	auto head = parser.parse();
	auto AST = ASTGenerate(head);
	//	PrintPT(head, 0);
	PrintAST printer;
	DeletePT(head);
	AST->accept(*dynamic_cast<Visitor*>(&printer));
	delete AST;
	return 0;
}