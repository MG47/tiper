/*
* string_ops.c
*/

#include "tiper.h"

void insert_newline(unsigned int line_offset)
{
	//TODO add fix for scrolling
	unsigned int lines_to_end = (buffer.buffer_lines - 1) - line_offset;
	unsigned int chars_to_end = (strlen(buffer.buf[line_offset]) + 1) - col ;

	// TODO fix this
	// TODO check allocation errors (out-of-memory)
	if (!buffer.buf)
		buffer.buf[buffer.buffer_lines] = malloc(sizeof(char) * BUFFER_COLUMNS);

	unsigned int i;
	for (i = 0; i < lines_to_end; i++) {
		strcpy(buffer.buf[buffer.buffer_lines - i], buffer.buf[buffer.buffer_lines - i - 1]);
	}

	buffer.buffer_lines++;

	strncpy(&buffer.buf[line_offset + 1][0], &buffer.buf[line_offset][col], chars_to_end);
	buffer.buf[line_offset][col] = '\n';
	buffer.buf[line_offset][col + 1] = '\0';
}

void remove_char(char *str, char remove) 
{
	char *src, *dst;
	for (src = dst = str; *src != '\0'; src++) {
		*dst = *src;
		if (*dst != remove) 
			dst++;
	}
	*dst = '\0';
}

void remove_char_at(char *src, int index)
{
	int i, len;
	len = strlen(src);
	for (i = index; i <= len; i++) {
		src[i] = src[i + 1];
	}
}

void remove_newline(unsigned int line_offset)
{
	unsigned int i;
	unsigned int lines_to_end = (buffer.buffer_lines - 1) - line_offset;

	remove_char(buffer.buf[line_offset - 1], '\n');
	strcat(buffer.buf[line_offset - 1], buffer.buf[line_offset]);

	// TODO confirm this
	for (i = 0; i < lines_to_end; i++) {
		strcpy(buffer.buf[line_offset + i], buffer.buf[line_offset + i + 1]);
	}

	free(buffer.buf[buffer.buffer_lines - 1]);
	buffer.buffer_lines--;
}

