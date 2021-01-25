#pragma once
#include <vector>
using namespace std;

/*
Instead of function pointers a switch statement can also be used as given below.
But function pointers make the solution easily extensible.

switch (m_currentOperatingMode)
{
	case segment_tree::operating_mode::SUM:
		m_tree[nodeid] = m_tree[lchildID] + m_tree[rchildID];
		break;
	case segment_tree::operating_mode::MIN:
		m_tree[nodeid] = min(m_tree[lchildID], m_tree[rchildID]);
		break;
	case segment_tree::operating_mode::MAX:
		m_tree[nodeid] = max(m_tree[lchildID], m_tree[rchildID]);
		break;
	default:
		break;
}
*/

class segment_tree {
	typedef int(segment_tree::*operation)(int, int) ;
	struct operation_data { char opcode; int arg1, arg2, arg3; };
	enum class operating_mode { SUM, MIN, MAX };

private:
	vector<int> m_tree{};
	vector<int> m_lazy{};
	operating_mode m_currentOperatingMode = operating_mode::SUM;
	operation m_currentOperation = &segment_tree::sum;
	int m_currentBoundingValue = 0;

public:
	int max(int a, int b) { return a >= b ? a : b; }
	int min(int a, int b) { return a <= b ? a : b; }
	int sum(int a, int b) { return a + b; }	
	
	void clear() { m_tree.clear(); m_lazy.clear(); }
	void setSize(size_t newSize) { size_t treeSize = floor(2 * pow(2, (ceil(log(newSize) / log(2)))+1)); m_tree.resize(treeSize); m_lazy.resize(treeSize); }
	
	void setOpMode(operating_mode newMode) { 
		m_currentOperatingMode = newMode;
		switch (m_currentOperatingMode)
		{
		case segment_tree::operating_mode::SUM:
			m_currentOperation = &segment_tree::sum;
			m_currentBoundingValue = 0; //adding 0 to any sum will not harm the result.
			break;
		case segment_tree::operating_mode::MIN:
			m_currentOperation = &segment_tree::min;
			m_currentBoundingValue = INT_MAX; //minimum of a 'number' and INT_MAX will prefer to give back the 'number'.
			break;
		case segment_tree::operating_mode::MAX:
			m_currentOperation = &segment_tree::max;
			m_currentBoundingValue = INT_MIN; //maximum of a 'number' and INT_MIN will prefer to give back the 'number'.
			break;
		default:
			break;
		}
	}
	
	void init(const vector<int>& values) {
		clear();
		setSize(values.size());
		//copy(values.begin(), values.end(), back_inserter(m_values));
		initialize(1, 0, values.size() - 1, values);
	}	

	void initialize(int nodeid, int ss, int se, const vector<int>& values) {
		if (ss == se) {
			m_tree[nodeid] = values[ss];
		}
		else {
			int mid=(ss+se)/2, lchildID = 2 * nodeid, rchildID = 2 * nodeid + 1;
			initialize(lchildID, ss, mid, values);
			initialize(rchildID, mid + 1, se, values);
			m_tree[nodeid] = (this->*m_currentOperation)(m_tree[lchildID], m_tree[rchildID]);						
		}
	}

	void update(int nodeid, int ss, int se, int pos, int deltaVal) {
		update(nodeid, ss, se, pos, pos, deltaVal);
	}

	void update(int nodeid, int ss, int se, int rs, int re, int deltaVal) {
		
		int mid = (ss + se) / 2, lchildID = 2 * nodeid, rchildID = 2 * nodeid + 1;

		//Transfer lazy updates to main tree and to child nodes of lazy tree only if the current node is not the leaf node.
		m_tree[nodeid] += m_currentOperatingMode == operating_mode::SUM ? ((se - se) + 1)*m_lazy[nodeid] : m_lazy[nodeid];
		if (ss != se) { m_lazy[lchildID] += m_lazy[nodeid], m_lazy[rchildID] += m_lazy[nodeid]; }
		m_lazy[nodeid] = 0; //no more lazy updates available.

		/*
		if out of range then nothing to process.
		if fully in range then update the main tree directly and child nodes of lazy tree. Stop processing further.
		if overlapping range then perform the normal segment tree operation
		*/
		if (ss > re || se < rs) { return; }
		else if (ss <= se && ss >= rs && se <= re) { 
			m_tree[nodeid] += m_currentOperatingMode==operating_mode::SUM?((se-ss)+1)*deltaVal:deltaVal; 
			if (ss != se) { m_lazy[lchildID] += deltaVal, m_lazy[rchildID] += deltaVal; }
		}
		else {			
			update(lchildID, ss, mid, rs, re, deltaVal);
			update(rchildID, mid + 1, se, rs, re, deltaVal);
			m_tree[nodeid] = (this->*m_currentOperation)(m_tree[lchildID], m_tree[rchildID]);
		}
	}	

	//get value for index at [pos]
	int getFrequency(int nodeid, int ss, int se, int pos) {
		return getCumulativeFrequency(nodeid, ss, se, pos, pos);
	}

	//get value for index from [0..pos]
	int getCumulativeFrequency(int nodeid, int ss, int se, int pos) {
		return getCumulativeFrequency(nodeid, ss, se, 0, pos);
	}

	int getCumulativeFrequency(int nodeid, int ss, int se, int qs, int qe) {
		int retVal = m_currentBoundingValue;
		int mid = (ss + se) / 2, lchildID = 2 * nodeid, rchildID = 2 * nodeid + 1;

		m_tree[nodeid] += m_currentOperatingMode == operating_mode::SUM ? ((se - ss) + 1)*m_lazy[nodeid] : m_lazy[nodeid];
		if (ss != se) { m_lazy[lchildID] += m_lazy[nodeid], m_lazy[rchildID] += m_lazy[nodeid]; }
		m_lazy[nodeid] = 0;

		if (!(ss>qe || se<qs)) {
			if (ss >= qs && se <= qe) { retVal = m_tree[nodeid]; }
			else {
				retVal = (this->*m_currentOperation)(getCumulativeFrequency(lchildID, ss, mid, qs, qe), getCumulativeFrequency(rchildID, mid + 1, se, qs, qe));
			}
		}
		return retVal;
	}
};