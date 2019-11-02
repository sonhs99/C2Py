LOGFILE = log.txt

all: run.out

run.out: c.o cpp.o
	g++ -o ./bin/run c/c.o cpp/cpp.o -lfl
	
c.o:
	make -C c
	
cpp.o:
	make -C cpp
	
clean:
	make -C c clean
	make -C cpp clean
	rm -r ./bin/run
	rm -r $(LOGFILE)
	
run:
	./bin/run > $(LOGFILE)