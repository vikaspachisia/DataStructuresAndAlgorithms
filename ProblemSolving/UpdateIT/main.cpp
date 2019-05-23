//scanf and printf is faster than cin and cout.
#include <iostream>
using namespace std;

struct operation_data { int L, R, V; };
operation_data update_queries[100001];
int queries[10001], bit[10001], N, U, Q;

void update_bit() {
	auto l = 0, r = 0, v = 0;
	for (int i = 0; i < U;i++) {
		l = update_queries[i].L+1, r = update_queries[i].R+2, v= update_queries[i].V;
		while (l <= N) { bit[l] += v; l += (l & -l); }
		while (r <= N) { bit[r] -= v; r += (r & -r); }
	}
}

void query_bit() {
	for (int i = 0; i < Q;i++) {
		int index = queries[i]+1;

		queries[i] = 0;
		while (index != 0) { queries[i] += bit[index]; index -= (index & -index); }
	}
}

void solve_main_problem()
{
	char testid[10];
	int T, ST;

	cin >> T;
	for (int t = 0; t < T; t++)
	{
		cin >> testid;		
		cin >> ST;
		for (int st = 0; st < ST; st++) {
			cin >> N >> U;	
			for (int i = 0; i <= N; i++)bit[i] = 0;
			for (int i = 0; i < U; i++) { cin >> update_queries[i].L >> update_queries[i].R >> update_queries[i].V; }
			cin >> Q;
			for (int i = 0; i < Q; i++) { cin >> queries[i]; }

			update_bit();
			query_bit();

			cout << testid << endl;
			for (int i = 0; i < Q; i++) { cout << queries[i] << endl; }
		}
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