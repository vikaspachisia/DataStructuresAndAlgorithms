#pragma once
#include "bit.h"
#include <vector>
using namespace std;

class BITFacade {
private:
	BIT m_bit1, m_bit2;

public:

	void init(vector<int> input) {
		m_bit1.clear();
		m_bit2.clear();

		m_bit1.setSize(input.size());
		m_bit2.setSize(input.size());
		for (int i = 0; i < input.size(); i++) { update(i + 1, input[i]); }
	}

	void update(int index, int value) {
		update(index, index, value);
	}

	void update(int index1, int index2, int value) {
		if (index1 > index2) { int tmp = index1; index1 = index2; index2 = tmp; }
		m_bit1.update(index1, value);
		m_bit1.update(index2 + 1, -value);
		m_bit2.update(index1, value*(index1 - 1));
		m_bit2.update(index2 + 1, -value * index2);
	}

	int getFrequency(int index) {
		return getCumulativeFrequency(index) - getCumulativeFrequency(index - 1);
	}

	int getCumulativeFrequency(int index) {
		return m_bit1.getCumulativeFrequency(index) * index - m_bit2.getCumulativeFrequency(index);
	}

	int getCumulativeFrequency(int index1, int index2) {
		if (index1 > index2) { int tmp = index1; index1 = index2; index2 = tmp; }
		return getCumulativeFrequency(index2) - getCumulativeFrequency(index1 - 1);
	}
};
