#include "AST.h"
#include "TypeResolver.h"
#include <iostream>

void TypeResolver::visit(Node & n){
	std::cout << "line ( ) : Unknown AST Node" << std::endl;
}
void TypeResolver::visit(ASTNode & n){
	std::for_each(n.defvars.begin(), n.defvars.end(), [=](Node * n){ 
		n->accept(*this);
	} );
	std::for_each(n.defunc.begin(), n.defunc.end(), [=](Node * n){
		n->accept(*this);
	} );
}
void TypeResolver::visit(DefVarNode & n){
	n.type->accept(*this);
	int a = actual;
	int s = size;
	std::for_each(n.names.begin(), n.names.end(), [=](auto n){
		now->addVar(n.first, a, s);
		/*if(n.second != NULL) {
			n.second->accept(*this);
			IsConvertable(a, expect, 0);
		}*/
	} ); 
}
void TypeResolver::visit(DefFunctionNode & n){
	n.retype->accept(*this);
	ret = actual;
	std::vector<int> arg;
	now = new SymbolTable(now);
	usage = true;
	std::for_each(n.args.begin(), n.args.end(), [=, &arg](Node * n){ 
		n->accept(*this);
		arg.push_back(actual);
	} );
	root->addFunc(n.name, ret, arg);
	n.block->accept(*this);
}
void TypeResolver::visit(BlockNode & n){
	if(!usage) now = new SymbolTable(now);
	usage = false;
	now->getParent()->addTable(now);
	std::for_each(n.vars.begin(), n.vars.end(), [=](Node * n){ 
		n->accept(*this);
	} );
	n.scope = now;
	std::for_each(n.stmts.begin(), n.stmts.end(), [=](Node * n){ 
		n->accept(*this);
	} );
	now = now->getParent();
}
void TypeResolver::visit(TypeNode & n){
	n.basic->accept(*this); 
	int temp = actual * 2;
	size = 1;
	if(n.size != NULL) { 
		temp++;
		n.size->accept(*this); 
	}
	actual = temp;
}
void TypeResolver::visit(BasicTypeNode & n){
	switch(n.type){
		case Int:
			actual = 1;
			break;
		case Float:
			actual = 2;
			break;
		default:
			actual = 0;
			break;
	}
}
void TypeResolver::visit(WhileNode & n){
	n.cond->accept(*this); 
	n.stmt->accept(*this); 
	if(n.Else != NULL)
		n.Else->accept(*this); 
}
void TypeResolver::visit(ForNode & n){
	n.cond->accept(*this);
	n.stmt->accept(*this); 
	if(n.Else != NULL)
		n.Else->accept(*this); 
}
void TypeResolver::visit(IfNode & n){
	n.cond->accept(*this); 
	n.stmt->accept(*this); 
	std::for_each(n.elif.begin(), n.elif.end(), [=](Node * n){
		n->accept(*this);
	} ); 
	if(n.Else != NULL){
		n.Else->accept(*this); 
	}
}
void TypeResolver::visit(BinaryNode & n){
	n.lhs->accept(*this);
	int e = actual;
	n.rhs->accept(*this); 
	actual = IsConvertable(e, actual, n.type);
}
void TypeResolver::visit(UnaryNode & n){
	n.expr->accept(*this); 
}
void TypeResolver::visit(LiteralNumberNode & n){
	bool dot = false;
	std::for_each(n.val.begin(), n.val.end(), [=, &dot](char c){
		if(c == '.' && !dot) dot = true; 
	} );
	if(dot) actual = 4; //실수
	else {
		actual = 2;
		size = stoi(n.val);
	} //정수
}
void TypeResolver::visit(VariableNode & n){
	//actual = now->searchVar(n.name).type;
}
void TypeResolver::visit(FunctionCallNode & n){
	std::for_each(n.args.begin(), n.args.end(), [=](Node * n){ 
		n->accept(*this);
	} ); 
}
void TypeResolver::visit(ReturnNode & n){
	n.expr->accept(*this); 
	//IsConvertable(actual, ret, 0);
}
void TypeResolver::visit(NopNode & n){
}

void TypeResolver::visit(VoidNode & n){
	actual = 0;
	size = 0;
}

void TypeResolver::visit(BreakNode & n){
}

void TypeResolver::visit(ContinueNode & n){
}

void TypeResolver::visit(CastNode & n){
	n.expr->accept(*this);
	actual = n.type;
}

int TypeResolver::IsConvertable(int a, int b, int Op){
	return 0;
}