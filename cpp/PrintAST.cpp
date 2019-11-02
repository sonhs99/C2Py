#include "PrintAST.h"
#include <iostream>

void PrintAST::LEVEL(int level){ for(int i = 0; i < level; i++) std::cout << WHITESPACE; }

void PrintAST::visit(Node & n){
	LEVEL(level); std::cout << "< UnknownNode >" << std::endl;
}
void PrintAST::visit(ASTNode & n){
	int i = 0;
	LEVEL(level); std::cout << "< Root >" << std::endl;
	LEVEL(level); std::cout << "Entry Point : " << n.entry << std::endl;
	LEVEL(level); std::cout << "defvar : " << std::endl;
	level++; std::for_each(n.defvars.begin(), n.defvars.end(), [=, &i](Node * n){ 
		LEVEL(level - 1); std::cout << "[ " << i << " ]" << std::endl;
		n->accept(*this); i++;
	} ); level--; i = 0;
	LEVEL(level); std::cout << "defunc : " << std::endl;
	level++; std::for_each(n.defunc.begin(), n.defunc.end(), [=, &i](Node * n){ 
		LEVEL(level - 1); std::cout << "[ " << i << " ]" << std::endl;
		n->accept(*this); i++;
	} ); level--;
	LEVEL(level); std::cout << "block : " << std::endl;
	level++; n.block->accept(*this); level--;
}
void PrintAST::visit(DefVarNode & n){
	int i = 0;
	LEVEL(level); std::cout << "< DefVar >" << std::endl;
	LEVEL(level); std::cout << "type : " << std::endl;
	level++; n.type->accept(*this); level--;
	LEVEL(level); std::cout << "names : " << std::endl;
	level++; std::for_each(n.names.begin(), n.names.end(), [=, &i](std::string n){ 
		LEVEL(level); std::cout << "[ " << i << " ] : " << n << std::endl; i++;
	} ); level--;
}
void PrintAST::visit(DefFunctionNode & n){
	int i = 0;
	LEVEL(level); std::cout << "< DefFunction >" << std::endl;
	LEVEL(level); std::cout << "name : " << n.name << std::endl;
	LEVEL(level); std::cout << "return : " << std::endl;
	level++; n.retype->accept(*this); level--;
	LEVEL(level); std::cout << "args : " << std::endl;
	level++; std::for_each(n.args.begin(), n.args.end(), [=, &i](Node * n){ 
		LEVEL(level - 1); std::cout << "[ " << i << " ]" << std::endl;
		n->accept(*this); i++;
	} ); level--; i = 0;
	LEVEL(level); std::cout << "vars : " << std::endl;
	level++; std::for_each(n.vars.begin(), n.vars.end(), [=, &i](Node * n){ 
		LEVEL(level - 1); std::cout << "[ " << i << " ]" << std::endl;
		n->accept(*this); i++;
	} ); level--;
	LEVEL(level); std::cout << "block : " << std::endl;
	if(n.block != NULL) {level++; n.block->accept(*this); level--;}
}
void PrintAST::visit(BlockNode & n){
	int i = 0;
	LEVEL(level); std::cout << "< Block >" << std::endl;
	LEVEL(level); std::cout << "stmts : " << std::endl;
	level++; std::for_each(n.stmts.begin(), n.stmts.end(), [=, &i](Node * n){ 
		LEVEL(level - 1); std::cout << "[ " << i << " ]" << std::endl;
		n->accept(*this); i++;
	} ); level--;
}
void PrintAST::visit(TypeNode & n){
	LEVEL(level); std::cout << "< Type >" << std::endl;
	LEVEL(level); std::cout << "basic type : " << std::endl;
	level++; n.basic->accept(*this); level--;
	if(n.size != NULL) { 
		LEVEL(level); std::cout << "size : " << std::endl; 
		level++; n.size->accept(*this); level--;
	}
}
void PrintAST::visit(BasicTypeNode & n){
	LEVEL(level); std::cout << "< BasicType >" << std::endl;
	LEVEL(level); std::cout << "name : " << getOp(n.type) << std::endl;
}
void PrintAST::visit(LoopNode & n){
	LEVEL(level); std::cout << "< Loop >" << std::endl;
	LEVEL(level); std::cout << "cond : " << std::endl;
	level++; n.cond->accept(*this); level--;
	LEVEL(level); std::cout << "stmt : " << std::endl;
	level++; n.stmt->accept(*this); level--;
	if(n.Else != NULL){
		LEVEL(level); std::cout << "else : " << std::endl;
		level++; n.Else->accept(*this); level--;
	}
}
void PrintAST::visit(IfNode & n){
	int i = 0;
	LEVEL(level); std::cout << "< If >" << std::endl;
	LEVEL(level); std::cout << "cond : " << std::endl;
	level++; n.cond->accept(*this); level--;
	LEVEL(level); std::cout << "stmt : " << std::endl;
	level++; n.stmt->accept(*this); level--;
	LEVEL(level); std::cout << "elif : " << std::endl;
	level++; std::for_each(n.elif.begin(), n.elif.end(), [=, &i](Node * n){ 
		LEVEL(level - 1); std::cout << "[ " << i << " ]" << std::endl;
		n->accept(*this); i++;
	} ); level--;
	if(n.Else != NULL){
		LEVEL(level); std::cout << "else : " << std::endl;
		level++; n.Else->accept(*this); level--;
	}
}
void PrintAST::visit(BinaryNode & n){
	LEVEL(level); std::cout << "< BinaryOp >" << std::endl;
	LEVEL(level); std::cout << "op : " << getOp(n.type) << std::endl;
	LEVEL(level); std::cout << "lhs : " << std::endl;
	level++; n.lhs->accept(*this); level--;
	LEVEL(level); std::cout << "rhs : " << std::endl;
	level++; n.rhs->accept(*this); level--;
}
void PrintAST::visit(UnaryNode & n){
	LEVEL(level); std::cout << "< UnaryOp >" << std::endl;
	LEVEL(level); std::cout << "op : " << getOp(n.type) << std::endl;
	LEVEL(level); std::cout << "expr : " << std::endl;
	level++; n.expr->accept(*this); level--;
}
void PrintAST::visit(LiteralNumberNode & n){
	LEVEL(level); std::cout << "< Number >" << std::endl;
	LEVEL(level); std::cout << "number : " << n.val << std::endl;
}
void PrintAST::visit(VariableNode & n){
	LEVEL(level); std::cout << "< Variable >" << std::endl;
	LEVEL(level); std::cout << "name : " << n.name << std::endl;
	if(n.expr != NULL){
		LEVEL(level); std::cout << "expr : " <<  std::endl;
		level++; n.expr->accept(*this); level--;
	}
}
void PrintAST::visit(FunctionCallNode & n){
	int i = 0;
	LEVEL(level); std::cout << "< FunctionCall >" << std::endl;
	LEVEL(level); std::cout << "name : " << n.name << std::endl;
	LEVEL(level); std::cout << "args : " << std::endl;
	level++; std::for_each(n.args.begin(), n.args.end(), [=, &i](Node * n){ 
		LEVEL(level - 1); std::cout << "[ " << i << " ]" << std::endl;
		n->accept(*this); i++;
	} ); level--;
}
void PrintAST::visit(ReturnNode & n){
	LEVEL(level); std::cout << "< Return >" << std::endl;
	LEVEL(level); std::cout << "expr : " << std::endl;
	level++; n.expr->accept(*this); level--;
}
void PrintAST::visit(NopNode & n){
	LEVEL(level); std::cout << "< Nop >" << std::endl;
}

void PrintAST::visit(VoidNode & n){
	LEVEL(level); std::cout << "< Void >" << std::endl;
}