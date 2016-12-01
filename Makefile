PROGRAM = Kingdom
CC = gcc
CFLAGS = -Wall -c
LDFLAGS =  -lGL -lGLU -lglut -lm
DEP=defines.h prototypes.h kingdom_main.h structs.h
OBJ= kingdom_main.o general.o globals.o drawing.o init.o screen.o window.o models.o print.o loadTexture.o loadObject.o sidebar.o shapes.c

%.o: %.c $(DEP)
	$(CC) $(CFLAGS) -c -o $@ $<

$(PROGRAM): $(OBJ)
	$(CC) $(LDFLAGS) -o $(PROGRAM) $^

.PHONY: clean beauty

clean:
	-rm *.o $(PROGRAM) *~

beauty:
	indent -kr *.c

