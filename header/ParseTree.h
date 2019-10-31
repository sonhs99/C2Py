#pragma once

typedef enum _NodeKind {
	Plus, Minus, Mul, Div, Pos, Neg, Assign,
	Greater, EquGre, Less, EquLess, Equ, NotEqu, In, Not,
	Func, Proc, If, For, Else, While, Return, Nop, Elif,
	Num, Ident, Int, Float,
	Root, Void, Type, Decl, Var, Block, Param
} NodeKind;

typedef struct TreeNode{
	NodeKind type;
	void * data;
	struct TreeNode * child;
	struct TreeNode * sibling;
} ParseTree;

#ifdef __cplusplus
extern "C" {
#endif

ParseTree *	CreatePT(NodeKind type, char * data, ParseTree * ch, ParseTree * s);
void		DeletePT(ParseTree * head);
void 		PrintPT(ParseTree * head, int level);

#ifdef __cplusplus
}
#endif
