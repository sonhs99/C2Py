#include "AST.h"
#include "TypeResolver.h"
#include <iostream>

void TypeResolver::visit(Node & n){
	std::cerr << "line ( ) : Unknown AST Node" << std::endl;
}
void TypeResolver::visit(ASTNode & n){
	std::for_each(n.defvars.begin(), n.defvars.end(), [=](Node * n){ 
		n->accept(*this);
	} );
	std::for_each(n.defunc.begin(), n.defunc.end(), [=](Node * n){
		n->accept(*this);
	} );
}
void TypeResolver::visit(DefVarNode & n){
	n.type->accept(*this);
	int a = actual;
	int s = size;
	for(auto n : n.names){
		now->addVar(n.first, a, s);
		if(n.second != NULL) {
			n.second->accept(*this);
			if(!IsConvertable(actual, a))
				std::cerr << "line ( ) : cannot convert '" << ResolveType(a) << "' to '" << ResolveType(actual) <<"'" << std::endl;
		}
	} 
}
void TypeResolver::visit(DefFunctionNode & n){
	n.retype->accept(*this);
	ret = actual;
	std::vector<int> arg;
	now = new SymbolTable(now);
	usage = true;
	std::for_each(n.args.begin(), n.args.end(), [=, &arg](Node * n){ 
		n->accept(*this);
		arg.push_back(actual);
	} );
	root->addFunc(n.name, ret, arg);
	now->Nomalize();
	n.block->accept(*this);
}
void TypeResolver::visit(BlockNode & n){
	if(!usage) now = new SymbolTable(now);
	usage = false;
	now->getParent()->addTable(now);
	std::for_each(n.vars.begin(), n.vars.end(), [=](Node * n){ 
		n->accept(*this);
	} );
	n.scope = now;
	std::for_each(n.stmts.begin(), n.stmts.end(), [=](Node * n){ 
		n->accept(*this);
	} );
	now = now->getParent();
}
void TypeResolver::visit(TypeNode & n){
	n.basic->accept(*this); 
	int temp = actual * 2;
	size = 1;
	if(n.size != NULL) { 
		temp++;
		n.size->accept(*this); 
		if(actual != 2 || size < 0)
			std::cerr << "line ( ) : size of array must be a positive integer" << std::endl;
		if(size < 0) size = 0;
	}
	actual = temp;
}
void TypeResolver::visit(BasicTypeNode & n){
	switch(n.type){
		case Int:
			actual = 1;
			break;
		case Float:
			actual = 2;
			break;
		default:
			actual = 0;
			break;
	}
}
void TypeResolver::visit(WhileNode & n){
	n.cond->accept(*this); 
	n.stmt->accept(*this); 
	if(n.Else != NULL)
		n.Else->accept(*this); 
}
void TypeResolver::visit(ForNode & n){
	if(((BinaryNode*)n.cond)->lhs->getT() != Node::VARIABLE){
		std::cerr << "line ( ) : 'for' statement must have a variable" << std::endl;
	}
	else {
		if(n.stmt->getT() != Node::BLOCK){
			auto temp = n.stmt;
			(n.stmt = new BlockNode());
			((BlockNode*)n.stmt)->addStatement(temp);
		}
		((BinaryNode*)n.cond)->rhs->accept(*this);
		if(actual == 0);
		else if(actual/2 == 0 || actual % 2 == 0){
			std::cerr << "line ( ) : 'for' statement must have an iterable array" << std::endl;
		}
		else{
			now = new SymbolTable(now);
			usage = true;
			now->addVar(((VariableNode*)((BinaryNode*)n.cond)->lhs)->name, actual/2, 1);
		}
	}
	n.stmt->accept(*this); 
	if(n.Else != NULL)
		n.Else->accept(*this); 
}
void TypeResolver::visit(IfNode & n){
	n.cond->accept(*this); 
	n.stmt->accept(*this); 
	std::for_each(n.elif.begin(), n.elif.end(), [=](Node * n){
		n->accept(*this);
	} ); 
	if(n.Else != NULL){
		n.Else->accept(*this); 
	}
}
void TypeResolver::visit(BinaryNode & n){
	n.lhs->accept(*this);
	int e = actual;
	bool l = lvalue;
	n.rhs->accept(*this);
	if(!e || !actual){
		if(e) actual = e;
		lvalue = false;
		return;
	}
	switch(n.type){
		case In:
			if(actual%2 == 0){
				std::cerr << "line ( ) : rhs of 'In' must have a array";
				actual = 0;
				break;
			}
			if(!IsConvertable(e, actual - 1)){
				std::cerr << "line ( ) : cannot convert '" << ResolveType(e) << "' to '" << ResolveType(actual - 1) <<"'" << std::endl;
			}
			else if(e != actual - 1)
				n.lhs = new CastNode(actual, n.lhs);
			actual = 2;
			break;
		case Array:
			if(e%2 == 0){
				std::cerr << "line ( ) : rhs of 'In' must have a array";
				actual = 0;
				lvalue = true;
				break;
			}
			if(actual != 2)
				std::cerr << "line ( ) : cannot convert '" << ResolveType(actual) << "' to 'int'" << std::endl;
			actual = e - 1;
			lvalue = true;
			return;
		case Assign:
			if(!l){
				std::cerr << "line ( ) : lhs of '=' must be lvalue " << std::endl;
			}
			if(!IsConvertable(e, actual))
				std::cerr << "line ( ) : cannot convert '" << ResolveType(e) << "' to '"<< ResolveType(actual) << "'" << std::endl;
			else if(e != actual)
				n.rhs = new CastNode(e, n.rhs);
			lvalue = true;
			return;
		case Plus:
		case Minus:
		case Div:
		case Mul:
			if(e%2 || actual%2){
				std::cerr << "line ( ) : Arithmetic Operator cannot hold array(s) as an operend" << std::endl;
				actual = 4;
				break;
			}
			if(e != actual){
				if(e == 4){
					if(!IsConvertable(actual, 4))
						std::cerr << "line ( ) : cannot convert '" << ResolveType(actual) << "' to 'float'" << std::endl;
					else n.rhs = new CastNode(4, n.rhs);
				}
				else if(actual == 4){
					if(!IsConvertable(e, 4))
						std::cerr << "line ( ) : cannot convert '" << ResolveType(e) << "' to 'float'" << std::endl;
					else n.lhs = new CastNode(4, n.lhs);
				}
				else
					std::cerr << "line ( ) : unknown type" << std::endl;
				actual = 4;
			}
			break;
		default:
			if(e%2 || actual%2){
				std::cerr << "line ( ) : Relational Operator cannot hold array(s) as an operend" << std::endl;
				actual = 2;
				break;
			}
			if(e != actual){
				if(e == 4){
					if(!IsConvertable(actual, 4))
						std::cerr << "line ( ) : cannot convert '" << ResolveType(actual) << "' to 'float'" << std::endl;
					else n.rhs = new CastNode(4, n.rhs);
				}
				else if(actual == 4){
					if(!IsConvertable(e, 4))
						std::cerr << "line ( ) : cannot convert '" << ResolveType(e) << "' to 'float'" << std::endl;
					else n.lhs = new CastNode(4, n.lhs);
				}
				else
					std::cerr << "line ( ) : unknown type" << std::endl;
			}
			actual = 2;
	}
	lvalue = false;
}
void TypeResolver::visit(UnaryNode & n){
	n.expr->accept(*this);
	switch(n.type){
		case Pos:
		case Neg:
			if(IsConvertable(actual, 2)){
				std::cerr << "line ( ) : cannot convert '" << ResolveType(actual) << "' to 'int'" << std::endl;
			}
			break;
		case Not:
			if(IsConvertable(actual, 2)){
				std::cerr << "line ( ) : cannot convert '" << ResolveType(actual) << "' to 'int'" << std::endl;
			}
			if(actual != 2)
				n.expr = new CastNode(2, n.expr);
			actual = 2;
			break;
		default:
			break;
	}
	lvalue = false;
}
void TypeResolver::visit(LiteralNumberNode & n){
	bool dot = false;
	std::for_each(n.val.begin(), n.val.end(), [=, &dot](char c){
		if(c == '.' && !dot) dot = true; 
	} );
	if(dot) actual = 4; //실수
	else {
		actual = 2;
		size = stoi(n.val);
	} //정수
	lvalue = false;
}
void TypeResolver::visit(VariableNode & n){
	try{
		actual = now->searchVar(n.name).type;
		lvalue = true;
	} catch(int){
		try{
			func = &(now->searchFunc(n.name));
			actual = 1;
			lvalue = false;
		}catch(int){
			actual = 0;
			lvalue = false;
		std::cerr << "line ( ) : '" << n.name << "' is not defined in the scope" << std::endl;
		}
	}
}
void TypeResolver::visit(FunctionCallNode & n){
	n.name->accept(*this);
	if(actual != 1){
		std::cerr << "line ( ) : lhs cannot call as function" << std::endl;
	}
	else if(func->args.size() != n.args.size()){
		std::cerr << "line ( ) : argument size is not matched" << std::endl;
	}
	bool IsEnd = actual != 1 || func->args.size() != n.args.size();
	int i = 0;
	for(Node *& n : n.args){ 
		n->accept(*this);
		if(!IsEnd){
			if(IsConvertable(actual,func->args[i]))
				if(actual != func->args[i]) n = new CastNode(func->args[i], n);
			else
				std::cerr << "line ( ) : cannot convert '" << ResolveType(actual) << "' to '" << ResolveType(func->args[i]) <<"'" << std::endl;
		}
		i++;
	}
	actual = IsEnd ? 0 : func->ret;
	lvalue = false;
}
void TypeResolver::visit(ReturnNode & n){
	n.expr->accept(*this);
	if(!IsConvertable(actual, ret)){
		std::cerr << "line ( ) : cannot convert '" << ResolveType(actual) << "' to '" << ResolveType(ret) <<"'" << std::endl;
	}
	else if(actual != ret)
		n.expr = new CastNode(ret, n.expr);
}
void TypeResolver::visit(NopNode & n){
}

void TypeResolver::visit(VoidNode & n){
	actual = 0;
	size = 0;
	lvalue = false;
}

void TypeResolver::visit(BreakNode & n){
}

void TypeResolver::visit(ContinueNode & n){
}

void TypeResolver::visit(CastNode & n){
	n.expr->accept(*this);
	actual = n.type;
}

bool TypeResolver::IsConvertable(int from, int to){
	if(from == to) return true;
	if(from%2 || to%2) return false;
	if((from/2 - 1)*(from/2 - 2) >= 0 &&
	  (to/2 - 1)*(to/2 - 2) >= 0) return true;
	return false;
}