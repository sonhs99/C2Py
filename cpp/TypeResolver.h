#pragma once
#include "AST.h"
#include <vector>
#include <string>

struct TypeInfo{
	int offset;
	int type;
	int size;
	int storage;
	enum { STACK = 0, HEAP, STATIC };
	std::string name;
	TypeInfo(std::string & n, int o, int t, int s, int st = STACK): name(n), offset(o), type(t), size(s), storage(st) {};
};

struct FunctionInfo{
	std::string name;
	int ret;
	std::vector<int> args;
	FunctionInfo(std::string const & n, int r, std::vector<int> const & arg): name(n), ret(r), args(arg) {};
};

class SymbolTable{
private:
	std::string name;
	std::vector<TypeInfo> vars;
	std::vector<FunctionInfo> funcs;
	std::vector<SymbolTable *> sub;
	SymbolTable * parent;
	int size = 0;
	int temp = 0;
	int base = 0;
	
public:
	SymbolTable(SymbolTable * p = NULL) : parent(p) { }
	~SymbolTable(){
		std::for_each(sub.begin(), sub.end(), [=](SymbolTable * s){ delete s; } );
	}
	void addVar(std::string & n, int type, int s, int st = TypeInfo::STACK);
	void addFunc(std::string const & n, int ret, std::vector<int> const & arg);
	void addTable(SymbolTable * t);
	void Nomalize(int i = 0);
	TypeInfo & searchVar(std::string & n);
	FunctionInfo & searchFunc(std::string & n);
	SymbolTable * getParent(){ return parent; }
	void print();
	friend void PrintTable(SymbolTable * t, int level, int temp);
	void setTemporaryStorage(int s) { temp = ((temp > s) ? temp : s); }
	int getTemporarySize() { return temp; }
	int getVariableSize() { return size;}
	void SizeNomalize(int s = 0);
	int getBaseSize(){ return base; }
};

class TypeResolver : public Visitor {
private:
	SymbolTable * root;
	SymbolTable * now;
	
	FunctionInfo * func = NULL;
	
	int actual;
	int ret;
	int size;
	int stack = 0;
	int temp = 0;
	
	bool lvalue = false;
	bool usage = false;
	
	static bool IsConvertable(int a, int b);
	
public:
	TypeResolver() : root(new SymbolTable()) { 
		now = root;
		std::string print = "print";
		root->addFunc(print, 0, {4});
		root->addTable(new SymbolTable(root));
	};
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

void PrintTable(SymbolTable * t, int level, int temp = 0);
const char * ResolveType(int type);