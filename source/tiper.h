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

/* Terminal Variables */
extern unsigned int maxrow, maxcol;
extern unsigned int row, col;
extern unsigned int current_page;


/* Signal handling functions - signal.c */
void init_signals();

/* Terminal functions - terminal.c */
void clear_screen();
void init_console();
void print_menu();

/* File I/O functions - file_ops.c*/
/* String handling functions - string_ops.c*/


#endif /*TIPER_H*/


