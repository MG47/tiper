/*
* file_ops.c
*/

#include "tiper.h"

static int new_file_flag;

FILE *stream;
struct file_buffer buffer;

FILE *create_new_file()
{
	int fd;
	char *new_filename = "untitled";

	fd = open(new_filename, O_RDWR | O_CREAT | O_TRUNC | O_EXCL, 0644);
	if (fd == -1) {
		if (errno == EEXIST)
			printf("file named 'untitled' already exists\n");
		return NULL;
	}

	stream = fdopen(fd, "r+");
	if (!stream) {
		printf("error: %s\n", strerror(errno));
		return NULL;
	}

	buffer.buf = (char **)malloc(sizeof(char *));
	buffer.buf[0] = malloc(sizeof(char) * BUFFER_COLUMNS);
	buffer.buffer_lines = 1;
	new_file_flag = 1;
	return stream;
}

FILE *parse_file(char *filename)
{
	unsigned int i;
	int new_file = 0;
	int fd;

	stream = fopen(filename, "r+");
	if (!stream) { 
		fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
		stream = fdopen(fd, "r+");
		if (!stream) {
			printf("error: %s\n", strerror(errno));
			return NULL;
		}
		new_file = 1;
	}

	/* TODO need to fix allocation for scrolling*/
	i = 0;
	buffer.buf = (char **)malloc(BUFFER_LINES * sizeof(char *));
	for (i = 0; i < BUFFER_LINES; i++) {
		buffer.buf[i] = malloc(sizeof(char) * BUFFER_COLUMNS);
	}

	if (new_file) {
		buffer.buffer_lines = 1;
		return stream;
	}

	i = 0;
	/* TODO : add critical maxrow & maxcolumn check */
	/* TODO : add rows dyanmically with fgets */
	while ((i < BUFFER_LINES) && (fgets(buffer.buf[i], BUFFER_COLUMNS, stream) != NULL))
		i++;
	/* TODO : fix limit*/
	if (i >= BUFFER_LINES - 1)
		exit(EXIT_FAILURE);


	buffer.buffer_lines = i + 1;
	return stream;
}

void save_to_file()
{
	//TODO add newline at end
	//TODO mvprintw saved to file//
	unsigned int i;
	fseek(stream, 0, SEEK_SET);
	for (i = 0; i < buffer.buffer_lines; i++) {
		fputs(buffer.buf[i], stream);
	}
	fflush(stream);

	//TODO ask new file name
//	if (new_file_flag)

}
