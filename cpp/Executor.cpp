#include "Executor.h"
#include <iostream>

void Executor::execute(std::vector<Opcode*> & code){
	Data *des = NULL, *src1 = NULL, *src2 = NULL;
	for(;PC < code.size();PC++){
		switch(code[PC]->kind){
			case ADD:
				des = resolve(code[PC]->des);
				src1 = resolve(code[PC]->src1);
				src2 = resolve(code[PC]->src2);
				switch(des->type){
					case Data::NOTALLOC:
						if(src1->type == Data::INT){
							des->ival = src1->ival + src2->ival;
							des->type = Data::INT;
						}
						else if(src1->type == Data::FLOAT){
							des->fval = src1->fval + src2->fval;
							des->type = Data::FLOAT;
						}
						break;
					case Data::INT:
						des->ival = src1->ival + src2->ival;
						break;
					case Data::FLOAT:
						des->fval = src1->fval + src2->fval;
						break;
				}
				break;
			case SUB:
				des = resolve(code[PC]->des);
				src1 = resolve(code[PC]->src1);
				src2 = resolve(code[PC]->src2);
				switch(des->type){
					case Data::NOTALLOC:
						if(src1->type == Data::INT){
							des->ival = src1->ival - src2->ival;
							des->type = Data::INT;
						}
						else if(src1->type == Data::FLOAT){
							des->fval = src1->fval - src2->fval;
							des->type = Data::FLOAT;
						}
						break;
					case Data::INT:
						des->ival = src1->ival - src2->ival;
						break;
					case Data::FLOAT:
						des->fval = src1->fval - src2->fval;
						break;
				}
				break;
			case DIV:
				des = resolve(code[PC]->des);
				src1 = resolve(code[PC]->src1);
				src2 = resolve(code[PC]->src2);
				switch(des->type){
					case Data::NOTALLOC:
						if(src1->type == Data::INT){
							des->ival = src1->ival / src2->ival;
							des->type = Data::INT;
						}
						else if(src1->type == Data::FLOAT){
							des->fval = src1->fval / src2->fval;
							des->type = Data::FLOAT;
						}
						break;
					case Data::INT:
						des->ival = src1->ival / src2->ival;
						break;
					case Data::FLOAT:
						des->fval = src1->fval / src2->fval;
						break;
				}
				break;
			case MUL:
				des = resolve(code[PC]->des);
				src1 = resolve(code[PC]->src1);
				src2 = resolve(code[PC]->src2);
				switch(des->type){
					case Data::NOTALLOC:
						if(src1->type == Data::INT){
							des->ival = src1->ival * src2->ival;
							des->type = Data::INT;
						}
						else if(src1->type == Data::FLOAT){
							des->fval = src1->fval * src2->fval;
							des->type = Data::FLOAT;
						}
						break;
					case Data::INT:
						des->ival = src1->ival * src2->ival;
						break;
					case Data::FLOAT:
						des->fval = src1->fval * src2->fval;
						break;
				}
				break;
			case POS:
				des = resolve(code[PC]->des);
				src1 = resolve(code[PC]->src1);
				switch(des->type){
					case Data::NOTALLOC:
						if(src1->type == Data::INT){
							des->ival = +src1->ival;
							des->type = Data::INT;
						}
						else if(src1->type == Data::FLOAT){
							des->fval = +src1->fval;
							des->type = Data::FLOAT;
						}
						break;
					case Data::INT:
						des->ival = +src1->ival;
						break;
					case Data::FLOAT:
						des->fval = +src1->fval;
						break;
				}
				break;
			case NEG:
				des = resolve(code[PC]->des);
				src1 = resolve(code[PC]->src1);
				switch(des->type){
					case Data::NOTALLOC:
						if(src1->type == Data::INT){
							des->ival = -src1->ival;
							des->type = Data::INT;
						}
						else if(src1->type == Data::FLOAT){
							des->fval = -src1->fval;
							des->type = Data::FLOAT;
						}
						break;
					case Data::INT:
						des->ival = -src1->ival;
						break;
					case Data::FLOAT:
						des->fval = -src1->fval;
						break;
				}
				break;
			case NOT:
				des = resolve(code[PC]->des);
				src1 = resolve(code[PC]->src1);
				des->ival = src->ival;
				des->type = Data::INT;
				break;
			case EQU:
				des = resolve(code[PC]->des);
				src1 = resolve(code[PC]->src1);
				src2 = resolve(code[PC]->src2);
				break;
			case NEQ:
				des = resolve(code[PC]->des);
				src1 = resolve(code[PC]->src1);
				src2 = resolve(code[PC]->src2);
				break;
			case GRE:
				des = resolve(code[PC]->des);
				src1 = resolve(code[PC]->src1);
				src2 = resolve(code[PC]->src2);
				break;
			case LES:
				des = resolve(code[PC]->des);
				src1 = resolve(code[PC]->src1);
				src2 = resolve(code[PC]->src2);
				break;
			case GEQ:
				des = resolve(code[PC]->des);
				src1 = resolve(code[PC]->src1);
				src2 = resolve(code[PC]->src2);
				break;
			case LEQ:
				des = resolve(code[PC]->des);
				src1 = resolve(code[PC]->src1);
				src2 = resolve(code[PC]->src2);
				break;
			case IN:
				des = resolve(code[PC]->des);
				src1 = resolve(code[PC]->src1);
				src2 = resolve(code[PC]->src2);
				break;
			case PUSH:
				src1 = resolve(code[PC]->src1);
				break;
			case POP:
				des = resolve(code[PC]->des);
				break;
			case CALL:
				des = resolve(code[PC]->des);
				break;
			case RET:
				src1 = resolve(code[PC]->src1);
				break;
			case MOV:
				des = resolve(code[PC]->des);
				src1 = resolve(code[PC]->src1);
				break;
			case JZ:
				des = resolve(code[PC]->des);
				src1 = resolve(code[PC]->src1);
				break;
			case JMP:
				des = resolve(code[PC]->des);
				break;
			case ITF:
				des = resolve(code[PC]->des);
				src1 = resolve(code[PC]->src1);
				break;
			case FTI:
				des = resolve(code[PC]->des);
				src1 = resolve(code[PC]->src1);
				break;
			case ALC:
				des = resolve(code[PC]->des);
				src1 = resolve(code[PC]->src1);
				break;
			case PRT:
				src1 = resolve(code[PC]->src1);
				break;
		}
		//delete des; des = NULL;
		//delete src1; src1 = NULL;
		//delete src2; src2 = NULL;
	}
}