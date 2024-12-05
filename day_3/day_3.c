#include "../base.h"

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_NUM_LEN 4
#define min(x, y, z) x != 0 && (x < y || y == 0) && (x < z || z == 0) ? x : y != 0 && (y < x || x == 0) && (y < z || z == 0) ? y : z != 0 && (z < x || x == 0) && (z < y || z == 0) ? z : 0

/// @param file_content char* (&)
static void
part_1(char *file_content);

/// @param file_content char* (&)
static void
part_2(char *file_content);

void
part_1(char *file_content)
{
	char *current = file_content;
	size_t result = 0;
	char n_s[MAX_NUM_LEN];
	char m_s[MAX_NUM_LEN];

	memset(n_s, 0, sizeof(n_s));
	memset(m_s, 0, sizeof(m_s));

	while ((current = strstr(current, "mul("))) {
		current += 4;

		char *n_end_num = current;

		for (int i = 0; i < MAX_NUM_LEN && *n_end_num && *n_end_num != ',' && isdigit(*n_end_num); ++i) {
			++n_end_num;
		}

		if (n_end_num) {
			if (*n_end_num != ',') {
				continue;
			}

			size_t n_len = n_end_num - current;

			assert(n_len <= 3 && "the number is too big");

			memcpy(n_s, current, n_len);
			n_s[n_len] = 0;

			current = n_end_num + 1;
		} else {
			continue;
		}

		char *m_end_num = current;

		for (int i = 0; i < MAX_NUM_LEN && *m_end_num && *m_end_num != ')' && isdigit(*m_end_num); ++i) {
			++m_end_num;
		}

		if (m_end_num) {
			if (*m_end_num != ')') {
				continue;
			}

			size_t m_len = m_end_num - current;

			assert(m_len <= 3 && "the number is too big");

			memcpy(m_s, current, m_len);
			m_s[m_len] = 0;

			current = m_end_num + 1;
		}

		int n = atoi(n_s);
		int m = atoi(m_s);

		result += n * m;
	}

	printf("Part 1 = %zu\n", result);
}

void
part_2(char *file_content)
{
	char *current = file_content;
	size_t result = 0;
	char n_s[MAX_NUM_LEN];
	char m_s[MAX_NUM_LEN];
	bool must_do = true;

	memset(n_s, 0, sizeof(n_s));
	memset(m_s, 0, sizeof(m_s));

	while (*current) {
		char *next_mul = strstr(current, "mul(");
		char *next_do = strstr(current, "do()");
		char *next_dont = strstr(current, "don\'t()");
		char *next = min(next_mul, next_do, next_dont);

		if (next_mul == next && next) {
			current = next_mul;
			current += 4;

			char *n_end_num = current;

			for (int i = 0; i < MAX_NUM_LEN && *n_end_num && *n_end_num != ',' && isdigit(*n_end_num); ++i) {
				++n_end_num;
			}

			if (n_end_num) {
				if (*n_end_num != ',') {
					continue;
				}

				size_t n_len = n_end_num - current;

				assert(n_len <= 3 && "the number is too big");

				memcpy(n_s, current, n_len);
				n_s[n_len] = 0;

				current = n_end_num + 1;
			} else {
				continue;
			}

			char *m_end_num = current;

			for (int i = 0; i < MAX_NUM_LEN && *m_end_num && *m_end_num != ')' && isdigit(*m_end_num); ++i) {
				++m_end_num;
			}

			if (m_end_num) {
				if (*m_end_num != ')') {
					continue;
				}

				size_t m_len = m_end_num - current;

				assert(m_len <= 3 && "the number is too big");

				memcpy(m_s, current, m_len);
				m_s[m_len] = 0;

				current = m_end_num + 1;
			}

			int n = atoi(n_s);
			int m = atoi(m_s);

			if (must_do) {
				result += n * m;
			}
		} else if (next == next_do && next) {
			current = next_do;
			current += 4;
			must_do = true;
		} else if (next == next_dont && next) {
			current = next_dont;
			current += 7;
			must_do = false;
		} else {
			break;
		}
	}

	printf("Part 1 = %zu\n", result);
}

int main() {
	char *file_content = read_file__Base("./input.txt");

	part_1(file_content);
	part_2(file_content);

	free(file_content);
}
