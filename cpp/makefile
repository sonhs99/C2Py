CC = g++ -c
CFLAG = -std=c++14 -I../header
CFILE = main.cpp Parser.cpp
TARGET = cpp.o

all: $(TARGET)

$(TARGET): $(CFILE)
	$(CC) $^ $(CFLAG)
	ld -relocatable $(CFILE:.cpp=.o) -o $@
	
clean:
	rm -r $(CFILE:.cpp=.o)
	rm -r $(TARGET)