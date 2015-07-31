#include <stdio.h>
#include "mcurses.h"

/*
This file is just a non-playable proof of concept for some
of the visual elements and routines of mcurses.h. It looks
like a BattleShip game, but is not playable after you get
through the intro screens.
*/

int main() {

	mcurses_init();	//GET ELF memory address

	/* Print the game splash screen */
	mcurses_clear();
	mcurses_addstr(0,0, "~~~~~~~~~~~~~~~~", 0, 16);
	mcurses_addstr(0,1, "~~~~~~~~~||~~~~~", 0, 16);
	mcurses_addstr(0,2, "~~~~---------~~~", 0, 16);
	mcurses_addstr(0,3, "~~~/_________\\~~", 0, 16);
	mcurses_addstr(0,4, "~~~~~~~~~~~~~~~~", 0, 16);
	mcurses_addstr(0,5, "~~~~~~~~~---~~~~", 0, 16);
	mcurses_addstr(0,6, "~~~~~~~~~|.|~~~~", 0, 16);
	mcurses_addstr(0,7, "~~~~~~~~~|.|~~~~", 0, 16);
	mcurses_addstr(0,8, "~~~~~~~~~|_|~~~~", 0, 16);
	mcurses_addstr(0,9, "................", 0, 16);
	mcurses_addstr(0,10,"..BATTLE SHIP!..", 0, 16);
	mcurses_addstr(0,11,"................", 0, 16);
	mcurses_addstr(0,12,"................", 0, 16);
	mcurses_addstr(0,13,"................", 0, 16);
	mcurses_addstr(0,14,".Insert Coin:[ ]", 0, 16);
	mcurses_addstr(0,15,"................", 0, 16);	
	mcurses_refresh();
	
	/* Check to see if coin has been inserted
		If not, complain and exit
		Otherwise, start the game and explain
		game peices */
	char coin;
	coin = mcurses_getch(14,14);
	mcurses_clear();
	if (coin == '$') {
		mcurses_addstr(0,1,"On the next", 0, 16);
		mcurses_addstr(0,2,"screen, place", 0, 16);
		mcurses_addstr(0,3,"your boats",0, 16);
		mcurses_addstr(0,5,"Boats:", 0, 16);
		mcurses_addstr(1,6,"** patrol", 0, 16);
		mcurses_addstr(1,7,"*** submarine", 0, 16);
		mcurses_addstr(1,8,"**** battleship", 0, 16);
		mcurses_addstr(1,9,"***** aircraft", 0, 16);
		mcurses_addstr(7,10,"carrier", 0,16);
	} else {
		mcurses_addstr(0,7,"You call that", 0, 16);
		mcurses_addstr(4,8,"COINZ\?\?!!", 0, 16);
		mcurses_addstr(0,9,"A ( ) not be a",0,16);
		mcurses_addch(3,9,coin);
		mcurses_addstr(4,10,"money!",0,16);
		mcurses_refresh();
		return;
	}
	mcurses_refresh();

	/* Print the empty playing board */
	mcurses_clear();
	mcurses_addstr(0,0,"-----[Enemy]----", 0, 16);
	mcurses_addstr(0,8,"------[You]-----", 0, 16);
	mcurses_refresh();
}
