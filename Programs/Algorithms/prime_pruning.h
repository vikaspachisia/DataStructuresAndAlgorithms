#pragma once
#include "program.h"
#include <algorithm>

using namespace std;

class prime_pruning {
public:
	string getString(int N, int K) {
		string retVal{};
		vector<int> primes = primenumbers(N);
		for (int i = 0; i < primes.size(); i++) {
			retVal.push_back('a' + (primes[i] % 26));
		}

		retVal = getLargestString(retVal);

		return retVal;
	}
private:

	string getLargestString(string input) {
		string sortedVal{ input };
		std::sort(sortedVal.begin(), sortedVal.end());

	}
	vector<int> primenumbers(int N) {
		vector<int> retVal{};
		int currNum = 3;

		if (N > 0) { retVal.push_back(2); N--; }
		while (N > 0) {
			if (isPrime(currNum)) { retVal.push_back(currNum); N--; }
			currNum++;
		}

		return retVal;
	}

	bool isPrime(int num) {
		bool retVal = true;
		for (int i = 3; i*i < num; i += 2) {
			if (num%i == 0) { retVal = false; break; }
		}
		return retVal;
	}
};

class program_tv_subscription : public program {
private:
	prime_pruning pp;
	string getInputFilename() override { return "prime_pruning_input.txt"; }
	string getOutputFilename() override { return "prime_pruning_output.txt"; }
	string getExpectedOutputFilename() override { return "prime_pruning_output_expected.txt"; }

	void runTests(programdata_reader& reader, programdata_writer& writer) override {
		int T, N, K;
		string result;

		cin >> T;
		for (int t = 1; t <= T; t++) {
			cin >> N >> K;
			
			result = pp.getString(N, K);

			cout << result << endl;
		}
	}
};