CC	= gcc
CFLAGS = -g
RM = rm -f

default: all

all: lab2

Lab2: lab2.c
	$(CC) $(CFLAGS) -o lab2 lab2.c

clean veryclean:
	$(RM) lab2