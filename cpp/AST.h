#pragma once
#include <ParseTree.h>
#include <string>
#include <vector>
#include <algorithm>

class Visitor;
class PrintAST;

class Node{
private:
	
public:
	friend class PrintAST;
	Node() {};
	~Node() {};
	virtual void accept(Visitor & v) = 0;
};

Node * ASTGenerate(ParseTree * pt);

class ASTNode : public Node{
private:
	std::string entry;
	std::vector<Node *> defvars;
	std::vector<Node *> defunc;
	Node * block;
public:
	friend class PrintAST;
	ASTNode(const char * ep, Node * b):
		entry(ep), block(b) {};
	void addVar(Node * n) { if(n != NULL) defvars.push_back(n); }
	void addFunc(Node * n) { if(n != NULL) defunc.push_back(n); }
	~ASTNode() {
		std::for_each(defvars.begin(), defvars.end(), [](Node * n){ delete n; });
		std::for_each(defunc.begin(), defunc.end(), [](Node * n){ delete n; });
		delete block;
	}
	void accept(Visitor & v);
};

class DefVarNode : public Node {
private:
	std::vector<std::string> names;
	Node * type;
	
public:
	friend class PrintAST;
	DefVarNode(Node * t):
		type(t) {}
	~DefVarNode() { delete type; }
	void addName(const char * n) { names.push_back(n); }
	void accept(Visitor & v);
};

class TypeNode : public Node {
private:
	Node * basic;
	Node * size;
	
public:
	friend class PrintAST;
	TypeNode(Node * b, Node * s): basic(b), size(s) {}
	~TypeNode() { delete basic; delete size; }
	void accept(Visitor & v);
};

class BasicTypeNode : public Node {
private:
	NodeKind type;
	
public:
	friend class PrintAST;
	BasicTypeNode(NodeKind t): type(t) {}
	~BasicTypeNode(){}
	void accept(Visitor & v);
};

class DefFunctionNode : public Node {
private:
	std::string name;
	std::vector<Node *> args;
	std::vector<Node *> vars;
	Node * retype;
	Node * block;
	
public:
	friend class PrintAST;
	DefFunctionNode(const char * n, Node * r, Node * b):
		name(n), retype(r), block(b) {}
	~DefFunctionNode() {
		std::for_each(args.begin(), args.end(), [](Node * n){ delete n; });
		std::for_each(vars.begin(), vars.end(), [](Node * n){ delete n; });
		delete retype;
		delete block;
	}
	void addArg(Node * a) { if(a != NULL) args.push_back(a); }
	void addVar(Node * v) { if(v != NULL) vars.push_back(v); }
	void accept(Visitor & v);
};

class BlockNode : public Node {
private:
	std::vector<Node *> stmts;
	
public:
	friend class PrintAST;
	BlockNode() {}
	~BlockNode() { std::for_each(stmts.begin(), stmts.end(), [](Node * n){ delete n; }); }
	void addStatement(Node * n) { if(n != NULL) stmts.push_back(n); }
	void accept(Visitor & v);
};

class WhileNode : public Node {
private:
	Node * cond;
	Node * stmt;
	Node * Else;
	
public:
	friend class PrintAST;
	WhileNode(Node * c, Node * s, Node * e):
		cond(c), stmt(s), Else(e) {};
	~WhileNode() { 
		delete cond; delete stmt; delete Else; 
	}
	void accept(Visitor & v);
};

class ForNode : public Node {
private:
	Node * cond;
	Node * stmt;
	Node * Else;
	
public:
	friend class PrintAST;
	ForNode(Node * c, Node * s, Node * e):
		cond(c), stmt(s), Else(e) {};
	~ForNode() { 
		delete cond; delete stmt; delete Else; 
	}
	void accept(Visitor & v);
};

class IfNode : public Node {
private:
	std::vector<Node *> elif;
	Node * cond;
	Node * stmt;
	Node * Else;

public:
	friend class PrintAST;
	IfNode(Node * c, Node * s, Node * e):
		cond(c), stmt(s), Else(e) {}
	~IfNode() {
		std::for_each(elif.begin(), elif.end(), [](Node * n){ delete n; });
		delete cond;
		delete Else;
	}
	void addElif(Node * e) { if(e != NULL) elif.push_back(e); }
	void accept(Visitor & v);
};

class BinaryNode : public Node {
private:
	NodeKind type;
	Node * lhs;
	Node * rhs;
	
public:
	friend class PrintAST;
	BinaryNode(NodeKind t, Node * l, Node * r):
		type(t), lhs(l), rhs(r) {}
	~BinaryNode() { delete lhs; delete rhs; }
	void accept(Visitor & v);
};

class UnaryNode : public Node {
private:
	NodeKind type;
	Node * expr;
	
public:
	friend class PrintAST;
	UnaryNode(NodeKind t, Node * e):
		type(t), expr(e) {}
	~UnaryNode() { delete expr; }
	void accept(Visitor & v);
};

class LiteralNumberNode : public Node {
private:
	std::string val;
	
public:
	friend class PrintAST;
	LiteralNumberNode(const char * v):
		val(v) {};
	~LiteralNumberNode() {};
	void accept(Visitor & v);
};

class VariableNode : public Node {
private:
	std::string name;
	Node * expr;
	
public:
	friend class PrintAST;
	VariableNode(const char * n, Node * e):
		name(n), expr(e) {};
	~VariableNode() { delete expr; }
	void accept(Visitor & v);
};

class FunctionCallNode : public Node {
private:
	std::string name;
	std::vector<Node *> args;
	
public:
	friend class PrintAST;
	FunctionCallNode(const char * n):
		name(n) {}
	~FunctionCallNode() { std::for_each(args.begin(), args.end(), [](Node * n){ delete n; }); }
	void addArg(Node * e) { if(e != NULL) args.push_back(e); }
	void accept(Visitor & v);
};

class ReturnNode : public Node {
private:
	Node * expr;
	
public:
	friend class PrintAST;
	ReturnNode(Node * e): expr(e) {}
	~ReturnNode() { delete expr; }
	void accept(Visitor & v);
};

class NopNode : public Node {
public:
	void accept(Visitor & v);
};

class VoidNode : public Node {
public:
	void accept(Visitor & v);
};

class Visitor{
public:
	virtual void visit(Node & n) = 0;
	virtual void visit(ASTNode & n) = 0;
	virtual void visit(DefVarNode & n) = 0;
	virtual void visit(DefFunctionNode & n) = 0;
	virtual void visit(BlockNode & n) = 0;
	virtual void visit(TypeNode & n) = 0;
	virtual void visit(BasicTypeNode & n) = 0;
	virtual void visit(WhileNode & n) = 0;
	virtual void visit(ForNode & n) = 0;
	virtual void visit(IfNode & n) = 0;
	virtual void visit(BinaryNode & n) = 0;
	virtual void visit(UnaryNode & n) = 0;
	virtual void visit(LiteralNumberNode & n) = 0;
	virtual void visit(VariableNode & n) = 0;
	virtual void visit(FunctionCallNode & n) = 0;
	virtual void visit(ReturnNode & n) = 0;
	virtual void visit(NopNode & n) = 0;
	virtual void visit(VoidNode & n) = 0;
};

