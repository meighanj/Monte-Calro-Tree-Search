CC=   g++
DEL_FILE= rm -f 
CFLAGS    = -W -Wall -g

SOURCES   = io.cc \
						MCTS.cc

OBJECTS   = io.o \
      			main.o	\
						MCTS.o 
				
TARGET    = exec

all: main

main: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(CFLAGS)

io.o: io.cc
	$(CC) io.cc -c $(CFLAGS)

MCTS.o: MCTS.cc
	$(CC) MCTS.cc -c $(CFLAGS)

clean: 
	-$(DEL_FILE) $(OBJECTS) $(TARGET) 

