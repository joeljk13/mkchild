CFLAGS = -g -O2 -Wall

mkchld: mkchld.o

.PHONY: clean
clean:
	rm -f mkchld *.[ios]
