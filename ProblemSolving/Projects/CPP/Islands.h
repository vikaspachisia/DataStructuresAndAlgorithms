#include <vector>
using namespace std;

class Island {
public:
	int numIslands(vector<vector<char>>& grid) {
		int islands = 0;
		vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
		for (unsigned int i = 0; i < grid.size(); i++) {
			for (unsigned int j = 0; j < grid[0].size(); j++) {				
				if (!visited[i][j] && grid[i][j] == '1') {
					islands++;
					MarkIsland(grid, i, j, visited);
				}
			}
		}
		return islands;
	}



private:
	void MarkIsland(vector<vector<char>>& grid, int row, int col, vector<vector<bool>>& visited) {
		if (row < 0 || row >= grid.size()) return;
		if (col < 0 || col >= grid[0].size()) return;
		if (visited[row][col]) return;
		if (grid[row][col] == '0') return;

		visited[row][col] = true;
		for (unsigned int m = 0; m < 4; m++) {
			MarkIsland(grid, row + xMove[m], col + yMove[m], visited);
		}
	}

	int xMove[4] = { 0, -1, 0, 1 };
	int yMove[4] = { -1, 0, 1, 0 };
};

class TestIsland {
public:
	bool Test() {
		bool testResult = true;

		vector<vector<vector<char>>> grid {
			//test case 1
			{
				{'1','1','1','1','0'},
				{'1','1','0','1','0'},
				{'1','1','0','0','0'},
				{'0','0','0','0','0'}
			},

			//test case 2
			{
				{'1','1','0','0','0'},
				{'1','1','0','0','0'},
				{'0','0','1','0','0'},
				{'0','0','0','1','1'}
			}
		};

		int results[2] = { 1,3 };

		Island island;
		for (int i = 0; i < grid.size(); i++) {
			int islands = island.numIslands(grid[i]);
			if (islands != results[i]) testResult = false;
		}

		return testResult;
	}
};