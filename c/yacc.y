%{
#include <stdio.h>
#include <stdlib.h>
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
%left EQUAL NOTEQU GREATER EQUGRE LESS EQULESS IN
%left ADD SUB
%left MUL DIV
%nonassoc UMINUS UPLUS NOT

%token LPAREN "(" RPAREN ")" LBRACKET "[" RBRACKET "]"
%token COMMA "," SEMICOLON ";" COLON ":" 
%token MAINPROG FUNCTION BEG END IF
%token ELIF ELSE NOP WHILE RETURN
%token FOR IN INT FLOAT

%type<node> program declarations identifier_list type standard_type subprograms
%type<node> subprogram subprogram_head args params block stmts stmt
%type<node> if elif else while for procedure variable exprs expr
%type<node> expr_list term stmt_semi init

%parse-param {
	struct TreeNode ** pt
}

%%
program
	:MAINPROG IDENT SEMICOLON declarations subprograms{
		$$ = CreatePT(Root, $2, 
			CreatePT(List, "list", $4, $5)
		, NULL);
		*pt = $$;
	}
	|MAINPROG error SEMICOLON declarations subprograms{
		fprintf(stderr, "line (%d) : \'Ident\' is missing\n", yylineno);
		$$ = CreatePT(Root, NULL, 
			CreatePT(List, "list", $4, $5)
		, NULL);
		*pt = $$;
	}
	|MAINPROG IDENT error declarations subprograms{
		fprintf(stderr, "line (%d) : \';\' is missing\n", yylineno);
		$$ = CreatePT(Root, $2, 
			CreatePT(List, "list", $4, $5)
		, NULL);
		*pt = $$;
	}
	|MAINPROG error declarations subprograms{
		fprintf(stderr, "line (%d) : \'Ident\' is missing\n", yylineno);
		fprintf(stderr, "line (%d) : \';\' is missing\n", yylineno);
		$$ = CreatePT(Root, NULL, 
			CreatePT(List, "list", $3, $4)
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
	:IDENT init { $$ = CreatePT(Ident, $1, $2, NULL); }
	|IDENT init COMMA identifier_list { $$ = CreatePT(Ident, $1, NULL, $4); }
	|error {
		fprintf(stderr, "line (%d) : \'Ident\' is missing\n", yylineno);
		$$ = CreatePT(Void, "void", NULL, NULL);
	}
	
init
	:ASS expr { $$ = $2;}
	| { $$ = CreatePT(Void, NULL, NULL, NULL); }
	|ASS error {
		fprintf(stderr, "line (%d) : \'expr\' is missing\n", yylineno);
		$$ = CreatePT(Void, "void", NULL, NULL); 
	}
	
type
	: standard_type { $$ = CreatePT(Type, "type", $1, NULL); }
	| standard_type LBRACKET NUMBER RBRACKET{
		$1->sibling = CreatePT(Num, $3, NULL, NULL);
		$$ = CreatePT(Type, "type", $1, NULL);
	}
	| standard_type LBRACKET NUMBER error{
		fprintf(stderr, "line (%d) : \']\' is missing\n", yylineno);
		$1->sibling = CreatePT(Num, $3, NULL, NULL);
		$$ = CreatePT(Type, "type", $1, NULL);
	}
	
standard_type
	:INT { $$ = CreatePT(Int, "int", NULL, NULL); }
	|FLOAT { $$ = CreatePT(Float, "float", NULL, NULL); }
	
subprograms
	:subprogram subprograms {$$ = CreatePT(List, "list", $1, $2); }
	| { $$ = CreatePT(Void, "void", NULL, NULL); }
	
subprogram
	:subprogram_head block {
		$1->child->sibling->sibling = $2;
		$$ = $1;
	}

subprogram_head
	:FUNCTION IDENT args COLON standard_type {
		$3->sibling = $5;
		$$ = CreatePT(Func, $2, $3, NULL);
	}
	|FUNCTION error args COLON standard_type {
		fprintf(stderr, "line (%d) : \'Ident\' is missing\n", yylineno);
		$3->sibling = $5;
		$$ = CreatePT(Func, NULL, $3, NULL);
	}
	|FUNCTION IDENT args { 
		$3->sibling = CreatePT(Void, "void", NULL, NULL);
		$$ = CreatePT(Func, $2, $3, NULL); 
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
	:identifier_list COLON type { $3->sibling = $1; $$ = CreatePT(Param, "param", $3,NULL);}
	|identifier_list error type { 
		fprintf(stderr, "line (%d) : \':\' is missing\n", yylineno);
		$3->sibling = $1; $$ = CreatePT(Param, "param", $3, NULL);
	}
	|identifier_list COLON type SEMICOLON params { 
		$3->sibling = $1;
		$$ = CreatePT(Param, "param", $3, $5); 
	}
	|identifier_list error type SEMICOLON params{ 
		fprintf(stderr, "line (%d) : \':\' is missing\n", yylineno);
		$3->sibling = $1; $$ = CreatePT(Param, "param", $3, $5);
	}
	
block
	:BEG declarations stmts END{ 
		$$ = CreatePT(Block, "block", $3, $2); 
	}
	|BEG declarations stmts error{
		fprintf(stderr, "line (%d) : \'end\' is missing\n", yylineno);
		$$ = CreatePT(Block, "block", $3, $2);
	}

stmts
	:stmt stmts{ $1->sibling = $2; $$ = $1; }
	| { $$ = NULL; }
	
stmt
	:stmt_semi SEMICOLON { $$ = $1; }
	|stmt_semi error { fprintf(stderr, "line (%d) : \';\' is missing\n", yylineno);}
	|block
	|if
	|while
	|for
	
	
stmt_semi
	:expr
	|RETURN expr { $$ = CreatePT(Return, "return", $2, NULL); }
	|NOP { $$ = CreatePT(Nop, "nop", NULL, NULL); }
	
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
	
variable
	:IDENT { $$ = CreatePT(Var, $1, NULL, NULL); }
	|IDENT LBRACKET expr RBRACKET { $$ = CreatePT(Var, $1, $3, NULL); }
	|IDENT LBRACKET expr error { 
		fprintf(stderr, "line (%d) : \']\' is required\n", yylineno);
		$$ = CreatePT(Var, $1, $3, NULL);
	}
	
procedure
	:IDENT LPAREN expr_list RPAREN { $$ = CreatePT(Proc, $1, $3, NULL); }
	|IDENT LPAREN expr_list error {
		fprintf(stderr, "line (%d) : \')\' is required\n", yylineno);
		$$ = CreatePT(Proc, $1, $3, NULL);
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
	|ADD expr %prec UPLUS  { $$ = CreatePT(Pos, "+", $2, NULL); }
	|SUB expr %prec UMINUS { $$ = CreatePT(Neg, "-", $2, NULL); }
	|NOT expr { $$ = CreatePT(Not, "!", $2, NULL); }
	|expr ASS	error { 
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		$1->sibling =  CreatePT(Void, "void", NULL, NULL); $$ = CreatePT(Assign, "=", $1, NULL); }
	|expr GREATER	error { 
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		$1->sibling =  CreatePT(Void, "void", NULL, NULL); $$ = CreatePT(Greater, "<", $1, NULL); }
	|expr EQUGRE	error { 
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		$1->sibling =  CreatePT(Void, "void", NULL, NULL); $$ = CreatePT(EquGre, "<=", $1, NULL); }
	|expr LESS		error { 
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		$1->sibling = CreatePT(Void, "void", NULL, NULL); $$ = CreatePT(Less, ">", $1, NULL); }
	|expr EQULESS	error { 
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		$1->sibling = CreatePT(Void, "void", NULL, NULL); $$ = CreatePT(EquLess, ">=", $1, NULL); }
	|expr EQUAL		error { 
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		$1->sibling = CreatePT(Void, "void", NULL, NULL); $$ = CreatePT(Equ, "==", $1, NULL); }
	|expr NOTEQU	error {
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		$1->sibling = CreatePT(Void, "void", NULL, NULL); $$ = CreatePT(NotEqu, "!=", $1, NULL); }
	|expr ADD		error { 
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		$1->sibling = CreatePT(Void, "void", NULL, NULL); $$ = CreatePT(Plus, "+", $1, NULL); }
	|expr SUB		error { 
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		$1->sibling = CreatePT(Void, "void", NULL, NULL); $$ = CreatePT(Minus, "-", $1, NULL); }
	|expr MUL		error { 
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		$1->sibling = CreatePT(Void, "void", NULL, NULL); $$ = CreatePT(Mul, "*", $1, NULL); }
	|expr DIV		error { 
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		$1->sibling = CreatePT(Void, "void", NULL, NULL); $$ = CreatePT(Div, "/", $1, NULL); }
	|expr IN		error { 
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		$1->sibling =  CreatePT(Void, "void", NULL, NULL); $$ = CreatePT(In, "in", $1, NULL); }
	|ADD error %prec UPLUS  { 
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		$$ = CreatePT(Pos, "+", CreatePT(Void, "void", NULL, NULL), NULL); }
	|SUB error %prec UMINUS { 
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		$$ = CreatePT(Neg, "-", CreatePT(Void, "void", NULL, NULL), NULL); }
	|NOT error { 
		fprintf(stderr, "line (%d) : \'expr\' is required\n", yylineno);
		$$ = CreatePT(Not, "!", CreatePT(Void, "void", NULL, NULL), NULL); }
	
term
	:NUMBER { $$ = CreatePT(Num, $1, NULL, NULL); }
	|variable
	|procedure
	|LPAREN expr RPAREN { $$ = $2; }
	|LPAREN expr error { fprintf(stderr, "line (%d) : \')\' is required\n", yylineno); $$ = $2; }
	|type term{ fprintf(stderr, "line (%d) : \'type\' is not required\n", yylineno); $$ = $2;}
	|type { fprintf(stderr, "line (%d) : \'term\' is required\n", yylineno); $$ = CreatePT(Void, "void", NULL, NULL);}
%%
