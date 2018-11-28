
Project2: main.o fifo.o
	gcc -o Project2 main.o fifo.o

main.o: src/main.c
	gcc -c src/main.c

fifo.o: src/fifo.c inc/fifo.h
	gcc -c src/fifo.c

unittest.o: unittest/unittest.c src/fifo.c
	gcc -o unit_test unittest/unittest.c src/fifo.c
	
clean:
	rm main.o fifo.o unittest.o
	
unittest: unittest.o
	./unittest/unit_test
	


























