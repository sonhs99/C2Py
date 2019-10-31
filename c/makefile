CC		= gcc -c
LEX		= flex
YACC	= bison -d
LEXFILE	= lex
YACCFILE= yacc
CFILE	= lex.yy.c $(YACCFILE).tab.c ParseTree.c
TARGET	= c.o 

all: $(TARGET)

$(TARGET): $(CFILE)
	$(CC) $^ -I../header
	ld -relocatable $(CFILE:.c=.o) -o $@
	
lex.yy.c: $(LEXFILE).l $(YACCFILE).tab.h
	$(LEX) $^

$(YACCFILE).tab.c $(YACCFILE).tab.h : $(YACCFILE).y
	$(YACC) $^
	
clean:
	rm lex.yy.c
	rm $(YACCFILE).tab.h
	rm $(YACCFILE).tab.c
	rm $(CFILE:.c=.o)
	rm $(TARGET)