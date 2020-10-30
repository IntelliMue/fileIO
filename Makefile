CPPFLAGS += -Wall -Wextra -Wpedantic

CFLAGS += -std=c11

ARFLAGS += -U

BINS = fileIOTest

LIBS = fileIO.a

FILES = fileTest.txt

DIRS = dirTest

CC = gcc

all: $(BINS)

lib: $(LIBS)

fileIOTest: SRC/fileIOTest.o fileIO.a
	gcc SRC/fileIOTest.o fileIO.a -o fileIOTest
	$(RM) SRC/fileIOTest.o

fileIO.a: fileIO.a(SRC/fileIO.o)

debug: CFLAGS += -g
debug: all

profile: CFLAGS += -pg
profile: all

.PHONY: clean all

clean:
	$(RM) *.o *.a $(BINS) $(FILES)
	$(RM) -rf $(DIRS)
