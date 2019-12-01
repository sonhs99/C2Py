#include "ICGenerator.h"
#include <iostream>

void ICGenerator::visit(Node & n){ }
void ICGenerator::visit(ASTNode & n){
	for(Node * n : n.defvars){ 
		n->accept(*this);
	}
	for(Node * n : n.defunc){
		n->accept(*this);
	}
}
void ICGenerator::visit(DefVarNode & n){
	for(auto n : n.names){
		auto var = scope->searchVar(n.first);
		if(var.type % 2 && var.size != 0)
			codes.push_back(new Opcode(Opcode::ALC,
								   new VariableOp(Operand::Variable, var.offset), 
								   new LiteralOp(var.size),
								   NULL));
		else if(n.second != NULL) {
			n.second->accept(*this);
			codes.push_back(new Opcode(Opcode::MOV,
								   new VariableOp(Operand::Variable, var.offset), 
								   operand,
								   NULL));
		}
	}
}
void ICGenerator::visit(DefFunctionNode & n){
	labels.insert(std::make_pair(n.name, codes.size()));
	codes.push_back(new Opcode(Opcode::PUSH,
								   NULL, 
								   new RegisterOp(RegisterOp::BP),
								   NULL));
	codes.push_back(new Opcode(Opcode::MOV,
								   new RegisterOp(RegisterOp::BP), 
								   new RegisterOp(RegisterOp::SP),
								   NULL));
	for(Node * arg : n.args)
		arg->accept(*this);
	n.block->accept(*this);
	codes.push_back(new Opcode(Opcode::POP,
								   new RegisterOp(RegisterOp::SP), 
								   NULL,
								   NULL));
	codes.push_back(new Opcode(Opcode::RET,
								   NULL, 
								   new LiteralOp(int(n.args.size())),
								   NULL));
}
void ICGenerator::visit(BlockNode & n){
	int size = n.scope->getVariableSize() + n.scope->getTemporarySize();
	codes.push_back(new Opcode(Opcode::ADD,
								   new RegisterOp(RegisterOp::SP), 
								   new RegisterOp(RegisterOp::SP),
								   new LiteralOp(size)));
	auto backup = scope;
	scope = n.scope;
	for(Node * n : n.vars){
		temp = 0;
		n->accept(*this);
	}
	for(Node * n : n.stmts){ 
		temp = 0;
		n->accept(*this);
	}
	scope = backup;
	codes.push_back(new Opcode(Opcode::SUB,
								   new RegisterOp(RegisterOp::SP), 
								   new RegisterOp(RegisterOp::SP),
								   new LiteralOp(size)));
}
void ICGenerator::visit(TypeNode & n){
	
}
void ICGenerator::visit(BasicTypeNode & n){
	
}
void ICGenerator::visit(WhileNode & n){
	std::string exit_number = std::string("_EXIT") + std::to_string(exit);
	std::string else_number = std::string("_ELSE") + std::to_string(Else);
	std::string loop_number = std::string("_LOOP") + std::to_string(stack + 1);
	labels.insert(std::make_pair(loop_number, codes.size()));
	n.cond->accept(*this); 
	codes.push_back(new Opcode(Opcode::JZ,
								   new LabelOp(else_number), 
								   operand));
	stack++;
	n.stmt->accept(*this); 
	codes.push_back(new Opcode(Opcode::JMP,
								   new LabelOp(loop_number), 
								   NULL ));
	stack--;
	if(n.Else != NULL)
		labels.insert(std::make_pair(else_number, codes.size()));
		n.Else->accept(*this); 
	exit++;
	labels.insert(std::make_pair(exit_number, codes.size()));
}
void ICGenerator::visit(ForNode & n){
	((BinaryNode*)n.cond)->rhs->accept(*this);
	stack++;
	n.stmt->accept(*this); 
	stack--;
	if(n.Else != NULL)
		n.Else->accept(*this); 
}
void ICGenerator::visit(IfNode & n){
	std::string exit_number = std::string("_EXIT") + std::to_string(exit);
	std::string else_number = std::string("_ELSE") + std::to_string(Else);
	n.cond->accept(*this); 
	codes.push_back(new Opcode(Opcode::JZ,
								   new LabelOp(else_number), 
								   operand));
	operand = NULL;
	n.stmt->accept(*this); 
	codes.push_back(new Opcode(Opcode::JMP,
								   new LabelOp(exit_number), 
								   NULL ));
	labels.insert(std::make_pair(else_number, codes.size()));
	Else++;
	for(Node * n : n.elif){
		temp = 0;
		n->accept(*this);
	}; 
	exit++;
	if(n.Else != NULL){
		temp = 0;
		n.Else->accept(*this); 
	}
	labels.insert(std::make_pair(exit_number, codes.size() + 1));
}
void ICGenerator::visit(BinaryNode & n){
	n.lhs->accept(*this);
	auto lhs = operand;
	n.rhs->accept(*this);
	auto rhs = operand;
	Opcode::Kind op;
	int s = scope->getVariableSize();
	switch(n.type){
		case Plus:
			op = Opcode::ADD;
			break;
		case Minus:
			op = Opcode::SUB;
			break;
		case Mul:
			op = Opcode::MUL;
			break;
		case Div:
			op = Opcode::DIV;
			break;
		case Greater:
			op = Opcode::GRE;
			break;
		case EquGre:
			op = Opcode::GEQ;
			break;
		case Less:
			op = Opcode::LES;
			break;
		case EquLess:
			op = Opcode::LEQ;
			break;
		case Equ:
			op = Opcode::EQU;
			break;
		case NotEqu:
			op = Opcode::NEQ;
			break;
		case In: //
			op = Opcode::IN;
			break;
		case Assign:
			codes.push_back(new Opcode(Opcode::MOV, lhs, rhs));
			operand = rhs->clone();
			return;
		case Array:
			codes.push_back(new Opcode(Opcode::ADD, new VariableOp(Operand::Temporary, temp + s), lhs, rhs));
			operand = new VariableOp(Operand::Variable, temp + s, true);
			return;
	}
	if(lhs->kind == Operand::Literal && rhs->kind == Operand::Literal){
		float lhs_v, rhs_v;
		if(((LiteralOp *)lhs)->IsInt) lhs_v = ((LiteralOp *)lhs)->ival;
		else lhs_v = ((LiteralOp *)lhs)->fval;
		if(((LiteralOp *)rhs)->IsInt) rhs_v = ((LiteralOp *)rhs)->ival;
		else rhs_v = ((LiteralOp *)rhs)->fval;
		switch(n.type){
			case Plus:
				lhs_v += rhs_v;
				break;
			case Minus:
				lhs_v -= rhs_v;
				break;
			case Mul:
				lhs_v *= rhs_v;
				break;
			case Div:
				lhs_v /= rhs_v;
				break;
			case Greater:
				lhs_v = lhs_v < rhs_v;
				break;
			case EquGre:
				lhs_v = lhs_v <= rhs_v;
				break;
			case Less:
				lhs_v = lhs_v > rhs_v;
				break;
			case EquLess:
				lhs_v = lhs_v >= rhs_v;
				break;
			case Equ:
				lhs_v = lhs_v == rhs_v;
				break;
			case NotEqu:
				lhs_v = lhs_v != rhs_v;
				break;
		}
		if(((LiteralOp *)lhs)->IsInt && ((LiteralOp *)rhs)->IsInt)
			operand = new LiteralOp(int(lhs_v));
		else if(n.type >= Greater && n.type <= NotEqu)
			operand = new LiteralOp(int(lhs_v));
		else
			operand = new LiteralOp(lhs_v);
		delete lhs;
		delete rhs;
	}
	else if(lhs->kind == Operand::Register && rhs->kind == Operand::Register){
		operand = new VariableOp(Operand::Temporary, temp + s);
		codes.push_back(new Opcode(op, operand->clone(), lhs, rhs));
		temp++;
	}
	else if(lhs->kind <= Operand::Variable && rhs->kind <= Operand::Variable){
		operand = new VariableOp(Operand::Temporary, temp + s);
		codes.push_back(new Opcode(op, operand->clone(), lhs, rhs));
		temp++;
	}
	else if(lhs->kind <= Operand::Variable && rhs->kind > Operand::Variable){
		operand = new VariableOp(Operand::Temporary, temp + s);
		codes.push_back(new Opcode(op, operand->clone(), lhs, rhs));
	}
	else if(lhs->kind > Operand::Variable && rhs->kind <= Operand::Variable){
		operand = new VariableOp(Operand::Temporary, temp + s);
		codes.push_back(new Opcode(op, operand->clone(), lhs, rhs));
	}
	else{
		operand = new VariableOp(Operand::Temporary, temp + s);
		codes.push_back(new Opcode(op, operand->clone(), lhs, rhs));
		temp--;
	}
}
void ICGenerator::visit(UnaryNode & n){
	n.expr->accept(*this);
	Opcode::Kind op;
	int s = scope->getVariableSize(); 
	switch(n.type){
		case Pos:
			op = Opcode::POS;
			break;
		case Neg:
			op = Opcode::NEG;
			break;
		case Not:
			op = Opcode::NOT;
			break;
	}
	if(operand->kind == Operand::Literal){
		float val;
		if(((LiteralOp *)operand)->IsInt) val = ((LiteralOp *)operand)->ival;
		else val = ((LiteralOp *)operand)->fval;
		switch(n.type){
			case Pos:
				val = +val;
				break;
			case Neg:
				val = -val;
				break;
			case Not:
				val = !val;
				break;
		}
		if(((LiteralOp *)operand)->IsInt || n.type == Not)
			operand = new LiteralOp(int(val));
		else operand = new LiteralOp(val);
		delete operand;
	}
	else if(operand->kind == Operand::Temporary){
		codes.push_back(new Opcode(op,
								   new VariableOp(Operand::Temporary, temp + s),
								   operand));
		operand = new VariableOp(Operand::Temporary, temp + s);
	}
	else {
		codes.push_back(new Opcode(op, 
								   new VariableOp(Operand::Temporary, temp + s), 
								   operand));
		operand = new VariableOp(Operand::Temporary, temp + s);
		temp++;
	}
}
void ICGenerator::visit(LiteralNumberNode & n){
	bool IsInt = false;
	int ival;
	float fval;
	for(char c : n.val){
		if(c == '.') {
			IsInt = true;
			break;
		} 
	}
	if(IsInt) {
		ival = stoi(n.val);
		operand = new LiteralOp(ival);
	}
	else {
		fval = stof(n.val);
		operand = new LiteralOp(fval);
	}
}
void ICGenerator::visit(VariableNode & n){
	int offset = 0;
	try{
		offset = scope->searchVar(n.name).offset;
	} catch(int){
		operand = new LabelOp(n.name);
		return;
	}
	operand = new VariableOp(Operand::Variable, offset);
}
void ICGenerator::visit(FunctionCallNode & n){
	n.name->accept(*this);
	auto label = operand;
	for(Node *& n : n.args){ 
		n->accept(*this);
		codes.push_back(new Opcode(Opcode::PUSH, NULL, operand, NULL));
	}
	codes.push_back(new Opcode(Opcode::CALL, label, NULL, NULL));
	operand = new RegisterOp(RegisterOp::RV);
}
void ICGenerator::visit(ReturnNode & n){
	n.expr->accept(*this);
}
void ICGenerator::visit(NopNode & n){
}

void ICGenerator::visit(VoidNode & n){
}

void ICGenerator::visit(BreakNode & n){
	std::string exit_number = std::string("_EXIT") + std::to_string(exit);
	codes.push_back(new Opcode(Opcode::JMP, new LabelOp(exit_number), NULL, NULL));
}

void ICGenerator::visit(ContinueNode & n){
	std::string loop_number = std::string("_LOOP") + std::to_string(stack);
	codes.push_back(new Opcode(Opcode::JMP, new LabelOp(loop_number), NULL, NULL));
}

void ICGenerator::visit(CastNode & n){
	n.expr->accept(*this);
	Opcode::Kind op;
	int s = scope->getVariableSize();
	if(n.type == 2) op = Opcode::FTI;
	else op = Opcode::ITF;
	if(operand->kind == Operand::Literal){
		int ival, fval;
		if(op == Opcode::FTI) {
			fval = ((LiteralOp*)operand)->ival;
			delete operand;
			operand = new LiteralOp(fval);
		}
		else {
			ival = ((LiteralOp*)operand)->fval;
			delete operand;
			operand = new LiteralOp(fval);
		}	
	}
	else if(operand->kind <= Operand::Variable){
		codes.push_back(new Opcode(op, new VariableOp(Operand::Temporary, temp + s), operand));
		operand = new VariableOp(Operand::Temporary, temp + s);
		temp++;
	}
	else{
		codes.push_back(new Opcode(op, new VariableOp(Operand::Temporary, temp + s), operand));
		operand = new VariableOp(Operand::Temporary, temp + s);
	}
}

const char * ResolveOp(Opcode::Kind op){
	switch(op){
		case Opcode::ADD:  return "ADD ";
		case Opcode::SUB:  return "SUB ";
		case Opcode::DIV:  return "DIV ";
		case Opcode::MUL:  return "MUL ";
		case Opcode::POS:  return "POS ";
		case Opcode::NEG:  return "NEG ";
		case Opcode::NOT:  return "NOT ";
		case Opcode::EQU:  return "EQU ";
		case Opcode::NEQ:  return "NEQ ";
		case Opcode::GRE:  return "GRE ";
		case Opcode::LES:  return "LES ";
		case Opcode::GEQ:  return "GEQ ";
		case Opcode::LEQ:  return "LEQ ";
		case Opcode::IN:   return "IN  ";
		case Opcode::PUSH: return "PUSH";
		case Opcode::POP:  return "POP ";
		case Opcode::CALL: return "CALL";
		case Opcode::RET:  return "RET ";
		case Opcode::MOV:  return "MOV ";
		case Opcode::JZ :  return "JZ  ";
		case Opcode::JMP:  return "JMP ";
		case Opcode::ITF:  return "ITF ";
		case Opcode::FTI:  return "FTI ";
		case Opcode::ALC:  return "ALC ";
		case Opcode::PRT:  return "PRT ";
	}
	return "void";
}

void Opcode::print(){
	std::cout << "< " << ResolveOp(kind) << " > : ";
	if(des != NULL)
		des->print();
	if(src1 != NULL)
		src1->print();
	if(src2 != NULL)
		src2->print();
	std::cout << std::endl;
}

void Operand::print(){
	switch(kind){
		case Literal:
			std::cout << "L ";
			break;
		case Register:
			std::cout << "R ";
			break;
		case Variable:
			std::cout << "V ";
			break;
		case Temporary:
			std::cout << "T ";
			break;
		case Label:
			std::cout << "<L> ";
			break;
	}
}

void LiteralOp::print(){
	std::cout << "L(";
	if(IsInt) std::cout << ival << ") ";
	else std::cout << fval << ") ";
}

void RegisterOp::print(){
	switch(i){
		case PC:
			std::cout << "PC ";
			break;
		case BP:
			std::cout << "BP ";
			break;
		case SP:
			std::cout << "SP ";
			break;
		case RV:
			std::cout << "RV ";
			break;
	}
}

void VariableOp::print(){
	if(storage == Stack) std::cout << "S(";
	else std::cout << "D(";
	std::cout << offset << ") ";
}

void LabelOp::print(){
	std::cout << "< " << name << " > "; 
}

void ICGenerator::PrintCode(){
	using Pair = std::pair<std::string, int>;
	int i = 0, j = 0;
	std::vector<std::pair<std::string, int> > labels(this->labels.begin(), this->labels.end());
	std::sort(labels.begin(), labels.end(), [](const Pair & p1, const Pair & p2)->bool{
		return p1.second < p2.second;
	});
	for(Opcode * c : codes) {
		printf("[ %4d ] %7s ", i, i != labels[j].second ? "" : labels[j].first.c_str());
		while(i == labels[j].second) j++;
		i++;
		c->print();
	} 
	for(Pair & p : labels){
		std::cout << p.first << " : " << p.second << std::endl;
	}
}

void ICGenerator::Optimize(){
	using Pair = std::pair<std::string, int>;
	std::vector<std::pair<std::string, int> > labels(this->labels.begin(), this->labels.end());
	std::sort(labels.begin(), labels.end(), [](const Pair & p1, const Pair & p2)->bool{
		return p1.second < p2.second;
	});
	for(int i = 0; i < codes.size(); i++){
		int delta = 0;
		switch(codes[i]->kind){
			case Opcode::CALL:
				if(((LabelOp*)codes[i]->des)->name == "print"){
					codes[i - 1]->kind = Opcode::PRT;
					delta = 1;
					delete codes[i];
					codes.erase(codes.begin() + i--);
					i--;
				}
				break;
			case Opcode::PRT:
				if(codes[i - 1]->kind == Opcode::ITF || codes[i - 1]->kind == Opcode::FTI){
					if(*((VariableOp*)codes[i - 1]->des) == *((VariableOp*)codes[i]->src1)){
						auto operand = codes[i - 1]->src1->clone();
						auto remove = codes[i]->src1;
						codes[i]->src1 = operand;
						delete remove;
						delete codes[i - 1];
						codes.erase(codes.begin() + --i);
						delta = 1;
					}
				}
		}
		for(Pair & label : labels)
			if(label.second >= i) label.second -= delta;
	}
	for(Pair & label : labels) this->labels[label.first] = label.second;
}