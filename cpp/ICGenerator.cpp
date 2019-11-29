#include "ICGenerator.h"
#include <iostream>

void ICGenerator::visit(Node & n){
	std::cerr << "line ( ) : Unknown AST Node" << std::endl;
}
void ICGenerator::visit(ASTNode & n){
	std::for_each(n.defvars.begin(), n.defvars.end(), [=](Node * n){ 
		n->accept(*this);
	} );
	std::for_each(n.defunc.begin(), n.defunc.end(), [=](Node * n){
		n->accept(*this);
	} );
}
void ICGenerator::visit(DefVarNode & n){
	for(auto n : n.names){
		if(n.second != NULL) {
			n.second->accept(*this);
		}
	}
}
void ICGenerator::visit(DefFunctionNode & n){
	n.block->accept(*this);
}
void ICGenerator::visit(BlockNode & n){
	for(Node * n : n.vars){ 
		n->accept(*this);
	}
	for(Node * n : n.stmts){ 
		n->accept(*this);
	}
}
void ICGenerator::visit(TypeNode & n){
	n.basic->accept(*this); 
}
void ICGenerator::visit(BasicTypeNode & n){
	
}
void ICGenerator::visit(WhileNode & n){
	n.cond->accept(*this); 
	stack++;
	n.stmt->accept(*this); 
	stack--;
	if(n.Else != NULL)
		n.Else->accept(*this); 
}
void ICGenerator::visit(ForNode & n){
	((BinaryNode*)n.cond)->rhs->accept(*this);
	stack++;
	n.stmt->accept(*this); 
	stack--;
	if(n.Else != NULL)
		n.Else->accept(*this); 
}
void ICGenerator::visit(IfNode & n){
	n.cond->accept(*this); 
	n.stmt->accept(*this); 
	for(Node * n : n.elif){
		n->accept(*this);
	}; 
	if(n.Else != NULL){
		n.Else->accept(*this); 
	}
}
void ICGenerator::visit(BinaryNode & n){
	n.lhs->accept(*this);
	n.rhs->accept(*this);
}
void ICGenerator::visit(UnaryNode & n){
	n.expr->accept(*this);
}
void ICGenerator::visit(LiteralNumberNode & n){
	
}
void ICGenerator::visit(VariableNode & n){
	
}
void ICGenerator::visit(FunctionCallNode & n){
	n.name->accept(*this);
	for(Node *& n : n.args){ 
		n->accept(*this);
	}
}
void ICGenerator::visit(ReturnNode & n){
	n.expr->accept(*this);
}
void ICGenerator::visit(NopNode & n){
}

void ICGenerator::visit(VoidNode & n){
	
}

void ICGenerator::visit(BreakNode & n){
	if(stack == 0)
		std::cerr << "line ( ) : Break statement is outside of loop" << std::endl;
}

void ICGenerator::visit(ContinueNode & n){
	if(stack == 0)
		std::cerr << "line ( ) : Continue statement is outside of loop" << std::endl;
}

void ICGenerator::visit(CastNode & n){
	n.expr->accept(*this);
}