#include "../base.h"

#include <assert.h>
#include <stdint.h>

#define MAX_LINE 1000

/// @param start char* (&)
/// @param ns int* (&)
/// @param ms int* (&)
static void
split_on_new_line_and_sort(char *start, int *ns, int *ms, void (*sort)(int n, int *ns, size_t len));

static 
void sort(int n, int *ns, size_t len);

/// @param file_content char* (&)
static void part_1(char *file_content);

void
split_on_new_line_and_sort(char *start, int *ns, int *ms, void (*sort)(int n, int *ns, size_t len)) {
	assert(start && "start need cannot be NULL");

	char *current = start;
	size_t start_line_pos = 0;
	size_t line_count = 0;
	char n_s[6];
	char m_s[6];

	memset(n_s, 0, sizeof(n_s));
	memset(m_s, 0, sizeof(m_s));

	while (*current) {
		if (*current == '\n') {
			memcpy(n_s, start + start_line_pos, sizeof(n_s) - 1);
			memcpy(m_s, start + start_line_pos + sizeof(n_s), sizeof(m_s) - 1);

			int n = atoi(n_s);
			int m = atoi(m_s);

			sort(n, ns, line_count);
			sort(m, ms, line_count);

			start_line_pos = (current - start) + 1;

			++line_count;
		}

		++current;
	}
}

void sort(int n, int *ns, size_t len)
{
	assert(len < MAX_LINE && "the length need to be less than MAX_LINE");

	int *peeked = NULL;

	for (size_t i = 0; i < len; ++i) {
		if (ns[i] <= n) {
			continue;
		}

		peeked = ns + i;

		break;
	}

	if (peeked) {
		int move = *peeked;
		*peeked = n;

		for (size_t i = (peeked - ns) + 1; i < len; ++i) {
			int tmp_move = move;

			move = ns[i];
			ns[i] = tmp_move;
		}

		ns[len] = move;
	} else if (len != 0) {
		ns[len] = n;
	} else {
		*ns = n;
	}
}

void part_1(char *file_content) {
	int ns[MAX_LINE] = {0};
	int ms[MAX_LINE] = {0};
	
	split_on_new_line_and_sort(file_content, ns, ms, &sort);

	int total_distance = 0;

	for (size_t i = 0; i < MAX_LINE; ++i) {
		total_distance += abs(ns[i] - ms[i]);
	}

	printf("Part 1 = %d\n", total_distance);
}

int main() {
	char *file_content = read_file__Base("./input.txt");

	part_1(file_content);

	free(file_content);
}
