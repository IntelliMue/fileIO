CPPFLAGS += -Wall -Wextra -Wpedantic

BINS = fileIO.exe

FILES = fileTest.txt

DIRS = dirTest

CC = gcc

all: $(BINS)

fileIO.exe: validation.o
	gcc validation.o -o fileIO.exe

debug: CFLAGS += -g
debug: all

profile: CFLAGS += -pg
profile: all

.PHONY: clean all

clean:
	$(RM) *.o *.a $(BINS) $(FILES)
	rm -rf $(DIRS)
