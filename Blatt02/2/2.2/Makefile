CC_FINAL=gcc
CC_GDB=gdb

CFLAGS_STD= -std=c99
CFLAGS_FINAL= -O0 $(CFLAGS_STD)
CFLAGS_DEBUG= -O3 -DDEBUG=1 $(CFLAGS_STD)
CFLAGS_GDB= -ggdb -O0 $(CFLAGS_STD)

MAIN=valArray.c
EXECUTABLE=valArray.x

all:
	$(CC_FINAL) $(CFLAGS_FINAL) -o $(EXECUTABLE) $(MAIN)

debug:
	$(CC_FINAL) $(CFLAGS_DEBUG) -o $(EXECUTABLE) $(MAIN)

gdb:
	$(CC_FINAL) $(CFLAGS_GDB) -o $(EXECUTABLE) $(MAIN)

clean:
	rm job.x *.x *.o

cleanlog:
	rm log/*
