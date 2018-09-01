CC = g++
CFLAGS = -Wall -std=c++14
DEPS = header.h macro.h
OBJ = global.o listDirectories.o handleCommands.o commands.o delete.o create.o rename.o goto.o copy.o snapshot.o move.o search.o main.o

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

tfe: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *o
