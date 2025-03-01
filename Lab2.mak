CC	= gcc
CFLAGS = -g
RM = rm -f

default: all

all: myLab2

Lab2: myLab2.c
	$(CC) $(CFLAGS) -o myLab2 myLab2.c

clean veryclean:
	$(RM) myLab2
