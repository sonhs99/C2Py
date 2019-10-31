%{
#include <stdio.h>
#include <stdlib.h>
#include <ParseTree.h>
%}

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
%type<node> expr_list term 

%parse-param {
	struct TreeNode ** pt
}

%%
program
	:MAINPROG IDENT SEMICOLON declarations subprograms block {
		$4->sibling = $5; $5->sibling = $6;
		$$ = CreatePT(Root, $2, $4, NULL);
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
	:subprogram subprograms { $1->sibling = $2; $$ = $1; }
	| { $$ = CreatePT(Void, NULL, NULL, NULL); }
	
subprogram
	:subprogram_head declarations block {
		if($1->child->sibling == NULL) $1->child->sibling = $2;
		else $1->child->sibling->sibling = $2;
		$2->sibling = $3;
		$$ = $1;
	}

subprogram_head
	:FUNCTION IDENT args COLON standard_type {
		$3->sibling = $5;
		$$ = CreatePT(Func, $2, $3, NULL);
	}
	|FUNCTION IDENT args SEMICOLON { $$ = CreatePT(Func, $2, $3, NULL); }
	
args
	:LPAREN params RPAREN { $$ = $2;}
	| { $$ = CreatePT(Void, NULL, NULL, NULL); }
	
params
	:identifier_list COLON type { $1->sibling = $3; $$ = CreatePT(Param, NULL, $1,NULL);}
	|identifier_list COLON type SEMICOLON params { 
		$1->sibling = $3;
		$$ = CreatePT(Param, NULL, $1, $5); 
	}
	
block
	:BEG stmts END{ $$ = CreatePT(Block, NULL, $2, NULL); }

stmts
	:stmt stmts{ $1->sibling = $2; $$ = $1; }
	| { $$ = NULL; }
	
stmt
	:variable ASS expr SEMICOLON { $1->sibling = $3; $$ = CreatePT(Assign, NULL, $1, NULL); }
	|procedure SEMICOLON { $$ = $1; }
	|block
	|if
	|while
	|for
	|RETURN expr SEMICOLON { $$ = CreatePT(Return, NULL, $2, NULL); }
	|NOP SEMICOLON { $$ = CreatePT(Nop, NULL, NULL, NULL); }
	
if
	: IF expr COLON stmt elif else{
		$2->sibling = $4; $4->sibling = $5; $5->sibling = $6;
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
    extern char *yytext;
	extern int yylineno;
    fprintf(stderr, "Error : line (%d) %s, parser error near \"%s\"\n", yylineno, str, yytext);
    return 0;
}
