#include <vector>
#include <string>
using namespace std;

class EnlargeTheCave {
public:
	vector <string> enlarge(vector <string> cave, int desiredArea)
	{
		bool ans_found = false;
		const int grid_height = cave.size(), grid_width = cave.size() > 0 ? cave[0].size() : 0;
		vector<vector<bool>> visited(grid_height, vector<bool>(grid_width, false));
		vector<string> ans{};

		for (int i = 0; i < grid_height && !ans_found; ++i) {
			for (int j = 0; j < grid_width && !ans_found; ++j) {
				if (cave[i][j] == '.' && !visited[i][j]) {
					vector<string> enlargedCave{ cave };
					if (updateCave(enlargedCave, visited, --desiredArea, i, j)) {
						ans = enlargedCave;
						ans_found = true;
					}
				}
			}
		}
		return ans;
	}

private:
	bool updateCave(vector<string>& cave, vector<vector<bool>>& visited, int& desiredArea, int x, int y) {
		if (desiredArea == 0)return true;
		visited[x][y] = true;
		for (auto dir : move_dir) {
			int nextx = x + dir.first, nexty = y + dir.second;
			if (nextx >= 0 && nextx < cave.size() && nexty >= 0 && nexty < cave[0].size()) {
				if (!visited[nextx][nexty] && is_move_valid(cave, nextx, nexty)) {
					cave[nextx][nexty] = '.';
					if (updateCave(cave, visited, --desiredArea, nextx, nexty)) return true;
				}
			}
		}
		return false;
	}

	bool is_move_valid(const vector<string>& cave, int x, int y) {
		for (auto dir : move_dir) {
			int nextx = x + dir.first, nexty = y + dir.second;
			if (nextx >= 0 && nextx < cave.size() && nexty >= 0 && nexty < cave[0].size() && cave[nextx][nexty] == 'K') {
				return false;
			}
		}
		return true;
	}

	const vector<pair<int, int>> move_dir{ {-1,0},{1,0},{0,1},{0,-1} };
};

class TestEnlargeTheCave {
public:
	bool Test() {
		EnlargeTheCave algo;
		for (int i = 0; i < desiredArea.size(); i++) {
			auto ans = algo.enlarge(cave[i], desiredArea[i]);
			if (ans != results[i]) {
				//got a different output. may be correct one too! Yet return false.
				return false;
			}
		}
	}

private:
	vector<int> desiredArea{ 7, 5, 6, 10, 82, 6, 12 };
	vector<vector<string>> cave{
		{".##", "###", "###"},
		{".##", "##K", "###"},
		{".##", "##K", "###"},
		{"###K########", "#.#K########", "..#K########", "############"},
		{"###############", "###############", "##K###..####K##", "######..#######", "###############", "##K#########K##", "###############", "###############"},
		{"#K#K###..###K#K##"},
		{"....", "....", "...."}
	};
	vector<vector<string>> results{
		{"...", "..#", "..#" },
		{"..#", ".#K", "..#" },
		{},
		{},
		{"...............", "..#.........#..", ".#K#.......#K##", "###.........###", "###.........###", "##K#.......#K##", "###.........###", "#............##" },
		{"#K#K#......#K#K##" },
		{"....", "....", "...." }
	};	
};