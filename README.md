# mcurses
A curses like library that 'draws' in memory instead of stdout

Documentation will come soon, but you can learn everything you need to know from the mcurses.h file (which is not too large) and the PoC battleship.c file.

The compiled code is intended to be self-modifying. The program will segfault without patching for this. A patcher perl script is also included with this project. An example of using it with a compiled battleship would be:
perl polypatcher.pl battleship

These games/programs are meant to be played/viewed from within a debugger. Development is being tested in GNU/Linux 32-bit with the edb debugger.
