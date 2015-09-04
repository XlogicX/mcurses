/*
Connect 4 - mcurses edition

Features to come
	-Determine win condition
	-Animation
	-AI
	-Better Welcome routine
*/
#include <stdio.h>
#include <stdlib.h>
#include "mcurses.h"
#include <unistd.h>
#include "autostep.h"

#define RED		'\x01'
#define BLACK 	'.'

int killchild() {
	//File mutex ( don't want to bother with mutexes on forked threads)	
	FILE *fp = fopen("filetex", "wb");
	fclose(fp);
}

int paintboard() {
	//Print the Walls
	int x = 0;
	int y = 1;
	while (x < 15) {
		while (y < 15) {
			mcurses_addch(x,y,'|');
			y++;
		}
		y = 1;
		x += 2;
	}
	//Print the Bottom
	mcurses_addstr(0,15,"###############", 0,16);
	//Print the Logo
	mcurses_addch(15,2,'C');
	mcurses_addch(15,3,'o');
	mcurses_addch(15,4,'n');
	mcurses_addch(15,5,'n');
	mcurses_addch(15,6,'e');
	mcurses_addch(15,7,'c');
	mcurses_addch(15,8,'t');
	mcurses_addch(15,10,'F');
	mcurses_addch(15,11,'o');
	mcurses_addch(15,12,'u');
	mcurses_addch(15,13,'r');									
}

//GLOBAL DATA, oh shit no! Still trying to find a use for a GOTO somewhere...
//Init autosteping (F9) forked-thread parameters
int pid;			//process id
pthread_t tid1;		//thread id
int delay = 500;	//looping speed

//Init the Pieces
char pieces[7][14] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
					' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
					' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
					' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
					' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
					' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
					' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',};

int drawpieces() {
	int x = 1;
	int y = 14;
	int n = 0;
	int m = 0;
	while (m < 14) {
		while (n < 7) {
			mcurses_addch(x, y, pieces[n][m]);
			n++;
			x += 2;
		}
		n = 0;
		x = 1;
		m++;
		y--;
	}
	mcurses_addstr(0,0,"                ",0,16);
}

int makemove(char color) {
	//get which row [c]
	int c; char x; int i = 0;
	while (i < 7) {
		x = mcurses_getch((i*2)+1,0); if (x != ' ') { c = i; }
		i++;
	}

	//find next available column to drop on [d]
	int d = 0;
	while (pieces[c][d] != ' ') {
		d++;
	}

	pid = fork();			//for fork
	if (pid == 0) {			//if not forked yet
		// threaded Child process to animate
		pthread_create(&tid1, NULL, &autostep, (void *)&delay); //fork it
		pthread_join(tid1,NULL);								//done
	} else if (pid > 0) {
		int falling_height = 13;
		while (falling_height > d) {
			pieces[c][falling_height] = color;
			drawpieces(pieces);
			mcurses_refresh();
			pieces[c][falling_height] = ' ';
			falling_height--;
		}	
		killchild();
	}

	pieces[c][d] = color;
	drawpieces(pieces);
	usleep(150000);
}

int win_screen(char color) {
	mcurses_clear();
	mcurses_addstr(4,5, "[-------]", 0, 16);
	mcurses_addstr(4,6, "|       |", 0, 16);
	mcurses_addstr(4,7, "|       |", 0, 16);		
	mcurses_addstr(4,8, "[-------]", 0, 16);
	if (color == '.') {
		mcurses_addstr(6, 6, "Black", 0, 16);
	} else {
		mcurses_addstr(6, 6, "Red", 0, 16);
	}
	mcurses_addstr(6, 7, "WINS!", 0, 16);
	mcurses_refresh();
	exit(0);
}

char win_check(char color) {
	//an algorithm (with DFA) would be rad, but I'm gonna do this
	//simple and tedious way (check every possible winning condition)

	//Check for wins along all rows
	int row = 0;
	int col = 0;
	while (row < 14) {
		while (col < 4) {
			if (pieces[col][row] == color && 
				pieces[col+1][row] == color && 
				pieces[col+2][row] == color && 
				pieces[col+3][row] == color) 
					{win_screen(color);}
			col++;
		}
		col = 0;
		row++;
	}

	//Check for wins along all columns
	int column = 0;
	int r = 0;
	while (column < 7) {
		while (r < 11) {
			if (pieces[column][r] == color && 
				pieces[column][r+1] == color && 
				pieces[column][r+2] == color && 
				pieces[column][r+3] == color) 
					{win_screen(color);}
			r++;
		}
		r = 0;
		column++;
	}

	//Check for diagonal wins that are bottom left to top right
	row = 0;
	col = 0;
	while (row < 11) {
		while (col < 4) {
			if (pieces[col][row] == color && 
				pieces[col+1][row+1] == color && 
				pieces[col+2][row+2] == color && 
				pieces[col+3][row+3] == color) 
					{win_screen(color);}
			col++;
		}
		col = 0;
		row++;
	}

	//Check for diagonal wins that are top left to bottom right
	row = 0;
	col = 0;
	while (row < 11) {
		while (col < 4) {
			if (pieces[col][row+3] == color && 
				pieces[col+1][row+2] == color && 
				pieces[col+2][row+1] == color && 
				pieces[col+3][row] == color) 
					{win_screen(color);}
			col++;
		}
		col = 0;
		row++;
	}
}

int welcome() {

	pid = fork();			//for fork
	if (pid == 0) {			//if not forked yet
		// threaded Child process to animate
		pthread_create(&tid1, NULL, &autostep, (void *)&delay); //fork it
		pthread_join(tid1,NULL);								//done
	} else if (pid > 0) {
		
		int row = 0;
		while (row < 11) {
			mcurses_clear();
			mcurses_addstr(3, row,"..", 0, 16);
			mcurses_addstr(2, row + 1,"....", 0, 16);
			mcurses_addstr(1, row + 2,"......", 0, 16);
			mcurses_addstr(1, row + 3,"......", 0, 16);
			mcurses_addstr(2, row + 4,"....", 0, 16);
			mcurses_addstr(3, row + 5,"..", 0, 16);
			row++;
			mcurses_refresh();
		}

		row = 0;
		while (row < 11) {
			mcurses_addstr(10, row,"\x01\x01", 0, 16);
			mcurses_addstr(9, row + 1,"\x01\x01\x01\x01", 0, 16);
			mcurses_addstr(8, row + 2,"\x01\x01\x01\x01\x01\x01", 0, 16);
			mcurses_addstr(8, row + 3,"\x01\x01\x01\x01\x01\x01", 0, 16);
			mcurses_addstr(9, row + 4,"\x01\x01\x01\x01", 0, 16);
			mcurses_addstr(10, row + 5,"\x01\x01", 0, 16);
			mcurses_refresh();
			if (row < 10) {
				mcurses_addstr(10, row,"  ", 0, 16);
				mcurses_addstr(9, row + 1,"    ", 0, 16);
				mcurses_addstr(8, row + 2,"      ", 0, 16);
				mcurses_addstr(8, row + 3,"      ", 0, 16);
				mcurses_addstr(9, row + 4,"    ", 0, 16);
				mcurses_addstr(10, row + 5,"  ", 0, 16);
			}	
			row++;		
		}

		row = 0;
		while (row < 9) {
			mcurses_addstr(2, row,"Connect Four", 0, 16);
			mcurses_addstr(2, row + 1,"============", 0, 16);
			mcurses_refresh();
			if (row < 8) {
				mcurses_addstr(2, row,"            ", 0, 16);
				mcurses_addstr(2, row + 1,"            ", 0, 16);
			}	
			row++;		
		}		

		killchild();
	}

	usleep(150000);
	mcurses_refresh();
}

int main() {
	mcurses_init();	//GET ELF memory address

	welcome();

	mcurses_clear();
	paintboard();
	mcurses_addch(15,0, BLACK);
	mcurses_refresh();



	// Main Input loop
	while (1) {
		makemove(BLACK);
		mcurses_addch(15,0, RED);
		win_check(BLACK);
		mcurses_refresh();
		
		makemove(RED);
		mcurses_addch(15,0, BLACK);
		win_check(RED);
		mcurses_refresh();
	}

return 0;
}






/*
==========================
|  Animation Framework   |
==========================

	----------------------
	| Onetime setup vars |
	----------------------

	int pid;			//process id
	pthread_t tid1;		//thread id
	int delay = 500;	//looping speed

	---------------------------------------------
	| Do all this each time animation is needed |
	---------------------------------------------

	pid = fork();			//for fork
	if (pid == 0) {			//if not forked yet
		// threaded Child process to animate
		pthread_create(&tid1, NULL, &autostep, (void *)&delay); //fork it
		pthread_join(tid1,NULL);								//done
	} else if (pid > 0) {
		// The Parent (main) process

		//Do The actual stuff and things (animation)
		killchild();
	}

*/
