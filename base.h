#ifndef BASE_H
#define BASE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

#define eprintf(f, ...) fprintf(stderr, f, __VA_ARGS__)

/// @param filename const char* (&)
/// @return char*
char *
read_file__Base(const char *filename);

char *
read_file__Base(const char *filename)
{
	FILE *file = fopen(filename, "r");

	if (!file) {
		eprintf("Cannot read the given file: %s\n", filename);
		exit(1);
	}

	struct stat st;

	stat(filename, &st);

	size_t n = st.st_size + 1;
	char *buffer = malloc(n);

	memset(buffer, 0, n);
	fread(buffer, sizeof(char), n, file);

	fclose(file);

	return buffer;
}

#endif // BASE_H
