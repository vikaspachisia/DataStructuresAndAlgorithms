#include <iostream>

using namespace std;

class PlusCastle {
public:

	int maximiseClosedFigures(int k)
	{
		if (k < 4) { return 0; }
		int res = 0;
		int x = sqrt(k);
		res = (x - 1)*(x - 1);
		int remain = k - x * x;
		if (remain == 0) { return res; }
		if (remain <= x) {
			res += remain - 1;
			return res;
		}
		else {
			remain -= x;
			res += (x - 1) + (remain - 1);
			return res;
		}
	}

	/*int maximiseClosedFigures(int k)
	{
		int retVal = 0;
		int r = 1, c=1;
		for (long long i = 1; i*i <= k; i++) {
			if (k/i > 1) r = i;
		}
		c = k / r;
		
		int maxIdx = c < r ? c : r;

		for (int i = 1; i<maxIdx; i++) {
			retVal += ((r - i)*(c - i));
		}
		if (r == c)retVal--;

		return retVal;
	}*/
};

int main() {
	
	PlusCastle pc;

	int result = pc.maximiseClosedFigures(9);
	result = pc.maximiseClosedFigures(44);
	result = pc.maximiseClosedFigures(898680485);

	return 0;
}


//write this in geeks for geeks.
#include "program_bit.h"
#include "program_binary_distance.h"

#include <string>
using namespace std;


#include <vector>

using namespace std;

class CollectAllCoins {
public:
	vector <int> collect(int R, int C)
	{
		vector<int> retVal{};
		vector<vector<int>> grid(R, vector<int>(C));
		for (int r = 0; r < R; r++) {
			for (int c = 0; c < C; c++) { grid[r][c] = 'T'; }
		}
		grid[0][0] = 'H';

		flipCoins(grid, 0, 0, retVal);

		for (int i = 0; i < R && retVal.size(); i++) {
			for (int j = 0; j < C && retVal.size(); j++) {
				if (grid[i][j] != '.')retVal.clear();
			}
		}

		return retVal;
	}

private:
	void flipCoins(vector<vector<int>> grid, int R, int C, vector<int>& result) {
		result.push_back(R*C + C);
		grid[R][C] = '.';

		if (R - 1 >= 0 && R - 1 < grid.size()) {
			if (grid[R - 1][C] == 'T')grid[R - 1][C] = 'H';
			else if (grid[R - 1][C] == 'H')grid[R - 1][C] = 'T';
		}

		if (R + 1 >= 0 && R + 1 < grid.size()) {
			if (grid[R + 1][C] == 'T')grid[R + 1][C] = 'H';
			else if (grid[R + 1][C] == 'H')grid[R + 1][C] = 'T';
		}

		if (C - 1 >= 0 && C - 1 < grid[0].size()) {
			if (grid[R][C - 1] == 'T')grid[R][C - 1] = 'H';
			else if (grid[R][C - 1] == 'H')grid[R][C - 1] = 'T';
		}

		if (C + 1 >= 0 && C + 1 < grid[0].size()) {
			if (grid[R][C + 1] == 'T')grid[R][C + 1] = 'H';
			else if (grid[R][C + 1] == 'H')grid[R][C + 1] = 'T';
		}

		for (int r = -1; r <= 1; r++) {
			if (R + r >= 0 && R + r < grid.size()) {
				for (int c = -1; c <= 1; c++) {
					if (C + c >= 0 && C + c < grid[0].size()) {
						if (grid[R + r][C + c] == 'H')flipCoins(grid, R + r, C + c, result);
					}
				}
			}
		}
	}
};

int main() {
	int K, N, AN, MAXAN=0;
	int A[1001];
	cin >> K;
	for (int k = 0; k < K; k++) {
		MAXAN = 0;
		cin >> N;
		for (int n = 0; n < N; n++)A[n] = 0;
		for (int n = 0; n < N; n++) { cin >> AN; A[AN]++; }
		for (int n = 0; n < N; n++) { if (N - A[AN] > MAXAN) MAXAN = N - A[AN]; }
		cout << MAXAN << endl;
	}
	return 0;
}
int main() {
	int retVal = 0;
	BallsOnAMeadow vm;
	
	vm.count(".(|||.()(||||||)");

	return 0;
}