EXEC=parcours_profondeur
CC=gcc
LDFLAGS= 
CFLAGS=-W -Wall -ansi -pedantic
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC) *.dot