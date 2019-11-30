%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ParseTree.h>

extern int yylex();
extern int yylineno;
int yyerror(struct TreeNode ** pt, char const *str) { return 0; };
%}

%debug

%union {
    char * data;
	struct TreeNode * node;
}
%token<data> NUMBER IDENT
%left ASS 
%left EQUAL NOTEQU GREATER EQUGRE LESS EQULESS
%right IN
%left ADD SUB
%left MUL DIV
%nonassoc UMINUS UPLUS NOT
%left LBRACKET LPAREN

%token LPAREN "(" RPAREN ")" LBRACKET "[" RBRACKET "]"
%token COMMA "," SEMICOLON ";" COLON ":" 
%token MAINPROG FUNCTION BEG END IF CONTINUE
%token ELIF ELSE NOP WHILE RETURN BREAK 
%token FOR IN INT FLOAT

%type<node> program declarations identifier_list type standard_type subprograms
%type<node> subprogram subprogram_head args params block stmts stmt
%type<node> if elif else while for exprs expr ret_expr
%type<node> expr_list term stmt_semi init param number

%parse-param {
	struct TreeNode ** pt
}

%destructor { free($$); } NUMBER IDENT

%%
program
	:MAINPROG IDENT SEMICOLON declarations subprograms{
		$$ = CreatePT(Root, strdup($2), 
			CreatePT(List, "list", $4, 
			CreatePT(List, "list", $5, NULL))
		, NULL);
		*pt = $$;
	}
	|MAINPROG error SEMICOLON declarations subprograms{
		fprintf(stderr, "line (%d) : \'Ident\' is missing\n", yylineno);
		$$ = CreatePT(Root, NULL, 
			CreatePT(List, "list", $4,
			CreatePT(List, "list", $5, NULL))
		, NULL);
		*pt = $$;
	}
	|MAINPROG IDENT error declarations subprograms{
		fprintf(stderr, "line (%d) : \';\' is missing\n", yylineno);
		$$ = CreatePT(Root, strdup($2), 
			CreatePT(List, "list", $4,
			CreatePT(List, "list", $5, NULL))
		, NULL);
		*pt = $$;
	}
	|MAINPROG error declarations subprograms{
		fprintf(stderr, "line (%d) : \'Ident\' is missing\n", yylineno);
		fprintf(stderr, "line (%d) : \';\' is missing\n", yylineno);
		$$ = CreatePT(Root, NULL, 
			CreatePT(List, "list", $3,
			CreatePT(List, "list", $4, NULL))
		, NULL);
		*pt = $$;
	}
	
declarations
	:type identifier_list SEMICOLON declarations {
		$1->sibling = $2;
		$$ = CreatePT(Decl, "decl", $1, $4);
	}
	|type identifier_list error declarations {
		fprintf(stderr, "line (%d) : \';\' is missing\n", yylineno);
		$1->sibling = $2;
		$$ = CreatePT(Decl, "decl", $1, $4);
	}
	| { $$ = CreatePT(Void, "void", NULL, NULL); }
	
identifier_list
	:IDENT init { $$ = CreatePT(Ident, strdup($1), $2, NULL); }
	|IDENT init COMMA identifier_list { $$ = CreatePT(Ident, strdup($1), NULL, $4); }
	|error {
		fprintf(stderr, "line (%d) : \'Ident\' is missing\n", yylineno);
		$$ = CreatePT(Void, "void", NULL, NULL);
	}
	
init
	:ASS expr { $$ = $2;}
	| { $$ = CreatePT(Void, "void", NULL, NULL); }
	| error { $$ = CreatePT(Void, "void", NULL, NULL); }
	
type
	: standard_type { $$ = CreatePT(Type, "type", $1, NULL); }
	| standard_type LBRACKET NUMBER RBRACKET{
		$1->sibling = CreatePT(Num, strdup($3), NULL, NULL);
		$$ = CreatePT(Type, "type", $1, NULL);
	}
	| standard_type LBRACKET RBRACKET {
		$1->sibling = CreatePT(Num, strdup("0"), NULL, NULL);
		$$ = CreatePT(Type, "type", $1, NULL);
	}
	| standard_type LBRACKET NUMBER error{
		fprintf(stderr, "line (%d) : \']\' is missing\n", yylineno);
		$1->sibling = CreatePT(Num, strdup($3), NULL, NULL);
		$$ = CreatePT(Type, "type", $1, NULL);
	}
	| standard_type LBRACKET error {
		fprintf(stderr, "line (%d) : \'NUMBER\' is missing\n", yylineno);
		fprintf(stderr, "line (%d) : \']\' is missing\n", yylineno);
		$1->sibling = CreatePT(Void, "void", NULL, NULL);
		$$ = CreatePT(Type, "type", $1, NULL);
	}
	| standard_type LBRACKET error RBRACKET {
		fprintf(stderr, "line (%d) : \'NUMBER\' is missing\n", yylineno);
		$1->sibling = CreatePT(Void, "void", NULL, NULL);
		$$ = CreatePT(Type, "type", $1, NULL);
	}
	| standard_type NUMBER RBRACKET{
		fprintf(stderr, "line (%d) : \'[\' is missing\n", yylineno);
		$1->sibling = CreatePT(Num, strdup($2), NULL, NULL);
		$$ = CreatePT(Type, "type", $1, NULL);
	}
	| standard_type NUMBER error{
		fprintf(stderr, "line (%d) : \'[\' is missing\n", yylineno);
		fprintf(stderr, "line (%d) : \']\' is missing\n", yylineno);
		$1->sibling = CreatePT(Num, strdup($2), NULL, NULL);
		$$ = CreatePT(Type, "type", $1, NULL);
	}
	| standard_type RBRACKET{
		fprintf(stderr, "line (%d) : \'[\' is missing\n", yylineno);
		fprintf(stderr, "line (%d) : \'NUMBER\' is missing\n", yylineno);
		$$ = CreatePT(Type, "type", $1, NULL);
	}
	
standard_type
	:INT { $$ = CreatePT(Int, "int", NULL, NULL); }
	|FLOAT { $$ = CreatePT(Float, "float", NULL, NULL); }
	| error error {
		fprintf(stderr, "line (%d) : \'type\' is required\n", yylineno);
		$$ = CreatePT(Void, "void", NULL, NULL);
	}
	
subprograms
	:subprogram subprograms {$1->sibling = $2; $$ = $1; }
	| { $$ = CreatePT(Void, "void", NULL, NULL); }
	
subprogram
	:subprogram_head block {
		$1->child->sibling->sibling = $2;
		$$ = $1;
	}

subprogram_head
	:FUNCTION IDENT args COLON type {
		$3->sibling = $5;
		$$ = CreatePT(Func, strdup($2), $3, NULL);
	}
	|FUNCTION error args COLON type {
		fprintf(stderr, "line (%d) : \'Ident\' is missing\n", yylineno);
		$3->sibling = $5;
		$$ = CreatePT(Func, NULL, $3, NULL);
	}
	|FUNCTION IDENT args error type {
		fprintf(stderr, "line (%d) : \':\' is missing\n", yylineno);
		$3->sibling = $5;
		$$ = CreatePT(Func, strdup($2), $3, NULL);
	}
	|FUNCTION error args error type {
		fprintf(stderr, "line (%d) : \'Ident\' is missing\n", yylineno);
		fprintf(stderr, "line (%d) : \':\' is missing\n", yylineno);
		$3->sibling = $5;
		$$ = CreatePT(Func, NULL, $3, NULL);
	}
	|FUNCTION IDENT args { 
		$3->sibling = CreatePT(Void, "void", NULL, NULL);
		$$ = CreatePT(Func, strdup($2), $3, NULL); 
	}
	|FUNCTION error args { 
		fprintf(stderr, "line (%d) : \'Ident\' is missing\n", yylineno);
		$3->sibling = CreatePT(Void, "void", NULL, NULL);
		$$ = CreatePT(Func, NULL, $3, NULL); 
	}
	
args
	:LPAREN params RPAREN { $$ = CreatePT(List, "list", $2, NULL);}
	|LPAREN params error {
		fprintf(stderr, "line (%d) : \')\' is missing\n", yylineno);
		$$ = CreatePT(List, "list", $2, NULL);
	}
	| { $$ = CreatePT(Void, "void", NULL, NULL); }
	
params
	:param { $$ = $1; }
	|param COMMA params {
		if($1 != NULL){$1->sibling = $3; $$ = $1;}
		else $$ = $3;	
		}
	
param
	:IDENT COLON type {
		$3->sibling = CreatePT(Ident, strdup($1), NULL, NULL);
		$$ = CreatePT(Param, "param", $3,NULL);
	}
	|IDENT error type {
		fprintf(stderr, "line (%d) : \':\' is missing\n", yylineno);
		$3->sibling = CreatePT(Ident, strdup($1), NULL, NULL);
		$$ = CreatePT(Param, "param", $3, NULL);
	}

block
	:BEG declarations stmts END{
		$$ = CreatePT(Block, "block",
			CreatePT(List, "list", $2, $3)
		, NULL); 
	}

stmts
	:stmt stmts{ if($1 != NULL) {$1->sibling = $2; $$ = $1;}
				else $$ = $2;}
	| { $$ = NULL; }
	|error stmts { $$ = $2; }
	
stmt
	:stmt_semi SEMICOLON { $$ = $1; }
	|stmt_semi error { fprintf(stderr, "line (%d) : \';\' is missing\n", yylineno); $$ = $1;}
	|block
	|if
	|while
	|for
	
stmt_semi
	:expr
	|BREAK	{ $$ = CreatePT(Break, "break", NULL, NULL); }
	|CONTINUE { $$ = CreatePT(Continue, "continue", NULL, NULL); }
	|RETURN ret_expr { $$ = CreatePT(Return, "return", $2, NULL); }
	|NOP { $$ = CreatePT(Nop, "nop", NULL, NULL); }
	| { $$ = NULL; }
	
ret_expr
	:expr
	| { $$ = CreatePT(Void, "void", NULL, NULL); }
	|error {
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		$$ = CreatePT(Void, "void", NULL, NULL);
		}
	
if
	: IF expr COLON stmt elif else{
		$2->sibling = $4;
		$4->sibling = CreatePT(List, "list", $5, $6);
		$$ = CreatePT(If, "if", $2, NULL);
	}
	|IF expr error stmt elif else{
		fprintf(stderr, "line (%d) : \':\' is required\n", yylineno);
		$2->sibling = $4;
		$4->sibling = CreatePT(List, "list", $5, $6);
		$$ = CreatePT(If, "if", $2, NULL);
	}

elif
	:ELIF expr COLON stmt elif{
		$2->sibling = $4;
		$$ = CreatePT(Elif, "elif", $2, $5);
	}
	| { $$ = CreatePT(Void, "void", NULL, NULL); }
	|ELIF expr error stmt elif{
		fprintf(stderr, "line (%d) : \':\' is required\n", yylineno);
		$2->sibling = $4;
		$$ = CreatePT(Elif, "elif", $2, $5);
	}
	
else
	:ELSE COLON stmt { $$ = CreatePT(Else, "else", $3, NULL); }
	| { $$ = CreatePT(Void, "void", NULL, NULL); }
	|ELSE error stmt { 
		fprintf(stderr, "line (%d) : \':\' is required\n", yylineno);
		$$ = CreatePT(Else, "else", $3, NULL); 
	}
	
while
	:WHILE expr COLON stmt else {
		$2->sibling = $4; $4->sibling = $5;
		$$ = CreatePT(While, "while", $2, NULL);
	}
	|WHILE expr error stmt else {
		fprintf(stderr, "line (%d) : \':\' is required\n", yylineno);
		$2->sibling = $4; $4->sibling = $5;
		$$ = CreatePT(While, "while", $2, NULL);
	}
	
for
	:FOR expr IN expr COLON stmt else {
		$2->sibling = $4; $6->sibling = $7;
		$$ = CreatePT(For, "for", 
			CreatePT(In, "in", $2, $6),
			NULL);
	}
	|FOR expr IN expr error stmt else {
		fprintf(stderr, "line (%d) : \':\' is required\n", yylineno);
		$2->sibling = $4; $6->sibling = $7;
		$$ = CreatePT(For, "for", 
			CreatePT(In, "in", $2, $6),
			NULL);
	}
	|FOR expr COLON stmt else {
		fprintf(stderr, "line (%d) : \'in\' is required\n", yylineno);
		$2->sibling = CreatePT(Void, "void", NULL, NULL); $4->sibling = $5;
		$$ = CreatePT(For, "for", 
			CreatePT(In, "in", $2, $4),
			NULL);
	}

expr_list
	:exprs { $$ = CreatePT(List, "List", $1, NULL); }
	| { $$ = CreatePT(Void, "void", NULL, NULL); }
	
exprs
	:expr
	|expr COMMA exprs { $1->sibling = $3; $$ = $1; }
	|expr error exprs {
		fprintf(stderr, "line (%d) : \',\' is missing\n", yylineno);
		$1->sibling = $3; $$ = $1;
	}
	
expr
	:term
	|expr ASS		expr { $1->sibling = $3; $$ = CreatePT(Assign, "=", $1, NULL); }
	|expr GREATER	expr { $1->sibling = $3; $$ = CreatePT(Greater, "<", $1, NULL); }
	|expr EQUGRE	expr { $1->sibling = $3; $$ = CreatePT(EquGre, "<=", $1, NULL); }
	|expr LESS		expr { $1->sibling = $3; $$ = CreatePT(Less, ">", $1, NULL); }
	|expr EQULESS	expr { $1->sibling = $3; $$ = CreatePT(EquLess, ">=", $1, NULL); }
	|expr EQUAL		expr { $1->sibling = $3; $$ = CreatePT(Equ, "==", $1, NULL); }
	|expr NOTEQU	expr { $1->sibling = $3; $$ = CreatePT(NotEqu, "!=", $1, NULL); }
	|expr ADD		expr { $1->sibling = $3; $$ = CreatePT(Plus, "+", $1, NULL); }
	|expr SUB		expr { $1->sibling = $3; $$ = CreatePT(Minus, "-", $1, NULL); }
	|expr MUL		expr { $1->sibling = $3; $$ = CreatePT(Mul, "*", $1, NULL); }
	|expr DIV		expr { $1->sibling = $3; $$ = CreatePT(Div, "/", $1, NULL); }
	|expr IN		expr { $1->sibling = $3; $$ = CreatePT(In, "in", $1, NULL); }
	|expr LBRACKET	expr RBRACKET { $1->sibling = $3; $$ = CreatePT(Array, "[]", $1, NULL); }
	|expr LPAREN expr_list RPAREN { $1->sibling = $3; $$ = CreatePT(Proc, NULL, $1, NULL); }
	|ADD expr %prec UPLUS  { $$ = CreatePT(Pos, "+", $2, NULL); }
	|SUB expr %prec UMINUS { $$ = CreatePT(Neg, "-", $2, NULL); }
	|NOT expr { $$ = CreatePT(Not, "!", $2, NULL); }
	|expr LBRACKET	expr error { 
		fprintf(stderr, "line (%d) : \']\' is required\n", yylineno);
		$1->sibling =  $3; $$ = CreatePT(Array, "[]", $1, NULL); }
	|expr LPAREN expr_list error {
		fprintf(stderr, "line (%d) : \')\' is required\n", yylineno);
		$1->sibling = $3;
		$$ = CreatePT(Proc, NULL, $1, NULL); 
	}	
	
term
	:number
	|IDENT { $$ = CreatePT(Var, strdup($1), NULL, NULL); }
	|LPAREN expr RPAREN { $$ = $2; }
	|LPAREN expr error { fprintf(stderr, "line (%d) : \')\' is required\n", yylineno); $$ = $2; }
	|error { fprintf(stderr, "line (%d) : \'term\' is required\n", yylineno); $$ = CreatePT(Void, "void", NULL, NULL);}
	
number
	:NUMBER { $$ = CreatePT(Num, strdup($1), NULL, NULL); }
	|NUMBER number {
		fprintf(stderr, "line (%d) : \'number\' is declared repeatedly\n", yylineno);
		free($1); $$ = $2; 
		}
%%
