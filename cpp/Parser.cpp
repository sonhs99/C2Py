#include "Parser.h"
#include <cstdio>

extern "C" int yyparse(ParseTree ** tree);
extern "C" FILE *yyin;

ParseTree * Parser::parse(){
	ParseTree * head;
	yyin = fopen(File.c_str(), "r");
	if(yyin == NULL) {
		fprintf(stderr, "Error : file is not find\n");
		return NULL;
	}
	if(yyparse(&head)) {
        return NULL;
    }
	fclose(yyin);
	return head;
}