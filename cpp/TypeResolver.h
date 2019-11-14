#pragma once
#include <map>
#include <string>

class SymbolTable{
private:
	std::string name;
	std::map<std::string, int> symbol;
	std::map<std::string, SymbolTable> sub;
	SymbolTable * parent;
public:
	SymbolTable();
	~SymbolTable();
	void addSymbol(std::string & n, int & symbol);
	void addTable(std::string & n, SymbolTable & t);
	int searchSymbol(std::string & n);
	SymbolTable & searchTable(std::string & n);
}

class TypeResolver : public Visitor {
private:
	SymbolTable root;
	SymbolTable * now;
	int expect;
	int actual;
	int ret;
	int size;
	
	int IsConvertable(int a, int b, int Opcode);
	
public:
	TypeResolver();
	~TypeResolver();
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
}