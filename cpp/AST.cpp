#include "AST.h"
#include <iostream>

Node * ASTGenerate(ParseTree * pt){
	if(pt == NULL) return NULL;
	Node * temp_a, * temp_b; 
	switch(pt->type){
		case Void: return NULL;
		case Nop: return new NopNode(pt->line);
		case Continue: return new ContinueNode(pt->line);
		case Break: return new BreakNode(pt->line);
		case Num: return new LiteralNumberNode(pt->line, pt->data);
		case Int:
		case Float: return new BasicTypeNode(pt->line, pt->type);
		case Var: return new VariableNode(pt->line, pt->data);
		case Return: return new ReturnNode(pt->line, ASTGenerate(pt->child));
		case Type:
			return new TypeNode(pt->line, (temp_a = ASTGenerate(pt->child)) ? temp_a : new VoidNode(pt->line) , ASTGenerate(pt->child->sibling));
		case Pos:
		case Neg:
		case Not:
			return new UnaryNode(pt->line, pt->type, (temp_a = ASTGenerate(pt->child)) ? temp_a : new VoidNode(pt->line));
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
		case Array:
			temp_a = ASTGenerate(pt->child->sibling);
			if(temp_a == NULL) temp_a = new VoidNode(pt->line);
			return new BinaryNode(pt->line, 
								  pt->type, 
								  (temp_b = ASTGenerate(pt->child)) ? temp_b : new VoidNode(pt->line),
								  temp_a);
		case For:
			temp_a = ASTGenerate(pt->child->sibling->sibling);
			temp_b = ASTGenerate(pt->child->sibling);
			return new ForNode(pt->line, ASTGenerate(pt->child), temp_b, temp_a);
		case While:
			temp_a = ASTGenerate(pt->child->sibling->sibling);
			temp_b = ASTGenerate(pt->child->sibling);
			return new WhileNode(pt->line, ASTGenerate(pt->child), temp_b, temp_a);
		case If:
			temp_b = new IfNode(pt->line, 
								ASTGenerate(pt->child),
								ASTGenerate(pt->child->sibling),
								ASTGenerate(pt->child->sibling->sibling->sibling)
			);
			for(auto temp_a = pt->child->sibling->sibling->child; temp_a != NULL; temp_a = temp_a->sibling) 
				((IfNode *)temp_b)->addElif(ASTGenerate(temp_a));
			
			return temp_b;
		case Elif:
			temp_b = new IfNode( pt->line, 
								ASTGenerate(pt->child),
								ASTGenerate(pt->child->sibling),
								NULL
			);
			return temp_b;
		case Else:
			return ASTGenerate(pt->child);
		case Block:
			temp_b = new BlockNode(pt->line);
			for(auto temp_a = pt->child->child; temp_a != NULL; temp_a = temp_a->sibling)
				((BlockNode *)temp_b)->addVar(ASTGenerate(temp_a));
			for(auto temp_a = pt->child->sibling; temp_a != NULL; temp_a = temp_a->sibling)
				((BlockNode *)temp_b)->addStatement(ASTGenerate(temp_a));
			return temp_b;
		case Proc:
			temp_b = new FunctionCallNode(pt->line, ASTGenerate(pt->child));
			for(auto temp_a = pt->child->sibling->child; temp_a != NULL; temp_a = temp_a->sibling)
				((FunctionCallNode *)temp_b)->addArg(ASTGenerate(temp_a));
			return temp_b;
		case Func:
			temp_b = new DefFunctionNode(pt->line, pt->data ? pt->data : "",
										(temp_a = ASTGenerate(pt->child->sibling)) ? temp_a : new VoidNode(pt->line),
										ASTGenerate(pt->child->sibling->sibling));
			for(auto temp_a = pt->child->child; temp_a != NULL; temp_a = temp_a->sibling)
				((DefFunctionNode *)temp_b)->addArg(ASTGenerate(temp_a));
			return temp_b;
		case Param:
		case Decl:
			temp_b = new DefVarNode(pt->line, (temp_a = ASTGenerate(pt->child)) ? temp_a : new VoidNode(pt->line));
			for(auto temp_a = pt->child->sibling; temp_a != NULL; temp_a = temp_a->sibling)
				((DefVarNode *)temp_b)->addName(temp_a->data ? temp_a->data : "",
											   ASTGenerate(temp_a->child));
			return temp_b;
		case Root:
			temp_b = new ASTNode(pt->line, pt->data ? pt->data : "");
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
void ForNode::accept(Visitor & v) { v.visit(*this); }
void WhileNode::accept(Visitor & v) { v.visit(*this); }
void BinaryNode::accept(Visitor & v) { v.visit(*this); }
void UnaryNode::accept(Visitor & v) { v.visit(*this); }
void LiteralNumberNode::accept(Visitor & v) { v.visit(*this); }
void VariableNode::accept(Visitor & v) { v.visit(*this); }
void FunctionCallNode::accept(Visitor & v) { v.visit(*this); }
void ReturnNode::accept(Visitor & v) { v.visit(*this); }
void NopNode::accept(Visitor & v) { v.visit(*this); }
void IfNode::accept(Visitor & v) { v.visit(*this); }
void VoidNode::accept(Visitor & v) { v.visit(*this); }
void ContinueNode::accept(Visitor & v) { v.visit(*this); }
void BreakNode::accept(Visitor & v) { v.visit(*this); }
void CastNode::accept(Visitor & v) { v.visit(*this); }

