CC=g++
CPPFLAGS=-Wall
CPPVERSION=c++17
TARGET=file_io
OBJECTS=main.o file_io.o

$(TARGET): $(OBJECTS)
	$(CC) -std=$(CPPVERSION) $(CPPFLAGS) -o $(TARGET) $(OBJECTS)

main.o: file_io.h main.cpp
	$(CC) -std=$(CPPVERSION) $(CPPFLAGS) -c main.cpp

file_io.o: file_io.h file_io.cpp
	$(CC) -std=$(CPPVERSION) $(CPPFLAGS) -c file_io.cpp