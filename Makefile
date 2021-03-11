target: main.o file_io.o
	g++ -o file_io main.o file_io

main.o: file_io.h main.c
	g++ -c main.c

file_io.o: file_io.h file_io.c
	g++ -c file_io.c

clean:
	rm *.o