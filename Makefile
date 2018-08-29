CC = g++
CFLAGS = -Wall -std=c++14
DEPS = header.h macro.h
OBJ = global.o listDirectories.o handleCommands.o main.o commands.o

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

tfe: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *o
