#include "Parser.h"
#include <cstdio>

extern "C" int yyparse(ParseTree ** tree);
extern "C" FILE *yyin;

ParseTree * Parser::parse(){
	ParseTree * head = NULL;
	yyin = fopen(File.c_str(), "r");
	if(yyin == NULL) {
		fprintf(stderr, "Error : file not find\n");
		return NULL;
	}
	int i = yyparse(&head); //PrintPT(head, 0);
	if(i) {
		fclose(yyin);
        return NULL;
    }
	fclose(yyin);
	return head;
}