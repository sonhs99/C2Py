#include <ParseTree.h>
#include <stdlib.h>
#include <stdio.h>
#include "yacc.tab.h"

#define LEVEL(level) for(int i = 0; i < level; i++) printf("  ");

ParseTree * CreatePT(NodeKind type, char * data, ParseTree * ch, ParseTree * s){
	ParseTree * node = malloc(sizeof(ParseTree));
	node->type = type;
	node->data = data;
	node->child = ch;
	node->sibling = s;
	return node;
}

void DeletePT(ParseTree * head){
	if(head == NULL) return;
	free(head->data);
	DeletePT(head->sibling);
	DeletePT(head->child);
	free(head);
}

void PrintPT(ParseTree * head, int level){
	if(head == NULL) return;
	LEVEL(level)
	if(head->type == Root) printf("< / : %s >\n", (char*)(head->data));
	else if(head->type == Func) printf("< function : %s >\n", (char*)(head->data));
	else if(head->type == Var) printf("< variable : %s >\n", (char*)(head->data));
	else if(head->type == Proc) printf("< funcCall : %s >\n", (char*)(head->data));
	else printf("< %s >\n", head->data == NULL ? getOp(head->type) : (char*)(head->data));
	PrintPT(head->child, level + 1);
	PrintPT(head->sibling, level);
}

const char * getOp(NodeKind code){
	switch(code){
		case Plus: case Pos: return "+";
		case Minus: case Neg: return "-";
		case Mul: return "*";
		case Div: return "/";
		case Assign: return "=";
		case Greater: return "<";
		case EquGre: return "<=";
		case Less: return ">";
		case EquLess: return ">=";
		case Equ: return "==";
		case NotEqu: return "!=";
		case Not: return "!";
		case If: return "if";
		case Elif: return "elif";
		case Else: return "else";
		case While: return "While";
		case Return: return "return";
		case Type: return "type";
		case Decl: return "decl";
		case Decls: return "decls";
		case Var: return "var";
		case Block: return "block";
		case Param: return "param";
		case Void: return "void";
	}
	return "Unknown";
}