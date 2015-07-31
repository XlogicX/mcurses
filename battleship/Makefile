
battleship_p: battleship util/polypatch.pl /usr/bin/perl
        perl util/polypatch.pl battleship

battleship: battleship.o
        gcc -m32 -o battleship battleship.o

battleship.o: src/battleship.c src/mcurses.h
        gcc -m32 -c -o battleship.o src/battleship.c

clean:
        rm *.o battleship
