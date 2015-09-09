CFLAGS = -g -O2 -Wall

mkchild: mkchild.o

.PHONY: clean
clean:
	rm -f mkchild *.[ios]
