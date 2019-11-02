%{
#include <stdio.h>
#include <stdlib.h>
#include <ParseTree.h>
%}

%define parse.error verbose

%union {
    char * data;
	struct TreeNode * node;
}
%token<data> NUMBER IDENT INT FLOAT
%left ASS 
%left EQUAL NOTEQU GREATER EQUGRE LESS EQULESS IN
%left ADD SUB
%left MUL DIV
%nonassoc UMINUS UPLUS NOT
%token LPAREN RPAREN LBRACKET RBRACKET DOT
%token MAINPROG FUNCTION PROCEDURE BEG END IF
%token ELIF ELSE NOP WHILE RETURN
%token COMMA SEMICOLON COLON FOR IN
%type<node> program declarations identifier_list type standard_type subprograms
%type<node> subprogram subprogram_head args params block stmts stmt
%type<node> if elif else while for procedure variable exprs expr
%type<node> expr_list term stmt_semi

%destructor { } <data>
%destructor { free ($$); } <*>

%parse-param {
	struct TreeNode ** pt
}

%%
program
	:MAINPROG IDENT SEMICOLON declarations subprograms block {
		$5->sibling = $6;
		$$ = CreatePT(Root, $2, 
			CreatePT(Decls, NULL, $4, $5)
		, NULL);
		*pt = $$;
	}
	
declarations
	:type identifier_list SEMICOLON declarations {
		$1->sibling = $2;
		$$ = CreatePT(Decl, NULL, $1, $4);
	}
	| { $$ = CreatePT(Void, NULL, NULL, NULL); }
	
identifier_list
	:IDENT { $$ = CreatePT(Ident, $1, NULL, NULL); }
	|IDENT COMMA identifier_list { $$ = CreatePT(Ident, $1, NULL, $3); }
	
type
	: standard_type { $$ = CreatePT(Type, NULL, $1, NULL); }
	| standard_type LBRACKET NUMBER RBRACKET{
		$1->sibling = CreatePT(Num, $3, NULL, NULL);
		$$ = CreatePT(Type, NULL, $1, NULL);
	}
	
standard_type
	:INT { $$ = CreatePT(Int, $1, NULL, NULL); }
	|FLOAT { $$ = CreatePT(Float, $1, NULL, NULL); }
	
subprograms
	:subprogram subprograms {$$ = CreatePT(Funcs, NULL, $1, $2); }
	| { $$ = CreatePT(Void, NULL, NULL, NULL); }
	
subprogram
	:subprogram_head declarations block {
		$1->child->sibling->sibling = CreatePT(Decls, NULL, $2, $3);
		$$ = $1;
	}

subprogram_head
	:FUNCTION IDENT args COLON standard_type {
		$3->sibling = $5;
		$$ = CreatePT(Func, $2, $3, NULL);
	}
	|FUNCTION IDENT args SEMICOLON { 
		$3->sibling = CreatePT(Void, NULL, NULL, NULL);
		$$ = CreatePT(Func, $2, $3, NULL); 
	}
	
args
	:LPAREN params RPAREN { $$ = CreatePT(Params, NULL, $2, NULL);}
	| { $$ = CreatePT(Void, NULL, NULL, NULL); }
	
params
	:identifier_list COLON type { $3->sibling = $1; $$ = CreatePT(Param, NULL, $3,NULL);}
	|identifier_list COLON type SEMICOLON params { 
		$3->sibling = $1;
		$$ = CreatePT(Param, NULL, $3, $5); 
	}
	
block
	:BEG stmts END{ $$ = CreatePT(Block, NULL, $2, NULL); }

stmts
	:stmt stmts{ $1->sibling = $2; $$ = $1; }
	| { $$ = NULL; }
	
stmt
	:stmt_semi SEMICOLON { $$ = $1; }
	|stmt_semi error { yyerrok; $$ = NULL; }
	|block
	|if
	|while
	|for
	|error SEMICOLON { yyerrok; $$ = NULL; }
	
	
stmt_semi
	:variable ASS expr { $1->sibling = $3; $$ = CreatePT(Assign, NULL, $1, NULL); }
	|procedure { $$ = $1; }
	|RETURN expr { $$ = CreatePT(Return, NULL, $2, NULL); }
	|NOP { $$ = CreatePT(Nop, NULL, NULL, NULL); }
	
if
	: IF expr COLON stmt elif else{
		$2->sibling = $4;
		$4->sibling = CreatePT(Elifs, NULL, $5, $6);
		$$ = CreatePT(If, NULL, $2, NULL);
	}

elif
	:ELIF expr COLON stmt elif{
		$2->sibling = $4;
		$$ = CreatePT(Elif, NULL, $2, $5);
	}
	| { $$ = CreatePT(Void, NULL, NULL, NULL); }
	
else
	:ELSE COLON stmt { $$ = CreatePT(Else, NULL, $3, NULL); }
	| { $$ = CreatePT(Void, NULL, NULL, NULL); }
	
while
	:WHILE expr COLON stmt else {
		$2->sibling = $4; $4->sibling = $5;
		$$ = CreatePT(While, NULL, $2, NULL);
	}
	
for
	:FOR expr IN expr COLON stmt else {
		$2->sibling = $4; $6->sibling = $7;
		$$ = CreatePT(For, NULL, 
			CreatePT(In, NULL, $2, $6),
			NULL);
	}
	
variable
	:IDENT { $$ = CreatePT(Var, $1, NULL, NULL); }
	|IDENT LBRACKET expr RBRACKET { $$ = CreatePT(Var, $1, $3, NULL); }
	
procedure
	:IDENT LPAREN expr_list RPAREN { $$ = CreatePT(Proc, $1, $3, NULL); }

expr_list
	:exprs
	| { $$ = NULL; }
	
exprs
	:expr 
	|expr COMMA exprs { $1->sibling = $3; $$ = $1; }
	
expr
	:term
	|expr GREATER	expr { $1->sibling = $3; $$ = CreatePT(Greater, NULL, $1, NULL); }
	|expr EQUGRE	expr { $1->sibling = $3; $$ = CreatePT(EquGre, NULL, $1, NULL); }
	|expr LESS		expr { $1->sibling = $3; $$ = CreatePT(Less, NULL, $1, NULL); }
	|expr EQULESS	expr { $1->sibling = $3; $$ = CreatePT(EquLess, NULL, $1, NULL); }
	|expr EQUAL		expr { $1->sibling = $3; $$ = CreatePT(Equ, NULL, $1, NULL); }
	|expr NOTEQU	expr { $1->sibling = $3; $$ = CreatePT(NotEqu, NULL, $1, NULL); }
	|expr ADD		expr { $1->sibling = $3; $$ = CreatePT(Plus, NULL, $1, NULL); }
	|expr SUB		expr { $1->sibling = $3; $$ = CreatePT(Minus, NULL, $1, NULL); }
	|expr MUL		expr { $1->sibling = $3; $$ = CreatePT(Mul, NULL, $1, NULL); }
	|expr DIV		expr { $1->sibling = $3; $$ = CreatePT(Div, NULL, $1, NULL); }
	|expr IN		expr { $1->sibling = $3; $$ = CreatePT(In, NULL, $1, NULL); }
	|ADD expr %prec UPLUS  { $$ = CreatePT(Pos, NULL, $2, NULL); }
	|SUB expr %prec UMINUS { $$ = CreatePT(Neg, NULL, $2, NULL); }
	|NOT expr { $$ = CreatePT(Not, NULL, $2, NULL); }
	
term
	:NUMBER { $$ = CreatePT(Num, $1, NULL, NULL); }
	|variable
	|procedure
	|LPAREN expr RPAREN { $$ = $2; }
	
%%

int yyerror(struct TreeNode ** pt, char const *str) {
	extern int yylineno;
    fprintf(stderr, "line(%d): %s \n", yylineno, str);
    return 0;
}
