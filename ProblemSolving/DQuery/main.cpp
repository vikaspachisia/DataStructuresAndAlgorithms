#include <stdio.h>
#include <stdlib.h>

/*
To use arrays in legacy method of programming contests.
*/
#define MAX_N 30001 //Maximum number of values that can be present in test cases.
#define MAX_Q 2000001 //Maximum number of queries that can be present in test cases.
#define MAX_V 1000001 //Maximum value an element can have in the input (array - values array)
#define MAX_ST 100000 //Maximum size of the segment tree that can take care of the above input limits.

struct  Query { int from, to, index; };
Query queries[MAX_Q];
int values[MAX_N], values_last_indices[MAX_V], values_last_indices_neg[MAX_V], query_results[MAX_Q], segment_tree[MAX_ST];
int value_count, query_count;
bool using_test_id;
/*
Comparison function to be used as an argument in the qsort function.
It compares the 'Query' structure on the following fields and in the order mentioned below:
Query.from, Query.to and then Query.index.
primarily used to sort 'queries' on the 'to' field.
*/
int compare_queries(const void* l, const void* r)
{
	int retVal = 0;
	const Query* lhs = (const Query*)l;
	const Query* rhs = (const Query*)r;
	if (!(lhs->to == rhs->to && lhs->from == rhs->from && lhs->index == rhs->index))
	{
		if (lhs->to != rhs->to ? (lhs->to < rhs->to)
			: (lhs->from != rhs->from ? (lhs->from < rhs->from) : lhs->index < rhs->index))
		{
			retVal = -1;
		}
		else
		{
			retVal = 1;
		}
	}

	return retVal;
}

void sortQueries()
{
	qsort(queries, query_count, sizeof(Query), compare_queries);
}

/*
Implement segment tree to keep track of the distinct values in the sorted order range.
*/
int query(int nodeid, int ss, int se, int qs, int qe) {
	if (ss > qe || se < qs) return 0;
	if (ss >= qs && se <= qe) return segment_tree[nodeid];
	auto mid = (ss + se) / 2;
	return query(2 * nodeid, ss, mid, qs, qe) + query(2 * nodeid + 1, mid + 1, se, qs, qe);
}

void update(int nodeid, int ss, int se, int pos, int val) {
	if (ss > pos || se < pos) return;

	segment_tree[nodeid] += val;

	if (pos == ss && pos == se) return;

	auto mid = (ss + se) / 2;
	if (pos >= ss && pos <= mid) { update(2 * nodeid, ss, mid, pos, val); }
	else if (pos > mid && pos <= se) { update(2 * nodeid + 1, mid + 1, se, pos, val); }
}


/*
Implement routines to read all sorts of inputs.
Although the input is defined to have some structure, the spojtoolkit had input data of all types:
1. Garbage input: characters appearing in place of numbers
2. Incomplete input: queries having only 'from' field without having 'to' fields
3. Extra input (more than needed): Query count is 2 but 10 queries are defined for the input.

Additionally the SPOJ and spojtoolkit takes only one test case at a time for testing.
While I wanted to execute around 50 test cases in one run of the program and output the 50 results into a file
that I can compare against another file presumed to have correct output values.
*/
inline int countDigits(int number)
{
	int numberOfDigits = 0;
	if (number == 0) { numberOfDigits++; }
	else { while (number) { numberOfDigits++; number /= 10; } }
	return numberOfDigits;
}

int getNextTestCase(char* buffer, size_t buffer_length, char* test_id, size_t test_id_length)
{
	int no_of_elements = 0;
	char* line = 0;

	if (using_test_id)
	{
		while ((line = fgets(buffer, buffer_length, stdin)) && buffer[0] != '#');
		if (line) {
			for (int i = 0; i < test_id_length; i++) { test_id[i] = 0; }
			for (int i = 0; buffer[i] && i < test_id_length; i++) { test_id[i] = buffer[i]; }
		}

		while ((line = fgets(buffer, buffer_length, stdin)) && buffer[0] == '#') {
			for (int i = 0; i < test_id_length; i++) { test_id[i] = 0; }
			for (int i = 0; buffer[i] && i < test_id_length; i++) { test_id[i] = buffer[i]; }
		}
	}
	else
	{
		line = fgets(buffer, buffer_length, stdin);
	}

	if (line) { sscanf_s(buffer, "%d", &no_of_elements); }

	return no_of_elements;
}

int gettestid(char* testid) {
	int tid = 0;
	if (testid[2] == '\n') {
		tid = testid[1] - '0';
	}
	else {
		tid = (testid[1] - '0') * 10 + testid[2] - '0';
	}
	return tid;
}

void solve_main_problem()
{
	char buffer[250001], testid[50] = { 0 }, *line = NULL;
	using_test_id = false;
	while ((value_count = getNextTestCase(buffer, sizeof(buffer), testid, sizeof(testid)))) {

		//Initialize the variables for correct processing of data.	
		for (int i = 0; i < MAX_V; i++) { values_last_indices_neg[i] = values_last_indices[i] = -1; }
		for (int i = 0; i < MAX_ST; i++) { segment_tree[i] = 0; }

		//Read the values from input.
		if (fgets(buffer, sizeof(buffer), stdin)) {
			int counter = 0;
			for (int i = 0; i < value_count; i++) {
				sscanf_s(buffer + counter, "%d", &values[i]);
				counter += countDigits(values[i]) + 1;
			}
		}
		else {
			value_count = 0;
		}

		//read the queries from input
		if (fgets(buffer, sizeof(buffer), stdin)) { sscanf_s(buffer, "%d", &query_count); }
		for (int i = 0; i < query_count; i++) {
			if (fgets(buffer, sizeof(buffer), stdin)) {
				auto argcount = sscanf_s(buffer, "%d %d", &queries[i].from, &queries[i].to);
				if (argcount != 2)queries[i].to = 0;
				queries[i].from--; queries[i].to--; queries[i].index = i;
			}
		}

		sortQueries();

		//process all queries
		int v = 0, q = 0;
		while (q < query_count) {
			//process all elements upto position 'curr_q_pos' before answering all queries ending at position 'curr_q_pos'.
			int curr_q_pos = queries[q].to, prev_q_pos = queries[q].to;
			if (curr_q_pos >= 0) {
				while (v <= curr_q_pos && v < value_count) {
					auto curr_val_idx = values[v] >= 0 ? values_last_indices[values[v]] : values_last_indices_neg[-values[v]];
					if (curr_val_idx >= 0) {
						update(1, 0, value_count - 1, curr_val_idx, -1);
					}

					update(1, 0, value_count - 1, v, 1);

					if (values[v] >= 0) values_last_indices[values[v]] = v;
					else values_last_indices_neg[-values[v]] = v;
					v++;
				}

				//answer all queries ending at position 'curr_q_pos'.
				while (curr_q_pos == prev_q_pos) {
					query_results[queries[q].index] = query(1, 0, value_count - 1, queries[q].from, queries[q].to);
					prev_q_pos = curr_q_pos;
					curr_q_pos = queries[++q].to;
				}
			}
			else
			{
				query_results[queries[q].index] = -1;
				q++;
			}
		}

		printf("%s", testid);
		for (int i = 0; i < query_count; i++) { printf("%d\n", query_results[i]); }
	}
}


FILE *inStream, *outStream;
void open_unit_test_files() {
	freopen_s(&inStream, "unit_test_input.txt", "r", stdin);
	freopen_s(&outStream, "unit_test_output.txt", "w", stdout);
	//std::ios_base::sync_with_stdio(false);
}

void close_unit_test_files() {
	fclose(stdin);
	fclose(stdout);

	fclose(inStream);
	fclose(outStream);
}

int main() {
	open_unit_test_files();

	solve_main_problem();

	close_unit_test_files();
	return 0;
}