#pragma once
#include "program.h"

class tv_subscription {
public:
	int minimumSubscriptions(const vector<int>& A, int N, int K, int D) {
		int retVal = 0, minVal=0;
		vector<int> cnt(K+1);
		
		for (int i = 0; i < D; i++) { cnt[A[i]]++; if (cnt[A[i]] == 1)minVal++; }

		retVal = minVal;
		for (int i = D; i < N; i++) {
			cnt[A[i]]++; if (cnt[A[i]] == 1)minVal++;
			cnt[A[i - D]]--; if (cnt[A[i - D]] == 0)minVal--;
			if (minVal < retVal)retVal = minVal;
		}

		return retVal;
	}	
};

class program_tv_subscription : public program {
private:
	tv_subscription tvs;
	string getInputFilename() override { return "tv_subscription_input.txt"; }
	string getOutputFilename() override { return "tv_subscription_output.txt"; }
	string getExpectedOutputFilename() override{ return "tv_subscription_output_expected.txt"; }

	void runTests(programdata_reader& reader, programdata_writer& writer) override {
		int T, N, K, D, ANS;
		vector<int> A(1000001);

		cin >> T;
		for (int t = 1; t <= T; t++) {
			cin >> N >> K >> D;
			for (int i = 0; i < N; i++) { cin >> A[i]; }

			ANS = tvs.minimumSubscriptions(A, N, K, D);

			cout << ANS << endl;
		}
	}
};