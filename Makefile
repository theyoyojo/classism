CC = gcc
CFLAGS = -g -Wall -Werror -pedantic -ansi -std=c11
OBJECTS = main.o vector.o class_vector.o

driver: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o driver
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
vector.o: vector.c
	$(CC) $(CFLAGS) -c vector.c -o vector.o
class_vector.o: class_vector.c
	$(CC) $(CFLAGS) -c class_vector.c -o class_vector.o
clean:
	rm driver $(OBJECTS)
