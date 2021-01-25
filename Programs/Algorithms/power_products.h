#pragma once
#include "program.h"
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class power_products {
public:
	int getCount(int N, short K, vector<int>& A) {
		int retVal=0;
		cache.clear(); cache[0]=0, cache[1] = K;

		for (int i = 1; i < N; i++) {
			for (int j = 0; j < i; j++) {
				if (logK(A[i] * A[j], K) > 0)retVal++;
			}
		}
		
		return retVal;
	}

private:
	short logK(long value, short K) {
		int retVal = 0; 
		short finalK = 0;
		long ipowk = 1;

		if ((itr = cache.find(value)) != cache.end()) { 
			if(itr->second == K) retVal = 1;
			else retVal = 0;
		}
		else {
			for (int i = 2; i < 100000 && ipowk < value; i++) {
				ipowk = 1, finalK = 0;
				for (int j = 1; j <= K && ipowk < value; j++) {
					ipowk *= i;	finalK = j;
				}
			}
			if (ipowk == value && finalK == K) { cache[value] = K; retVal = 1; }
			else{ cache[value] = 0; retVal = 0; }
		}
		return retVal;
	}
	std::map<long, short> cache;
	std::map<long, short>::const_iterator itr;
};

class program_power_products : public program {
private:
	power_products algo;
	string getInputFilename() override { return "power_products_input.txt"; }
	string getOutputFilename() override { return "power_products_output.txt"; }
	string getExpectedOutputFilename() override { return "power_products_output_expected.txt"; }

	void runTests(programdata_reader& reader, programdata_writer& writer) override {
		int N, K, ANS;
		vector<int> A(100001);
		while (cin >> N >> K) {
			for (int i = 0; i < N; i++) { cin >> A[i]; }
			ANS = algo.getCount(N, K, A);
			cout << ANS << endl;
		}
	}
};
