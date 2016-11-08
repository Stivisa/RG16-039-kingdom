TARGET=kingdom_main
PROGRAM = Kingdom
CC = gcc
CFLAGS = -Wall -c
LDFLAGS =  -lGL -lGLU -lglut -lm


program: $(TARGET).o general.o globals.o ground.o init.o screen.o window.o
	gcc -o $(PROGRAM) $(LDFLAGS)  $(TARGET).o general.o globals.o ground.o init.o screen.o window.o
	
$(TARGET).o: $(TARGET).c defines.h prototypes.h kingdom_main.h
	$(CC) $(CFLAGS) $(TARGET).c

general.o: general.c defines.h prototypes.h kingdom_main.h
	$(CC) $(CFLAGS) general.c
	
globals.o: globals.c defines.h prototypes.h kingdom_main.h
	$(CC) $(CFLAGS) globals.c

ground.o: ground.c defines.h prototypes.h kingdom_main.h
	$(CC) $(CFLAGS) ground.c

init.o: init.c defines.h prototypes.h kingdom_main.h
	$(CC) $(CFLAGS) init.c

screen.o: screen.c defines.h prototypes.h kingdom_main.h
	$(CC) $(CFLAGS) screen.c

window.o: window.c defines.h prototypes.h kingdom_main.h
	$(CC) $(CFLAGS) window.c

.PHONY: clean beauty

clean:
	-rm *.o $(PROGRAM) 

beauty:
	indent -kr $(PROGRAM).c

