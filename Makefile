CC = g++
CFLAGS = -Wall -std=c++14
DEPS = header.h
OBJ = main.o

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

tfe: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
