%{
	#include <stdio.h>
	#include <string.h>
	#include "yacc.tab.h"
	struct {
		const char * name;
		int value;
	} reserved[] = {
		{ "mainprog"	, MAINPROG },
		{ "function"	, FUNCTION },
		{ "procedure"	, PROCEDURE },
		{ "begin"		, BEG },
		{ "end"			, END },
		{ "if"			, IF },
		{ "elif"		, ELIF },
		{ "else"		, ELSE },
		{ "nop"			, NOP },
		{ "for"			, FOR},
		{ "while"		, WHILE },
		{ "return"		, RETURN },
		{ "in"			, IN },
		{ "int"			, INT },
		{ "float"		, FLOAT },
		{ ""			, EOF },
	};
	
	int yywrap(void) {
    	return 1;
	}
%}

%%

(0|[1-9][0-9]*)("."[0-9]+[1-9])?	{
	char * str = malloc(sizeof(yytext));
	yylval.data = strcpy(str, yytext);
	return NUMBER;
}
[A-Za-z][A-Za-z0-9]*		{
	int i = 0;
	char * str = malloc(sizeof(yytext));
	yylval.data = strcpy(str, yytext);
	for(i = 0; reserved[i].name[0] != '\0'; i++)
		if(strcmp(reserved[i].name, yytext) == 0) break;
	if(reserved[i].name[0] == '\0') return IDENT;
	else return reserved[i].value;
}

"+"		return ADD;
"-"		return SUB;
"*"		return MUL;
"/"		return DIV;
"=" 	return ASS;
"!"		return NOT;

==		return EQUAL;
!=		return NOTEQU;
"<"		return GREATER;
"<="	return EQUGRE;
">"		return LESS;
">="	return EQULESS;

"."		return DOT;

","		return COMMA;
":"		return COLON;
";" 	return SEMICOLON;
"("		return LPAREN;
")"		return RPAREN;
"[" 	return LBRACKET;
"]" 	return RBRACKET;
\n 		yylineno++;

"//".*(\n|^) yylineno++;

[ \t]+
%%
