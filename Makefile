INC=-I/CUnit/CUnit-2.1-3/CUnit/Headers/
LIB=-L/CUnit/CUnit-2.1-3/CUnit/Sources/.libs/
LIBS=C:\cygwin64\ECEN5813\Project2\CUnit\CUnit-2.1-3\CUnit\Sources\.libs\libcunit.a \
	 C:\cygwin64\ECEN5813\Project2\CUnit\CUnit-2.1-3\CUnit\Sources\Basic\.libs\libcunitbasic.a \
	 C:\cygwin64\ECEN5813\Project2\CUnit\CUnit-2.1-3\CUnit\Sources\libcunit_test.a 	
	 
Project2: main.o fifo.o
	gcc -o Project2 main.o fifo.o

unittest: unittest.o fifo.o
	gcc -LCunit -o unit_test unittest.o fifo.o $(LIBS)
	./unit_test
	
main.o: src/main.c
	gcc -c src/main.c

fifo.o: src/fifo.c inc/fifo.h
	gcc -c src/fifo.c

unittest.o: unittest/unittest.c
	gcc -c unittest/unittest.c
	
clean:
	rm main.o fifo.o unittest.o
	



























