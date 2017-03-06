CC ?= cc

CFLAGS := 
LDFLAGS := -lwlc

.PHONY: all clean
all: asc

clean:
	-rm *.o

asc: asc.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c %.h
	$(CC) -o $@ -c $< $(CFLAGS)


