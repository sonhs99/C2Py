%{
	#include <stdio.h>
	#include <string.h>
	#include "yacc.tab.h"
	
	int yywrap(void) {
    	return 1;
	}
%}

%%

"mainprog"	return MAINPROG;
"function"	return FUNCTION;
"begin"		return BEG;
"end"		return END;
"if"		return IF;
"elif"		return ELIF;
"else"		return ELSE;
"nop"		return NOP;
"for"		return FOR;
"while"		return WHILE;
"return"	return RETURN;
"in"		return IN;
"int"		return INT;
"float"		return FLOAT;
"continue"	return CONTINUE;
"break"		return BREAK;

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

","		return COMMA;
":"		return COLON;
";" 	return SEMICOLON;
"("		return LPAREN;
")"		return RPAREN;
"[" 	return LBRACKET;
"]" 	return RBRACKET;

\n 		yylineno++;

[A-Za-z][A-Za-z0-9]*		{
	char * str = malloc(sizeof(yytext));
	yylval.data = strcpy(str, yytext);
	return IDENT;
}

(\+|-)?(0|[1-9][0-9]*)("."[0-9]+[1-9])?	{
	char * str = malloc(sizeof(yytext));
	yylval.data = strcpy(str, yytext);
	return NUMBER;
}

"//".*(\n|^) yylineno++;

[ \t]+
.		fprintf(stderr, "line (%d) : Unknown Token - %s\n", yylineno, yytext);
%%
