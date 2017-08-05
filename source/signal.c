/*
* signal.c
*/

#include "tiper.h"

static void signal_handler(int signo)
{
	/* TODO switch Case */
	if (signo == SIGINT) {
		erase();
		refresh();
		endwin();
		clear_screen();
		exit(EXIT_FAILURE);
	}

	if (signo = SIGWINCH) {
		//TODO Handle resize gracefully
	}
}

#if 0
static void resize_handler(int sig)
{
	// handle SIGWINCH
}
#endif

void init_signals()
{
	if (signal(SIGINT, signal_handler) == SIG_ERR) {
		printf("Error: Cannot handle signal SIGNINT");
		exit(EXIT_FAILURE);
	}

	if (signal(SIGWINCH, signal_handler) == SIG_ERR) {
		printf("Error: Cannot handle signal SIGNINT");
		exit(EXIT_FAILURE);
	}
}


