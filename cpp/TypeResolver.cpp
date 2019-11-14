#include "AST.h"
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
	if(!root.getSymbol(n.name))
		std::cout << "line ( ) : EntryPoint is not found" << std::endl;
}
void TypeResolver::visit(DefVarNode & n){
	int e = 0;
	n.type->accept(*this); 
	e = expect;
	std::for_each(n.names.begin(), n.names.end(), [=](auto n){
		now->addSymbol(n.first, e);
		if(n.second != NULL) {
			n.second->accept(*this);
			IsConvertable(e, expect);
		}
	} ); 
}
void TypeResolver::visit(DefFunctionNode & n){
	int i = 0;
	std::cout << "< DefFunction >" << std::endl;
	std::cout << "name : " << n.name << std::endl;
	std::cout << "return : " << std::endl;
	n.retype->accept(*this);
	ret = actual;	
	std::cout << "args : " << std::endl;
	std::for_each(n.args.begin(), n.args.end(), [=, &i](Node * n){ 
		LEVEL(level - 1); std::cout << "[ " << i << " ]" << std::endl;
		n->accept(*this); i++;
	} ); 
	std::cout << "block : " << std::endl; 
	if(n.block != NULL) {n.block->accept(*this); }
}
void TypeResolver::visit(BlockNode & n){
	int i = 0;
	std::cout << "< Block >" << std::endl;
	std::cout << "vars : " << std::endl;
	std::for_each(n.vars.begin(), n.vars.end(), [=, &i](Node * n){ 
		LEVEL(level - 1); std::cout << "[ " << i << " ]" << std::endl;
		n->accept(*this); i++;
	} ); i = 0;
	std::cout << "stmts : " << std::endl;
	std::for_each(n.stmts.begin(), n.stmts.end(), [=, &i](Node * n){ 
		LEVEL(level - 1); std::cout << "[ " << i << " ]" << std::endl;
		n->accept(*this); i++;
	} ); 
}
void TypeResolver::visit(TypeNode & n){
	n.basic->accept(*this); 
	actual *= 2;
	if(n.size != NULL) { 
		actual++;
		n.size->accept(*this); 
	}
}
void TypeResolver::visit(BasicTypeNode & n){
	actual = n.type;
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
	actual = IsConvertable(e, actual);
}
void TypeResolver::visit(UnaryNode & n){
	n.expr->accept(*this); 
}
void TypeResolver::visit(LiteralNumberNode & n){
	bool dot = false;
	std::for_each(n.val.begin(), n.val.end(), [=, &dot](char c){
		if(c == '.' && !dot) dot = true; 
	} );
	if(dot); //실수
	else ; //정수
}
void TypeResolver::visit(VariableNode & n){
	actual = now->searchSymbol(n.name);
	if(n.expr != NULL){
		if(actual & 1 != 1)
			std::cout << "line ( ) : '" << n.name << "' is not List" << std::endl;
		n.expr->accept(*this); 
	}
}
void TypeResolver::visit(FunctionCallNode & n){
	int i = 0;
	std::cout << "< FunctionCall >" << std::endl;
	std::cout << "name : " << n.name << std::endl;
	LEVEL(level); std::cout << "args : " << std::endl;
	std::for_each(n.args.begin(), n.args.end(), [=, &i](Node * n){ 
		LEVEL(level - 1); std::cout << "[ " << i << " ]" << std::endl;
		n->accept(*this); i++;
	} ); 
}
void TypeResolver::visit(ReturnNode & n){
	n.expr->accept(*this); 
	IsConvertable(actual, ret);
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