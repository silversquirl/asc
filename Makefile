CC ?= cc

CFLAGS := -I.
LDFLAGS := -lwlc -llua

.PHONY: all clean
all: asc

clean:
	-rm *.o

asc: asc.o lua_api.o lua/lowlevel.o lua/root.o lua/consts.o
	$(CC) -o $@ $^ $(LDFLAGS)

lua_api.o: lua_api.c lua_api.h lua/lowlevel.h lua/root.h lua/consts.h
	$(CC) -o $@ -c $< $(CFLAGS)

%.o: %.c %.h
	$(CC) -o $@ -c $< $(CFLAGS)

