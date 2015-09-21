CFLAGS = -g -O2 -Wall
prefix = ~/bin

mkchild: mkchild.o

.PHONY: install
install:
	mkdir -p $(prefix)
	cp mkchild $(prefix)

.PHONY: uninstall
uninstall:
	rm -f $(prefix)/mkchild

.PHONY: clean
clean:
	rm -f mkchild *.[ios]
