#pragma once
#include <string>
#include <vector>
#include <map>
#include "AST.h"
#include "TypeResolver.h"

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
	enum Kind{ Literal = 0, Register, Variable, Temporary, Label };
	Operand(Kind k) : kind(k) {};
	virtual void print();
	virtual Operand * clone() { return new Operand(kind); }
protected:
	Kind kind;
};

class LiteralOp : public Operand{
private:
	bool IsInt;
	union{
		int ival;
		float fval;
	};
public:
	friend class ICGenerator;
	LiteralOp(int v) :
		Operand(Literal), IsInt(true), ival(v) {};
	LiteralOp(float v) :
		Operand(Literal), IsInt(false), fval(v) {};
	void print();
	Operand * clone() { if(IsInt) return new LiteralOp(ival); else return new LiteralOp(fval); }
};

class RegisterOp : public Operand{
private:
	int i;
public:
	enum {PC = 0, BP, SP, RV};
	friend class ICGenerator;
	RegisterOp(int v) :
		Operand(Register), i(v) {};
	void print();
	Operand * clone() { return new RegisterOp(i); }
};

class VariableOp : public Operand{
private:
	int offset;
	int storage;
public:
	enum {Stack = 0, Data};
	friend class ICGenerator;
	VariableOp(Operand::Kind k, int o, bool s = false) :
		Operand(k), offset(o), storage(s ? Data : Stack) {};
	void print();
	Operand * clone() { return new VariableOp(kind, offset, storage == Data); }
};

class LabelOp : public Operand{
private:
	std::string name;
public:
	friend class ICGenerator;
	LabelOp(std::string const & n) : 
		Operand(Operand::Label), name(n) {};
	void print();
	Operand * clone() { return new LabelOp(name); }
};

class Opcode{
public:
	friend class ICGenerator;
	enum Kind{ ADD = 0, SUB, DIV, MUL, POS, NEG,
			 NOT, EQU, NEQ, GRE, LES, GEQ, LEQ, IN,
			  PUSH, POP, CALL, RET, MOV, 
			  JZ, JMP, ITF, FTI, ALC};
	Opcode(Kind k, Operand * d, Operand * s1, Operand * s2 = NULL):
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
	std::vector<Opcode*> codes;
	std::map<std::string, int> labels;
	SymbolTable * root;
	SymbolTable * scope;
	int stack = 0;
	int temp = 0;
	int Else = 0;
	int exit = 0;
	
	Operand * operand = NULL;
public:
	ICGenerator(SymbolTable * t): root(t) {};
	~ICGenerator() { for(Opcode * c : codes) delete c; }
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
	void PrintCode();
};

