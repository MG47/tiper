/*
*
*/


#include "tiper.h"


void print_menu()
{
	attron(A_REVERSE);
	mvprintw(maxrow + 1, maxcol / 4, "Tiper Text Editor (%d.%d)\n", TIPER_VERSION, TIPER_REVISION);
	mvprintw(maxrow + 2, maxcol / 4, "Shortcuts");
	mvprintw(maxrow + 1, maxcol / 2, "Save and Exit: Ctrl+x");
	mvprintw(maxrow + 2, maxcol / 2, "Save: Ctrl+i");
	mvprintw(maxrow + 1,  (maxcol * 3.0) / 4, "Exit: Ctrl+c");
	attroff(A_REVERSE);
}

void clear_screen()
{
	const char* CLEAR_SCREEN_ANSI =  "\e[2J\e[H";
	write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 7);
}

void init_console()
{
	int max_length;
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	getmaxyx(stdscr, max_length, maxcol);
	maxrow = max_length - 3;
	print_menu();
	refresh();
}

