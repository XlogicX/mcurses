connect4p: connect4 src/polypatch.pl /usr/bin/perl
	perl src/polypatch.pl connect4

connect4: connect4.o
	gcc -m32 -o connect4 connect4.o -lX11 -lXtst -lpthread

connect4.o: src/connect4.c src/mcurses.h src/autostep.h
	gcc -m32 -c -o connect4.o src/connect4.c

clean:
	rm *.o connect4
