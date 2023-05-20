CC = gcc
EXEC = program
CFLAGS = -Wall 
OBJ = main.o parent.o child.o

ifdef FANCY
CLAGS += -D FANCY
FANCY : clean $(EXEC)
endif

ifdef DEBUG
CFLAGS += -D DEBUG
DEBUG : 
	clean $(EXEC)
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) 

main.o : main.c header.h 
	$(CC) $(CFLAGS) -c main.c 

child.o : child.c 
	$(CC) $(CFLAGS) -c child.c

parent.o : parent.c 
	$(CC) $(CFLAGS) -c parent.c

clean:
	rm -f $(EXEC) $(OBJ)