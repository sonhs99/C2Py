#include <ParseTree.h>
#include <cstring>
#include "Parser.h"
#include "AST.h"
#include "PrintAST.h"
#include "TypeResolver.h"
#include "ICGenerator.h"

int main(int argc, char *argv[]){
	bool ParseTree = false;
	bool AbstractSyntexTree = false;
	bool SymbolTable = false;
	if(argc < 2) {
		std::cerr << "Usage : <executable> <filename> <option>\n";
		return 1;
	}
	for(int i = 2; i < argc; i++){
		if(strcmp(argv[i], "-p") == 0) ParseTree = true;
		else if(strcmp(argv[i], "-a") == 0) AbstractSyntexTree = true;
		else if(strcmp(argv[i], "-s") == 0) SymbolTable = true;
		else {
			std::cerr << "Usage : <executable> <filename> <option>\n";
			return 1;
		}
	}
	Parser parser(argv[1]);
	auto head = parser.parse();
	auto AST = ASTGenerate(head);
	TypeResolver resolver;
	ICGenerator generator;
	AST->accept(*dynamic_cast<Visitor*>(&resolver));
	AST->accept(*dynamic_cast<Visitor*>(&generator));
	if(head != NULL){
		if(ParseTree){
			printf("\n================ Parse Tree ==============\n\n");
			PrintPT(head, 0);
		}
		if(AbstractSyntexTree){
			PrintAST printer;
			printf("\n========= Abstract Syntex Tree ===========\n\n");
			AST->accept(*dynamic_cast<Visitor*>(&printer));
		}
		if(SymbolTable){
			printf("\n============= Symbol Table ===============\n\n");
			PrintTable(resolver.getTable(), 0);
		}
	}
	DeletePT(head);
	delete AST;
	delete resolver.getTable();
	return 0;
}