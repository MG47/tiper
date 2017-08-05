/*
* terminal.c
*/

#include "tiper.h"

#define CLEAR_SCREEN_ANSI "\e[2J\e[H"

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

void clear_screen()
{
	const char* clear_screen = CLEAR_SCREEN_ANSI;
	write(STDOUT_FILENO, clear_screen, 7);
}

void clear_and_exit()
{
	erase();
	refresh();
	endwin();
	clear_screen();
	exit(EXIT_SUCCESS);
}
