connect4_p: connect4 util/polypatch.pl /usr/bin/perl
	perl util/polypatch.pl connect4

connect4: connect4.o
	gcc -m32 -o connect4 connect4.o

connect4.o: src/connect4.c src/mcurses.h
	gcc -m32 -c -o connect4.o src/connect4.c

clean: 
	rm *.o connect4
