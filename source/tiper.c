/*
* tiper.c - main
*/

#include "tiper.h"

#define DEBUG_ON


//TODO Make a struct for these
unsigned int maxrow, maxcol;
unsigned int row, col;
unsigned int current_page;


#ifndef CTRL
#define CTRL(x) ((x) & 0x1f)
#endif


static void usage()
{
	printf("tiper:\n");
	printf("Usage: "
		"tiper [OPTIONS] [FILE]\n"
		"OPTIONS:\n"
		"-h - Usage\n"
		"-v - Version\n"); 
}

static void print_version()
{
	printf("Tiper version:%d.%d\n", TIPER_VERSION, TIPER_REVISION);
}

static void process_input(int read)
{
	unsigned int page_offset = (current_page * maxrow);
	unsigned int line_offset = page_offset + row;

	switch (read) {
	case KEY_LEFT:
	//fix column bug
		if (col > 0) {
			col--;
		} else {
			if (row) {
				row--;
				line_offset = page_offset + row;
				col = strlen(buffer.buf[line_offset]) - 1;
			} else {
				if (current_page) {
					row = maxrow - 1;
					line_offset = page_offset + row;
					col = strlen(buffer.buf[line_offset]) - 1;
					current_page--;
				}
			}
			print_contents(current_page);
		}
		move(row, col);
		break;
	case KEY_RIGHT:
	//fix column bug
		if (col < maxcol && col < (strlen(buffer.buf[line_offset]) - 1)) {
			col++;
		} else {
			if (line_offset < (buffer.buffer_lines - 2)) {
				if (row < maxrow - 1) {
					row++;
				} else {
					row = 0;
					current_page++;
					print_contents(current_page);
				} 
				col = 0;
			}
		}
		move(row, col);
		break;
	case KEY_UP:
		if (row) {
			row--;
			line_offset = page_offset + row;
			if (col > (strlen(buffer.buf[line_offset]) - 1))
				col = (strlen(buffer.buf[line_offset]) - 1);
		} else {
			if (current_page) {
				row = maxrow - 1;
				line_offset = page_offset + row;
				if (col > (strlen(buffer.buf[line_offset]) - 1))
					col = (strlen(buffer.buf[line_offset]) - 1);
				current_page--;
				print_contents(current_page);
			}
		}
		move(row, col);
		break;
	case KEY_DOWN:
		if (line_offset < (buffer.buffer_lines - 2)) {
			if (row < maxrow - 1) {
				row++;
			} else {
				row = 0;
				current_page++;
				print_contents(current_page);
			} 
		}
/*Android shell has a different behaviour for key_down.*/
#ifdef ANDROID_SHELL
		col = 0;
#else
		if (col > (strlen(buffer.buf[row]) - 1))
			col = (strlen(buffer.buf[row]) - 1);
#endif
		move(row, col);
		break;
	case KEY_BACKSPACE:
		//TODO fix last line bug
		if (col > 0) {
			remove_char_at(buffer.buf[line_offset], (col - 1));
			mvdelch(row, col - 1);
			col--;
		} else {
			/* TODO fix max column limit */
			if ((strlen(buffer.buf[line_offset]) + (strlen(buffer.buf[line_offset - 1])))  >= maxcol)
				break;
			if (line_offset) {
				col = (strlen(buffer.buf[line_offset - 1])) - 1;
				remove_newline(line_offset);
				if (row > 0) {
					row--;
				} else {
					current_page--;
					row = maxrow - 1;
				}
				print_contents(current_page);
			}
		}
		move(row, col);
		break;
	case KEY_DC:
		//TODO fix last line bug
		if (col < (strlen(buffer.buf[line_offset]) - 1)) {
			remove_char_at(buffer.buf[line_offset], col);
			delch();
		} else {
			if (line_offset < buffer.buffer_lines - 2) {
				/* TODO fix max column limit */
				if ((strlen(buffer.buf[line_offset]) + (strlen(buffer.buf[line_offset + 1])))  >= maxcol)
					break;		
				remove_newline(line_offset + 1);
			}
		}
		print_contents(current_page);
		break;
	case KEY_ENTER:
	case 10:
		insert_newline(line_offset);
		if (row == (maxrow - 1)) {
			current_page++;
			row = 0;
		} else {
			row++;
		}
		print_contents(current_page);
		col = 0;
		move(row, col);
		break;
	case KEY_HOME:
	case KEY_END:
		break;
	case CTRL('f'):
		break;		
	case CTRL('i'):
		save_to_file();
		break;			
	case CTRL('x'):
		save_to_file();
		clear_and_exit();
		break;			
	case KEY_F(1):
		break;
	case KEY_F(2):
		break;
	default:
		if (col < maxcol) {
			unsigned int page_offset = current_page * maxrow; 
			insert_char_at(buffer.buf[page_offset + row], col, read);
			mvprintw(row, 0, "%s", buffer.buf[page_offset + row]);
			col++;
			move(row, col);
		}
	}
}

int main(int argc, char **argv)
{
	int opt;
	char *file_string;	
	int read;

	printf("\nTiper Text Editor :\n");
	if (argc > 2) {
		usage();
		return 0;
	}

	while ((opt = getopt(argc, argv, "hv")) != -1) {
		switch (opt) {
		case 'h':
			usage();
			return 0;
		case 'v':
			print_version();
			return 0;
		}
	}

	if (argc < 2) {
		stream = create_new_file();
	} else {
		file_string = argv[1];
		stream = parse_file(file_string);
	}

	if (!stream)
		return 0;

	/* Initialize Signals */

	init_signals();

	current_page = 0;
	init_console();
	move(row, col);
	print_contents(current_page);
	move(0, 0);

	while (1) {	
#ifdef DEBUG_ON	
		print_cursor_info();
#endif
		move(row, col);
		read = getch();
		process_input(read);
		refresh();

	}
	return 0;
}


