CC = g++
CFLAGS = -Wall -std=c++14
DEPS = header.h macro.h
OBJ = global.o listDirectories.o handleCommands.o main.o 

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

tfe: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
