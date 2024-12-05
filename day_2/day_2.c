#include "../base.h"

#include <assert.h>
#include <stdbool.h>

#define MAX_LINE 1000
#define MAX_NUM_BY_LINE 8

typedef struct Line {
	int nums[MAX_NUM_BY_LINE];
	int num_count;
} Line;

/// @param start char* (&)
/// @param lines Lines* (&) 
static
void split_on_new_line(char *start, Line *lines);

/// @param ns int* (&)
/// @param safes int* (&)
static void
validate_line_part_1(int *ns, int num_count, int *safes);

/// @param ns int* (&)
/// @param safes int* (&)
static void
validate_line_part_2(int *ns, int num_count, bool *is_safe, int ignore_report);

/// @param file_content char* (&)
static void
part_1(char *file_content);

/// @param file_content char* (&)
static void
part_2(char *file_content);

void split_on_new_line(char *start, Line *lines)
{
	assert(start && "start need cannot be NULL");

	char *current = start;
	size_t line_count = 0;
	char line[MAX_NUM_BY_LINE][3] = {0};

	for (int i = 0; i < MAX_NUM_BY_LINE; ++i) {
		memset(line[i], 0, sizeof(*line));
	}

	while (*current) {
		size_t num_count = 0;

		while (*current && *current != '\n') {
			char *start_num = current;

			while (*current && *current != ' ' && *current != '\n') {
				++current;
			}

			int n = current - start_num;

			memcpy(line[num_count], start_num, n);
			line[num_count++][n] = 0;

			if (*current != '\n') {
				++current;
			}
		}

		for (int i = 0; i < num_count; ++i) {
			lines[line_count].nums[i] = atoi(line[i]);
		}

		lines[line_count].num_count = num_count;

		++line_count;
		++current;
	}
}

void
validate_line_part_1(int *ns, int num_count, int *safes)
{
	int first_num = *ns;
	int next_num = ns[1];

	if (first_num == next_num || abs(next_num - first_num) > 3) {
		return;
	}

	bool is_increasing = next_num > first_num;

	for (int i = 1; i < num_count; ++i) {
		if ((is_increasing && ns[i] < ns[i - 1]) ||
			(!is_increasing && ns[i] > ns[i - 1]) ||
			abs(ns[i - 1] - ns[i]) > 3 ||
			ns[i - 1] == ns[i]) {
			return;
		}
	}

	++(*safes);
}

void
validate_line_part_2(int *ns, int num_count, bool *is_safe, int ignore_report)
{
	int first_num = *ns;
	int next_num = ns[1];

	if (first_num == next_num || abs(next_num - first_num) > 3) {
		return;
	}

	bool is_increasing = next_num > first_num;

	for (int i = 1; i < num_count; ++i) {
		if ((is_increasing && ns[i] < ns[i - 1]) ||
			(!is_increasing && ns[i] > ns[i - 1]) ||
			abs(ns[i - 1] - ns[i]) > 3 ||
			ns[i - 1] == ns[i]) {
			return;
		}
	}

	*is_safe = true;
}

void
part_1(char *file_content)
{
	Line lines[MAX_LINE] = {0};
	int safes = 0;

	split_on_new_line(file_content, lines);

	for (int i = 0; i < MAX_LINE; ++i) {
		validate_line_part_1(lines[i].nums, lines[i].num_count, &safes);
	}

	printf("Part 1 = %d\n", safes);
}

void
part_2(char *file_content)
{
	Line lines[MAX_LINE] = {0};
	int safes = 0;

	split_on_new_line(file_content, lines);

	for (int i = 0; i < MAX_LINE; ++i) {
		bool is_safe = false;	
		int tmp_nums[MAX_NUM_BY_LINE] = {0};

		validate_line_part_1(lines[i].nums, lines[i].num_count, (int*)&is_safe);

		for (int j = 0; j < lines[i].num_count && !is_safe; ++j) {
			for (int k = 0; k < lines[i].num_count; ++k) {
				if (k < j) {
					tmp_nums[k] = lines[i].nums[k];
				} else if (k > j) {
					tmp_nums[k - 1] = lines[i].nums[k];
				}
			}

			validate_line_part_2(tmp_nums, lines[i].num_count - 1, &is_safe, j);
		}

		if (is_safe) {
			++safes;
		}
	}

	printf("Part 2 = %d\n", safes);
}

int main() {
	char *file_content = read_file__Base("./input.txt");

	part_1(file_content);
	part_2(file_content);

	free(file_content);
}
