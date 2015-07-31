# mcurses
A curses like library that 'draws' in memory instead of stdout

Documentation will come soon, but you can learn everything you need to know from the mcurses.h file (which is not too large) and the PoC battleship.c file.

These games/programs are meant to be played/viewed from within a debugger. Development is being tested in GNU/Linux 32-bit with the edb debugger. If you are compiling from a 64-bit distribution, you may need to install the g++-multilib library (usually straight forward with a package manager i.e. 'sudo apt-get install g++-multilib').

To compile, just run 'make' from within the battleship directory (where the Makefile is).
