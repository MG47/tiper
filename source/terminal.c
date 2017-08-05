/*
* terminal.c
*/

#include "tiper.h"

#define CLEAR_SCREEN_ANSI "\e[2J\e[H"

static void print_menu()
{
	attron(A_REVERSE);
	mvprintw(maxrow + 1, maxcol / 4, "Tiper Text Editor (%d.%d)\n", TIPER_VERSION, TIPER_REVISION);
	mvprintw(maxrow + 2, maxcol / 4, "Shortcuts");
	mvprintw(maxrow + 1, maxcol / 2, "Save and Exit: Ctrl+x");
	mvprintw(maxrow + 2, maxcol / 2, "Save: Ctrl+i");
	mvprintw(maxrow + 1,  (maxcol * 3.0) / 4, "Exit: Ctrl+c");
	attroff(A_REVERSE);
}

static void clear_screen()
{
	const char* clear_screen = CLEAR_SCREEN_ANSI;
	write(STDOUT_FILENO, clear_screen, 7);
}


void print_cursor_info()
{
	unsigned int page_offset = (current_page * maxrow);
	unsigned int line_offset = page_offset + row;
	mvprintw(maxrow + 1, 0, "Page %u: %u (%u), %u", current_page, line_offset, row, col);
	mvprintw(maxrow + 2, 0, "MAX LINES: %u", buffer.buffer_lines - 1);
	refresh();
}

void print_contents(unsigned int page_no) 
{
	clear();
	unsigned int i;
	unsigned int page_offset = page_no * maxrow;
	unsigned int line_offset = page_offset % maxrow;

	for (i = line_offset; i < (line_offset + maxrow); i++) {
		//TODO bounds check 
		if (!((i + page_offset) < buffer.buffer_lines))
			break;
		mvprintw(i, 0, "%s", buffer.buf[i + page_offset]);
	}
	refresh();
	print_menu();
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

void clear_and_exit()
{
	erase();
	refresh();
	endwin();
	clear_screen();
	exit(EXIT_SUCCESS);
}
