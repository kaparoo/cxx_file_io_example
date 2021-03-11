target: main.o file_io.o
	g++ -o file_io main.o file_io.o

main.o: file_io.h main.cpp
	g++ -c main.cpp

file_io.o: file_io.h file_io.cpp
	g++ -c file_io.cpp

clean:
	rm *.o