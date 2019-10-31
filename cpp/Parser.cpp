#include "Parser.h"
#include <cstdio>

extern "C" int yyparse(ParseTree ** tree);
extern "C" FILE *yyin;

ParseTree * Parser::parse(){
	ParseTree * head;
	yyin = fopen(File.c_str(), "r");
	if(yyin == NULL) {
		fprintf(stderr, "Error : file is not find\n");
		exit(1);
	}
	if(yyparse(&head)) {
        fprintf(stderr, "Error!\n");
        exit(1);
    }
	fclose(yyin);
	PrintPT(head, 0);
	return head;
}