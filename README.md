# mcurses
A curses like library that 'draws' in memory instead of stdout

Documentation will come soon, but you can learn everything you need to know from the mcurses.h file (which is not too large) and the PoC connect4.c file. This project is hardly close to any kind of public consumption, but I like to keep these repos private as short a time as possible.

These games/programs are meant to be played/viewed from within a debugger. Development is being tested in GNU/Linux 32-bit with the edb debugger. If you are compiling from a 64-bit distribution, you may need to install the g++-multilib library (usually straight forward with a package manager i.e. 'sudo apt-get install g++-multilib').

Dependencies:
libxtst-dev (for keyboard emulation, this library may be under a different name depending on Linux distribution)
g++-multilib (if doing this in 64 bit host)

To compile, just run 'make' from within the connect4 directory (where the Makefile is)...and cross fingers

A quick demo video of what execution (from the edb debugger) looks like: http://xlogicx.net/files/connect4.mp4
