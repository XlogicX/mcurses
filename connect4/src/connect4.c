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
	mcurses_addstr(0,2, "   ..", 0, 16);
	mcurses_addstr(0,3, "  .  .", 0, 16);
	mcurses_addstr(0,4, " .    .", 0, 16);
	mcurses_addstr(0,5, " .    .", 0, 16);
	mcurses_addstr(0,6, "  .  .", 0, 16);
	mcurses_addstr(0,7, "   ..   \x01\x01", 0, 16);
	mcurses_addstr(0,8, "       \x01  \x01", 0, 16);
	mcurses_addstr(0,9, "      \x01    \x01", 0, 16);
	mcurses_addstr(0,10,"      \x01    \x01", 0, 16);
	mcurses_addstr(0,11,"       \x01  \x01", 0, 16);
	mcurses_addstr(0,12,"Connect \x01\x01", 0, 16);
	mcurses_addstr(0,13," Four", 0, 16);
	mcurses_refresh();

	void draw_board(){
		//Draw Empty Board
		mcurses_clear();
		mcurses_addstr(0,15,"----------------", 0, 16); //Floor of board
		//Draw the verticle lines
		int i = 0;
		while (i < 15) {
			mcurses_vlineyl(i,1,14, '|');
			i += 2;			
		}
		//Fill the right side
		i = 1;
		while (i < 15) {
			mcurses_addch(15,i, 'x');
			i++;
		}
		mcurses_refresh();
	}

	char board[7][14];
	board[0][4] = 'd';

	void update_peices() {
		int bx = 0;
		int dx = 1;
		while (bx < 7) {
			mcurses_addch(dx, 0, board[0][bx]);
			bx++;
			dx += 2;
		}
	}

	update_peices();
	mcurses_refresh();
}
