#include "ICGenerator.h"

struct Data{
	union{
		int ival;
		float fval;
	};
	int type;
	enum { NOTALLOC = 0, INT, FLOAT, EOS };
	Data(int i): type(INT), ival(i) {};
	Data(float i): type(FLOAT), fval(i) {};
	Data(): type(NOTALLOC) {};
};

class Stack : public std::stack<Data>{
public:
	using std::stack<Data>::c;
};

class Heap{
private:
	std::vector<Data> tape;
	int alloc_count = 0;
	
public:
	int Alloc(int i);
	Data & operator[](int i){
		return tape[i];
	}
}

class Executor{
private:
	Stack stack;
	Heep heap;
	int PC, BP, SP;
	Data RV;
	
public:
	Executor(): BP(0), SP(0) {};
	void execute(std::vector<Opcode*> & code);
	Data * resolve(Operand * op);
}