/*
mcurses is a programming library that allows a programmer to write text-based
user interfaces in memory. This is an interaction that would typically only
be viewable while debugging a program.

Supported mcurses functions:
mcurses_addch(x,y, character) - draws a character at x,y coord
mcurses_hline(row, character) - draws a full row of characters
mcurses_vline(column, character) - draws a full column of characters
mcurses_hlinexl(x,y, length, character) - draws horizontal line starting at x with length
mcurses_vlineyl(x,y, length, character) - draws vertical line starting at y with length
mcurses_clear() - clears the entire 16x16 'screen'
mcurses_refresh() - causes 'screen' to be redrawn (with an int3 interupt)
mcurses_border() - adds a border with a character around the 16x16 grid
addstr(x,y,string,s,e) - print string at x,y, with horizontal start/stops (default 0/16)
mcurses_box(x1,y1,x2,y2,character) - make box out of character given points at upper left and lower right
getch(x,y) - get character at coord x,y and return it
*/

int address;	/*Base address for our "memory" display */

void mcurses_init() {
	//GET ELF Start
	asm ("call next;				\
		next:;						\
		pop %%eax;					\
		movl $0xFFFFF000, %%ebx;	\
		andl %%ebx, %%eax;			\
		movl %%eax, %0;"
	     :"=r"(address)        	/* output */
	     :
	     :"%eax", "%ebx"        /* clobbered register */
	     );
	//address variable now contains the ELF Start address
}

int mcurses_addch(int x, int y, char c) {
	y *= 16;		//row offset
	y += address;	//adding to base address
	x += y;			//add x coordinate to it
	asm ("movb %1, %%al;	\
		movb %%al, (%0);"
	     :
	     :"r"(x),"r"(c) 	/* input */
	     :"%eax"		/* clobbered register */
	     );
}

int mcurses_hline(int row, char c) {
	row *= 16;
	row += address;
	int i = 0;
	while (i < 16) {
		asm ("movb %1, %%al;	\
			movb %%al, (%0)"
		     :
		     :"r"(row),"r"(c) 	/* input */
		     :"%eax"		/* clobbered register */
		     );
		row++;
		i++;
	}
}

int mcurses_vline(int col, char c) {
	int i = 0;
	for (i = 0; i < 16; i++) {
		mcurses_addch(col, i, c);
	}
}

int mcurses_border(char c) {
	mcurses_hline(0, c);
	mcurses_hline(15, c);
	mcurses_vline(0, c);
	mcurses_vline(15, c);
}

int mcurses_hlinexl(int x, int y, int length, char c) {
	if (x + length > 15) {	//if length is overflowed
		length = 16 - x;	//just make length go to the end
	}
	int i;
	for (i = 0; i < length; i++) {
		mcurses_addch(x, y, c);
		x++;
	}
}

int mcurses_vlineyl(int x, int y, int length, char c) {
	if (y + length > 15) {	//if length is overflowed
		length = 16 - y;	//just make length go to the end
	}
	int i;
	for (i = 0; i < length; i++) {
		mcurses_addch(x, y, c);
		y++;
	}
}

int mcurses_box(int x1, int y1, int x2, int y2, char c){
	mcurses_hlinexl(x1, y1, x2 - x1 + 1, c);	//top
	mcurses_hlinexl(x1, y2, x2 - x1 + 1, c);	//bottom
	mcurses_vlineyl(x1, y1+1, y2 - y1 - 1, c);	//right
	mcurses_vlineyl(x2, y1+1, y2 - y1 - 1, c);	//left
}

int mcurses_addstr(int x, int y, char *text, int s, int e) {
	int i = 0;
	while (text[i] != '\0') {
		mcurses_addch(x,y,text[i]);
		i++;
		x++;

		if (x == e) {
			y++;
			x = s;
		}
	}
}

char mcurses_getch(int x, int y) {
	/* Get proper memory address from the coord */
	char pixel;
	y *= 16;		//row offset
	y += address;	//adding to base address
	x += y;			//add x coordinate to it
	asm ("movb (%1), %%al;	\
		movb %%al, %0;"
	     :"=r"(pixel)	/*output*/
	     :"r"(x)	/* input */
	     :"%eax"		/* clobbered register */
	     );
	return pixel;
}

void mcurses_clear() {
	int i;
	for (i = 0; i < 16; i++) {
		mcurses_hline(i,' ');
	}
}

void mcurses_refresh() {
	asm ("int $3;");
}
