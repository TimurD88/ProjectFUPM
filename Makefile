# Makefile 4


CC=gcc
CFLAGS=-I.
DEPS = pdp.h
OBJ = pdp11.o pdp_run.o


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


hellomake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
