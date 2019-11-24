#include <ParseTree.h>
#include "Parser.h"
#include "AST.h"
#include "PrintAST.h"
#include "TypeResolver.h"

int main(int argc, char *argv[]){
	if(argc < 2) {
		printf("Usage : <executable> <filename> <option>\n");
		return 1;
	}
	Parser parser(argv[1]);
	auto head = parser.parse();
	auto AST = ASTGenerate(head);
	TypeResolver resolver;
	AST->accept(*dynamic_cast<Visitor*>(&resolver));
	if(head != NULL){
		printf("\n================ Parse Tree ==============\n\n");
		PrintPT(head, 0);
		PrintAST printer;
		DeletePT(head);
		printf("\n========= Abstract Syntex Tree ===========\n\n");
		AST->accept(*dynamic_cast<Visitor*>(&printer));
		printf("\n============= Symbol Table ===============\n\n");
		PrintTable(resolver.getTable(), 0);
	}
	delete AST;
	delete resolver.getTable();
	return 0;
}