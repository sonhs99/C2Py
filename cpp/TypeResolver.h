#pragma once
#include "AST.h"
#include <vector>
#include <string>

struct TypeInfo{
	int offset;
	int type;
	int size;
	std::string name;
	TypeInfo(std::string & n, int o, int t, int s): name(n), offset(o), type(t), size(s) {};
};

struct FunctionInfo{
	std::string name;
	int ret;
	std::vector<int> args;
	FunctionInfo(std::string & n, int r, std::vector<int> & arg): name(n), ret(r), args(arg) {};
};

class SymbolTable{
private:
	std::string name;
	std::vector<TypeInfo> vars;
	std::vector<FunctionInfo> funcs;
	std::vector<SymbolTable *> sub;
	SymbolTable * parent;
	int size;
public:
	SymbolTable(SymbolTable * p = NULL) : parent(p), size(0) { }
	~SymbolTable(){
		std::for_each(sub.begin(), sub.end(), [=](SymbolTable * s){ delete s; } );
	}
	void addVar(std::string & n, int type, int s);
	void addFunc(std::string & n, int ret, std::vector<int> & arg);
	void addTable(SymbolTable * t);
	void Nomalize();
	TypeInfo searchVar(std::string & n);
	FunctionInfo searchFunc(std::string & n);
	SymbolTable * getParent(){ return parent; }
	void print();
	friend void PrintTable(SymbolTable * t, int level);
};

class TypeResolver : public Visitor {
private:
	SymbolTable * root;
	SymbolTable * now;
	
	int actual;
	int ret;
	int size;
	
	bool lvalue = false;
	bool usage = false;
	
	static bool IsConvertable(int a, int b);
	
public:
	TypeResolver() : root(new SymbolTable()) { now = root; };
	~TypeResolver() {};
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
	SymbolTable * getTable() { return root; }
};

void PrintTable(SymbolTable * t, int level);
const char * ResolveType(int type);