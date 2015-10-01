
INCLUDE=../list/include -I.
LIBS=-L ../list/lib -lreadline -lncurses -Llib/ -lmylib
CC=gcc
CFLAGS=-Wall -g -I$(INCLUDE)
DEBUG= 

mydash: shell.o	error.o	Job.o 
	$(CC) $(CFLAGS) $(DEBUG) -o $@ shell.o error.o Job.o $(LIBS)
	mv ./mydash ..

dox:
	echo "Generating documentation using doxygen..."
	doxygen doxygen-config > doxygen.log
	echo "Use konqueror docs/html/index.html to see docs (or any other browser)"

clean:
	/bin/rm -f *.o $(PROGS) a.out core  *.log
	/bin/rm -fr docs
