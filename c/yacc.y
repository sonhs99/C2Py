%{
#include <stdio.h>
#include <stdlib.h>
#include <ParseTree.h>

extern int yylex();
int yyerror(struct TreeNode ** pt, char const *str);
%}

%define parse.error verbose

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
%token MAINPROG FUNCTION PROCEDURE BEG END IF
%token ELIF ELSE NOP WHILE RETURN
%token FOR IN INT FLOAT

%type<node> program declarations identifier_list type standard_type subprograms
%type<node> subprogram subprogram_head args params block stmts stmt
%type<node> if elif else while for procedure variable exprs expr
%type<node> expr_list term stmt_semi

%parse-param {
	struct TreeNode ** pt
}

%%
program
	:MAINPROG IDENT SEMICOLON declarations subprograms block {
		$5->sibling = $6;
		$$ = CreatePT(Root, $2, 
			CreatePT(List, "list", $4, $5)
		, NULL);
		*pt = $$;
	}
	
declarations
	:type identifier_list SEMICOLON declarations {
		$1->sibling = $2;
		$$ = CreatePT(Decl, "decl", $1, $4);
	}
	| { $$ = CreatePT(Void, "void", NULL, NULL); }
	
identifier_list
	:IDENT { $$ = CreatePT(Ident, $1, NULL, NULL); }
	|IDENT COMMA identifier_list { $$ = CreatePT(Ident, $1, NULL, $3); }
	
type
	: standard_type { $$ = CreatePT(Type, "type", $1, NULL); }
	| standard_type LBRACKET NUMBER RBRACKET{
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
	:subprogram_head declarations block {
		$1->child->sibling->sibling = CreatePT(List, "list", $2, $3);
		$$ = $1;
	}

subprogram_head
	:FUNCTION IDENT args COLON standard_type {
		$3->sibling = $5;
		$$ = CreatePT(Func, $2, $3, NULL);
	}
	|FUNCTION IDENT args SEMICOLON { 
		$3->sibling = CreatePT(Void, "void", NULL, NULL);
		$$ = CreatePT(Func, $2, $3, NULL); 
	}
	
args
	:LPAREN params RPAREN { $$ = CreatePT(List, "list", $2, NULL);}
	| { $$ = CreatePT(Void, "void", NULL, NULL); }
	
params
	:identifier_list COLON type { $3->sibling = $1; $$ = CreatePT(Param, "param", $3,NULL);}
	|identifier_list COLON type SEMICOLON params { 
		$3->sibling = $1;
		$$ = CreatePT(Param, "param", $3, $5); 
	}
	
block
	:BEG stmts END{ $$ = CreatePT(Block, "block", $2, NULL); }

stmts
	:stmt stmts{ $1->sibling = $2; $$ = $1; }
	| { $$ = NULL; }
	
stmt
	:stmt_semi SEMICOLON { $$ = $1; }
	|stmt_semi error { yyerrok; }
	|block
	|if
	|while
	|for
	
	
stmt_semi
	:variable ASS expr { $1->sibling = $3; $$ = CreatePT(Assign, "=", $1, NULL); }
	|variable error expr { yyerrok; }
	|procedure { $$ = $1; }
	|RETURN expr { $$ = CreatePT(Return, "return", $2, NULL); }
	|NOP { $$ = CreatePT(Nop, "nop", NULL, NULL); }
	
if
	: IF expr COLON stmt elif else{
		$2->sibling = $4;
		$4->sibling = CreatePT(List, "list", $5, $6);
		$$ = CreatePT(If, "if", $2, NULL);
	}
	|error { yyerrok; YYABORT; }

elif
	:ELIF expr COLON stmt elif{
		$2->sibling = $4;
		$$ = CreatePT(Elif, "elif", $2, $5);
	}
	| { $$ = CreatePT(Void, "void", NULL, NULL); }
	
else
	:ELSE COLON stmt { $$ = CreatePT(Else, "else", $3, NULL); }
	| { $$ = CreatePT(Void, "void", NULL, NULL); }
	
while
	:WHILE expr COLON stmt else {
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
	
variable
	:IDENT { $$ = CreatePT(Var, $1, NULL, NULL); }
	|IDENT LBRACKET expr RBRACKET { $$ = CreatePT(Var, $1, $3, NULL); }
	
procedure
	:IDENT LPAREN expr_list RPAREN { $$ = CreatePT(Proc, $1, $3, NULL); }

expr_list
	:exprs { $$ = CreatePT(List, "List", $1, NULL); }
	| { $$ = CreatePT(Void, "void", NULL, NULL); }
	
exprs
	:expr 
	|expr COMMA exprs { $1->sibling = $3; $$ = $1; }
	
expr
	:term
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
	|expr error		expr { yyerrok; }
	|ADD expr %prec UPLUS  { $$ = CreatePT(Pos, "+", $2, NULL); }
	|SUB expr %prec UMINUS { $$ = CreatePT(Neg, "-", $2, NULL); }
	|NOT expr { $$ = CreatePT(Not, "!", $2, NULL); }
	|error expr { yyerrok; }
	
term
	:NUMBER { $$ = CreatePT(Num, $1, NULL, NULL); }
	|variable
	|procedure
	|LPAREN expr RPAREN { $$ = $2; }
	|LPAREN error RPAREN { yyerrok; }
	
%%

int yyerror(struct TreeNode ** pt, char const *str) {
	extern int yylineno;
    fprintf(stderr, "line(%d): %s \n", yylineno, str);
    return 0;
}
