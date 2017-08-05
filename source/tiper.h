/*
* Tiper.h
*/
#ifndef TIPER_H
#define TIPER_H

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <ncurses.h>
#include <fcntl.h>

#define TIPER_VERSION 0
#define TIPER_REVISION 1

/* TODO Remove limits */
#define BUFFER_LINES 300
#define BUFFER_COLUMNS 80

struct file_buffer {
	char **buf;
	unsigned int buffer_lines;
};


/* Terminal variables */
extern unsigned int maxrow, maxcol;
extern unsigned int row, col;
extern unsigned int current_page;

/* File variables */
extern struct file_buffer buffer;
extern FILE *stream;



/* Signal handling functions - signal.c */
void init_signals();

/* Terminal functions - terminal.c */
void clear_screen();
void init_console();
void print_menu();
void clear_and_exit();

/* File I/O functions - file_ops.c*/
FILE *create_new_file();
FILE *parse_file(char *filename);
void save_to_file();

/* String handling functions - string_ops.c*/
void insert_newline(unsigned int line_offset);
void remove_char(char *str, char remove);
void remove_char_at(char *src, int index);
void remove_newline(unsigned int line_offset);


#endif /*TIPER_H*/


