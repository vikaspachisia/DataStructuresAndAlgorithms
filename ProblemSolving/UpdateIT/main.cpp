//scanf and printf is faster than cin and cout.
#include <stdio.h>
using namespace std;
#define MAX_N 10002
void solve_main_problem()
{
	char testid[10];
	int T, ST, VAL, N, U, Q, L, R, D[MAX_N]{};

	scanf("%d",&T);
	for (int t = 0; t < T; t++)
	{
		scanf("%s",&testid);
		scanf("%d",&ST);
		for (int st = 0; st < ST; st++) {
			scanf("%d %d", &N, &U);
			for (int i = 0; i <= N; i++)D[i] = 0;
			for (int i = 1; i <= U; i++) { 
				scanf("%d %d %d", &L, &R, &VAL);
				D[L+1] += VAL, D[R + 2] -= VAL; 
			}
			
			for (int i = 1; i <= N; i++) { D[i] += D[i - 1]; }

			printf("%d\n", testid);
			scanf("%d",&Q);			
			for (int i = 1; i <= Q; i++) { scanf("%d", &VAL); printf("%d", D[VAL+1]); }		
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