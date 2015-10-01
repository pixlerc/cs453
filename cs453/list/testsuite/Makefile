
INSTALL=..
INCLUDE=$(INSTALL)/include -I.
LIBS=$(INSTALL)/lib
LFLAGS=-L$(LIBS) -lmylib
CC=gcc
CFLAGS=-Wall -g  -I$(INCLUDE)

PROGS=RandomTestList SimpleTestList UnitTestList

all: $(PROGS)


RandomTestList: RandomTestList.o Object.o
	$(CC) $(CFLAGS) -o $@ $^  $(LFLAGS)
	cp ./RandomTestList ..

SimpleTestList: SimpleTestList.o Object.o
	$(CC) $(CFLAGS) -o $@ $^   $(LFLAGS)
	cp ./SimpleTestList ..

UnitTestList: UnitTestList.o Object.o
	$(CC) $(CFLAGS) -o $@ $^   $(LFLAGS)
	cp ./UnitTestList ..

clean:
	rm --force list *.o $(PROGS)
