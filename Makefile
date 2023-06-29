CC = gcc

BASE_C_GLOBS = $(wildcard *.c)
BASE_OBJ_GLOBS = $(BASE_C_GLOBS:.c=.o)

CFLAGS = -Os -Wall
LDFLAGS = -lcurl

CC_CMD = $(CC) -c -o $@ $< $(CFLAGS)
LD_CMD = $(CC) -o $@ $< $(LDFLAGS)

PROG = packmux

all: $(PROG)

$(PROG): $(BASE_OBJ_GLOBS)
	$(LD_CMD)
