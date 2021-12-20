CC = gcc
AR = ar
FLAGS = -Wall

all: stringProg

stringProg: main.o
	$(CC) $(FLAGS) -o stringProg main.o

main.o: main.c
	${CC} $(FLAGS) -c main.c

.phony: clean

clean:
	del -fr *.a *.o stringProg
