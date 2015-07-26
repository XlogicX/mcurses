# mcurses
A curses like library that 'draws' in memory instead of stdout

Documentation will come soon, but you can learn everything you need to know from the mcurses.h file (which is not too large) and the PoC battleship.c file.

When compiling battleship.c (or you're own program that uses the mcurses library), the file will need to be hand hacked to be rwx for now (instead of r-x). I will soon include instructions for this. A more automated way to do this will eventually be prefered.

These games/programs are meant to be played/viewed from within a debugger. Development is being tested in GNU/Linux 32-bit with the edb debugger.
