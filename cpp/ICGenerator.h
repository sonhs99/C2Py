#pragma once
#include <string>
#include "AST.h"

class ArrayDescriptor{
private:
	int size;
	int count;
	int element;
	void * array;
public:
};

class Operand{
public:
	friend class ICGenerator;
	enum Kind{ };
	Operand(Kind k) : kind(k) {};
	
private:
	Kind kind;
};	

class Opcode{
public:
	friend class ICGenerator;
	enum Kind{ };
	Opcode(Kind k, Operand * d, Operand * s1, Operand * s2):
		kind(k), des(d), src1(s1), src2(s2) {};
	~Opcode(){
		delete des;
		delete src1;
		delete src2;
	}
	void print();
private:
	Kind kind;
	Operand * des, * src1, * src2;
};

class ICGenerator : public Visitor{
private:
	int stack = 0;
public:
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
	void visit(CastNode & n);
};

