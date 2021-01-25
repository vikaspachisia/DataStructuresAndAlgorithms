#pragma once

class binary_distance {
public:
	int run()
private:
	int maxDist(int N, int V) {
		int retVal = 0;

		auto levelOfN = level(N), levelOfV = level(V), leftTreeLevel = 0, rightTreeLevel = 0;
		if (isInLeftTree(N, levelOfN)) {
			leftTreeLevel = levelOfN, rightTreeLevel = levelOfN - 1;
		}
		else {
			leftTreeLevel = levelOfN, rightTreeLevel = levelOfN;
		}

		retVal = levelOfV + (isInLeftTree(V, levelOfV) ? rightTreeLevel : leftTreeLevel);

		return retVal;
	}

	bool isInLeftTree(int node) { auto lvl = level(node); return isInLeftTree(node, lvl); }
	bool isInLeftTree(int node, int level) { auto startNode = getStartNodeOnLevel(level); if (node < ((3 * startNode) / 2))return true; else return false; }
	int getStartNodeOnLevel(int level) { return 1 << level; }
	int level(int node) { int depth = -1; while (node > 0) { depth++; node /= 2; } return depth; }
	int max(int a, int b) { return a > b ? a : b; }
};

class program_bd : public program {
private:
	binary_distance bd;
	string getInputFilename() override { return "binary_distance_input.txt"; }
	string getOutputFilename() override { return "binary_distance_output.txt"; }
	string getExpectedOutputFilename() override{ return "binary_distance_output_expected.txt"; }

	void runTests(programdata_reader& reader, programdata_writer& writer) override {
		int testVal = 0, N, V;
		
		testVal = bd.maxDist(6, 2);
		testVal = bd.maxDist(6, 6);
		testVal = bd.maxDist(5, 4);
		testVal = bd.maxDist(2, 2);
		testVal = bd.maxDist(1000000000, 1);
		testVal = bd.maxDist(20, 7);
		testVal = bd.maxDist(12, 4);

		while (cin >> N >> V) {
			testVal = bd.maxDist(N, V);
			cout << testVal << endl;
		}
	}
};