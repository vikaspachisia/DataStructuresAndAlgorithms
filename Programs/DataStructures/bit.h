#pragma once
#include <vector>
using namespace std;

class BIT {
public:
	struct CFIndicies { size_t lowIndex, highIndex; };

private:
	vector<int> m_bit; //binary indexed table	

public:
	void init(const vector<int>& input) {
		m_bit.clear();
		setSize(input.size());
		for (int i = 0; i < input.size(); i++) { update(i + 1, input[i]); }
	}

	void clear() { m_bit.clear(); }
	void setSize(size_t size) {
		m_bit.resize(size + 1);
	}

	void update(int index, int value) {
		while (index < m_bit.size()) {
			m_bit[index] += value;
			index += (index & -index);
		}
	}

	void update(int index1, int index2, int value) {
		update(index1, value);
		update(index2 + 1, -value);
	}

	int getCumulativeFrequency(int index) {
		int retVal = 0;
		if (index < m_bit.size()) {
			while (index != 0) {
				retVal += m_bit[index];
				index -= (index & -index);
			}
		}
		return retVal;
	}

	int getCumulativeFrequency(int index1, int index2) {
		if (index1 > index2) { int tmp = index1; index1 = index2; index2 = tmp; }
		return getCumulativeFrequency(index2) - getCumulativeFrequency(index1 - 1);
	}

	int getFrequency(int index) {
		int retVal = m_bit[index];
		int common_ancestor_index = index - (index & -index);
		if (index > 0) {
			index--;
			while (index != common_ancestor_index) {
				retVal -= m_bit[index];
				index -= (index & -index);
			}
		}
		return retVal;
	}

	//works only for non-decreasing cumulative frequencies
	size_t findIndex(int cumulativeFrequency, bool highestIndexRequired) {
		size_t returnIndex = -1;
		for (size_t index = 0, maskIndex = m_bit.size(); maskIndex != 0; maskIndex >>= 1) {
			size_t biIndex = index + maskIndex;
			if (biIndex < m_bit.size() && cumulativeFrequency >= m_bit[biIndex]) {
				index = biIndex;
				cumulativeFrequency -= m_bit[biIndex];
				if (cumulativeFrequency == 0) {
					returnIndex = index;
					if (!highestIndexRequired) break;
				}
			}
		}
		return returnIndex;
	}

	CFIndicies findIndices(int cumulativeFrequency) {
		CFIndicies returnIndices{ static_cast<size_t>(-1), static_cast<size_t>(-1) };
		for (size_t index = 0, maskIndex = m_bit.size(); maskIndex != 0; maskIndex >>= 1) {
			size_t biIndex = index + maskIndex;
			if (biIndex < m_bit.size() && cumulativeFrequency >= m_bit[biIndex]) {
				index = biIndex;
				cumulativeFrequency -= m_bit[biIndex];
				if (cumulativeFrequency == 0) {
					if (returnIndices.lowIndex == -1) returnIndices.lowIndex = index;
					returnIndices.highIndex = index;
				}
			}
		}
		return returnIndices;
	}	
};
