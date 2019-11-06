#pragma once
#include "AST.h"

#define WHITESPACE "  "

class PrintAST : public Visitor{
private:
	int level;
	inline void LEVEL(int level);
public:
	PrintAST(): level(0) {}
	void visit(Node & n);
	void visit(ASTNode & n);
	void visit(DefVarNode & n);
	void visit(DefFunctionNode & n);
	void visit(BlockNode & n);
	void visit(TypeNode & n);
	void visit(BasicTypeNode & n);
	void visit(WhileNode & n);
	void visit(ForNode & n);
	void visit(IfNode & n);
	void visit(BinaryNode & n);
	void visit(UnaryNode & n);
	void visit(LiteralNumberNode & n);
	void visit(VariableNode & n);
	void visit(FunctionCallNode & n);
	void visit(ReturnNode & n);
	void visit(NopNode & n);
	void visit(VoidNode & n);
	void visit(ContinueNode & n);
	void visit(BreakNode & n);
};