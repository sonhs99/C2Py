#include "AST.h"
#include <iostream>
#include <unistd.h>

Node * ASTGenerate(ParseTree * pt){
	if(pt == NULL) return NULL;
	Node * temp_a, * temp_b; 
	switch(pt->type){
		case Void: return new VoidNode();
		case Nop: return new NopNode();
		case Num: return new LiteralNumberNode(pt->data);
		case Int:
		case Float: return new BasicTypeNode(pt->type);
		case Var: return new VariableNode(pt->data,ASTGenerate(pt->child));
		case Return: return new ReturnNode(ASTGenerate(pt->child));
		case Type:
			return new TypeNode(ASTGenerate(pt->child), ASTGenerate(pt->child->sibling));
		case Pos:
		case Neg:
		case Not: return new UnaryNode(pt->type, ASTGenerate(pt->child));
		case Plus:
		case Minus:
		case Mul:
		case Div:
		case Assign:
		case Greater:
		case EquGre:
		case Less:
		case EquLess:
		case Equ:
		case NotEqu:
		case In:
			temp_a = ASTGenerate(pt->child->sibling);
			return new BinaryNode(pt->type, ASTGenerate(pt->child), temp_a);
		case For:
		case While:
			temp_a = ASTGenerate(pt->child->sibling->sibling);
			temp_b = ASTGenerate(pt->child->sibling);
			return new LoopNode(ASTGenerate(pt->child), temp_b, temp_a);
		case If:
		case Elif:
			temp_b = new IfNode( ASTGenerate(pt->child),
								ASTGenerate(pt->child->sibling),
								ASTGenerate(pt->child->sibling->sibling->sibling)
			);
			for(auto temp_a = pt->child->sibling->sibling->child; temp_a != NULL; temp_a = temp_a->sibling) 
				((IfNode *)temp_b)->addElif(ASTGenerate(temp_a));
			return temp_b;
		case Block:
			temp_b = new BlockNode();
			for(auto temp_a = pt->child; temp_a != NULL; temp_a = temp_a->sibling)
				((BlockNode *)temp_b)->addStatement(ASTGenerate(temp_a));
			return temp_b;
		case Proc:
			temp_b = new FunctionCallNode(pt->data);
			for(auto temp_a = pt->child->sibling->child; temp_a != NULL; temp_a = temp_a->sibling)
				((FunctionCallNode *)temp_b)->addArg(ASTGenerate(temp_a));
			return temp_b;
		case Func:
			temp_b = new DefFunctionNode(pt->data,
										ASTGenerate(pt->child->sibling),
										ASTGenerate(pt->child->sibling->sibling->sibling));
			for(auto temp_a = pt->child->child; temp_a != NULL; temp_a = temp_a->sibling)
				((DefFunctionNode *)temp_b)->addArg(ASTGenerate(temp_a));
			for(auto temp_a = pt->child->sibling->sibling->child; temp_a != NULL; temp_a = temp_a->sibling)
				((DefFunctionNode *)temp_b)->addVar(ASTGenerate(temp_a));
			return temp_b;
		case Param:
		case Decl:
			temp_b = new DefVarNode(ASTGenerate(pt->child));
			for(auto temp_a = pt->child->sibling; temp_a != NULL; temp_a = temp_a->sibling)
				((DefVarNode *)temp_b)->addName(temp_a->data);
			return temp_b;
		case Root:
			temp_b = new ASTNode(pt->data, ASTGenerate(pt->child->sibling->sibling));
			for(auto temp_a = pt->child->child; temp_a != NULL; temp_a = temp_a->sibling)
				((ASTNode *)temp_b)->addVar(ASTGenerate(temp_a));
			for(auto temp_a = pt->child->sibling->child; temp_a != NULL; temp_a = temp_a->sibling)
				((ASTNode *)temp_b)->addFunc(ASTGenerate(temp_a));
			return temp_b;
	}
	return NULL;
}

void ASTNode::accept(Visitor & v) { v.visit(*this); }
void DefVarNode::accept(Visitor & v) { v.visit(*this); }
void TypeNode::accept(Visitor & v) { v.visit(*this); }
void BasicTypeNode::accept(Visitor & v) { v.visit(*this); }
void DefFunctionNode::accept(Visitor & v) { v.visit(*this); }
void BlockNode::accept(Visitor & v) { v.visit(*this); }
void LoopNode::accept(Visitor & v) { v.visit(*this); }
void BinaryNode::accept(Visitor & v) { v.visit(*this); }
void UnaryNode::accept(Visitor & v) { v.visit(*this); }
void LiteralNumberNode::accept(Visitor & v) { v.visit(*this); }
void VariableNode::accept(Visitor & v) { v.visit(*this); }
void FunctionCallNode::accept(Visitor & v) { v.visit(*this); }
void ReturnNode::accept(Visitor & v) { v.visit(*this); }
void NopNode::accept(Visitor & v) { v.visit(*this); }
void IfNode::accept(Visitor & v) { v.visit(*this); }
void VoidNode::accept(Visitor & v) { v.visit(*this); }

