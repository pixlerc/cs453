all: library

library:	
	cd list; make clean; make; cp lib/* ..;
	cd ..
	cd dash; make

clean:
	rm mydash libmylib.*; cd list; make clean; cd ../dash; make clean;
