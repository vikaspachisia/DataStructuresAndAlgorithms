#pragma once
#include "program.h"

class p_binary {
public:
	int getCount(int N, int P) {
		int i = 1, count=0, retVal=-1;
		while ((N - i * P) >= i && retVal==-1) {
			count = getBitCount(N - i * P);
			if (count <= i) retVal = i;			
			i++;
		}
		return retVal;
	}

private:
	int getBitCount(int value) {
		int retVal = 0;
		while (value)
		{
			retVal++;
			value -= (value & -value);
		}
		return retVal;
	}
};

class program_p_binary : public program {
private:
	p_binary algo;
	string getInputFilename() override { return "p_binary_input.txt"; }
	string getOutputFilename() override { return "p_binary_output.txt"; }
	string getExpectedOutputFilename() override { return "p_binary_output_expected.txt"; }

	void runTests(programdata_reader& reader, programdata_writer& writer) override {
		int N, P, ANS;
		while (cin >> N >> P) {
			ANS = algo.getCount(N, P);
			cout << ANS << endl;
		}
	}
};
