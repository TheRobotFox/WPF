CC=gcc
CFLAGS=-Wall -mwindows -s -Os
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:%.c=%.o)

WPF: $(OBJECTS)
	$(CC) $^ $(CFLAGS) -o $@

clean: 
	rm -f $(OBJECTS)