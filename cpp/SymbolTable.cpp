#include "TypeResolver.h"
#include <iostream>

void SymbolTable::addVar(std::string & n, int type, int s){
	vars.push_back(TypeInfo(n, size, type, s));
	int SizeOfType = 0;
	switch(type/2){
		case 1:
			SizeOfType = 4;
			break;
		case 2:
			SizeOfType = 4;
			break;
		default:
			SizeOfType = 0;
	}
	size += SizeOfType * s;
}

void SymbolTable::addFunc(std::string & n, int ret, std::vector<int> & arg){
	funcs.push_back(FunctionInfo(n, ret, arg));
}

void SymbolTable::addTable(SymbolTable * t){
	sub.push_back(t);
}

TypeInfo SymbolTable::searchVar(std::string & n){
	for(auto var : vars){	
		if(var.name == n) return var;
	}
	if(parent == NULL) throw 0;
	return parent->searchVar(n);
}

FunctionInfo SymbolTable::searchFunc(std::string & n){
	for(auto func : funcs){	
		if(func.name == n) return func;
	}
	if(parent == NULL) throw 0;
	return parent->searchFunc(n);
}

const char * ResolveType(int type){
	switch(type){
		case 1: return "func";
		case 2: return "int";
		case 3: return "int[]";
		case 4: return "float";
		case 5: return "float[]";
		default: return "void";
	}
}
	
void SymbolTable::print(){
	if(parent != NULL) parent->print();
	for(auto & var : vars){
		printf("[ %s%#04x ] : %s\t%s\t%d\n", var.offset >= 0 ? "+" : "-", var.offset>= 0 ? var.offset : -var.offset, var.name.c_str(), ResolveType(var.type), var.size);
	}
	for(auto & func : funcs){
		printf("[ FUNCT ] : %s\t%s\t(", func.name.c_str(), ResolveType(func.ret));
		for(auto arg : func.args){
			std::cout << ResolveType(arg) << ", ";
		}
		std::cout << ")" << std::endl;
	}
}

void PrintTable(SymbolTable * t, int level){
	auto i = t->sub.begin();
	for(auto & var : t->vars){
		for(int i = 0; i < level; i++) std::cout << "  ";
		printf("[ %s%#04x ] : %10s%10s %d\n", var.offset >= 0 ? "+" : "-", var.offset>= 0 ? var.offset : -var.offset, var.name.c_str(), ResolveType(var.type), var.size);
	}
	for(auto & func : t->funcs){
		for(int i = 0; i < level; i++) std::cout << "  ";
		printf("[ FUNCT ] : %10s%10s (", func.name.c_str(), ResolveType(func.ret));
		for(auto arg : func.args){
			std::cout << ResolveType(arg) << ", ";
		}
		std::cout << ")" << std::endl;
		PrintTable(*(i++), level+1);
	}
	for(;i != t->sub.end(); i++){
		PrintTable(*i, level+1);
	}
}

void SymbolTable::Nomalize(){
	for(auto & var : vars){
		var.offset -= (size + 4);
	}
	size = 0;
}

