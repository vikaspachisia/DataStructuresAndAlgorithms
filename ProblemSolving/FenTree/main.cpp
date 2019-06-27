/**
* @author Vikas Pachisia (vikas.pachisia@gmail.com)
*
* @brief Solution to the SPOJ problem 'FENTREE'.
* This module not only implements the algorithm to solve the SPOJ problem
* But it also implements the design to read input in various formats
* (example an input that contains test_id as first line versus the one that does not have it)
* and to skip inputs that do not provide adequate data in the designated format
* but still continue to work on the next test
* (example an input providing string where numbers are expected)
*
* More importantly it implements all the use cases (8) of the Fenwick Tree
* explained in the wiki article and geeks for geeks site.
* @wiki https://en.wikipedia.org/wiki/Fenwick_tree
* updated the article that explains this implementation
*
* @gfg https://contribute.geeksforgeeks.org/binary-indexed-tree-or-segment-tree-all-operations/
*/
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class BIT {
public:
	struct CFIndicies { int lowIndex, highIndex; };

private:
	vector<int> m_bit; //binary indexed table	

public:
	void init(const vector<int>& input) { 
		m_bit.clear();
		setSize(input.size()); 
		for (int i = 0; i < input.size(); i++) { update(i + 1, input[i]); }
	}

	void update(int index, int value) {
		while (index < m_bit.size()) {
			m_bit[index] += value;
			index += (index & -index);
		}
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
	int findIndex(int cumulativeFrequency, bool highestIndexRequired) {
		int returnIndex = -1;
		for (int index = 0, maskIndex = m_bit.size(); maskIndex != 0; maskIndex >>= 1) {
			int biIndex = index + maskIndex;
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
		CFIndicies returnIndices{ -1,-1 };
		for (int index = 0, maskIndex = m_bit.size(); maskIndex != 0; maskIndex >>= 1) {
			int biIndex = index + maskIndex;
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
	
	void setSize(int size) {
		m_bit.resize(size + 1);
	}
};

class BITFacade {
private:
	BIT m_bit1, m_bit2;

public:

	void init(vector<int> input) {
		m_bit1.init(input);
		m_bit2.init(input);
		for (int i = 0; i < input.size(); i++) { update(i+1, input[i]); }
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
		return getCumulativeFrequency(index) - getCumulativeFrequency(index-1);
	}

	int getCumulativeFrequency(int index) {
		return m_bit1.getCumulativeFrequency(index) * index - m_bit2.getCumulativeFrequency(index);
	}

	int getCumulativeFrequency(int index1, int index2) {
		if (index1 > index2) { int tmp = index1; index1 = index2; index2 = tmp; }
		return getCumulativeFrequency(index2) - getCumulativeFrequency(index1 - 1);
	}
};

class Problem {
private:
	struct operation_data { char opcode; int arg1, arg2; };
	FILE *inStream, *outStream;

public:
	Problem() { open_unit_test_files(); }
	~Problem() { close_unit_test_files(); }

	bool continueToRead(istream& instream) {
		bool retVal = true;
		if (instream.eof() || instream.fail() || instream.bad()) retVal = false;
		return retVal;
	}
	
	inline bool isWhiteSpace(const char buffer[])
	{
		string str(buffer);
		str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
		str.erase(str.find_last_not_of(' ') + 1);         //surfixing spaces

		return str.empty();
	}

	int getNextTest(string& test_id, vector<int>& input, vector<operation_data>& operations) {
		int retVal = 0;
		int op_count = 0, inp_count = 0;
		//usingTestIDInInput=true when testid is present in input (used generally during local debugging) otherwise false.
		bool usingTestIDInInput = true, continueRead = true;
		char buffer[1024]{};

		if (usingTestIDInInput) {
			while ((continueRead = continueToRead(cin.getline(buffer, sizeof(buffer)))) && buffer[0] != '#');
			if (continueRead) {
				test_id = buffer;
				while ((continueRead = continueToRead(cin.getline(buffer, sizeof(buffer)))) && buffer[0] == '#') { test_id = buffer; }
			}			
		}
		else {
			continueRead = continueToRead(cin.getline(buffer, sizeof(buffer)));
		}

		
		if (continueRead && !isWhiteSpace(buffer)) { stringstream line(buffer); line >> inp_count; }

		if (continueRead) {
			continueRead = continueToRead(cin.getline(buffer, sizeof(buffer)));
			if (continueRead && !isWhiteSpace(buffer)) {
				stringstream line(buffer);

				input.resize(inp_count);
				for (int i = 0; i < inp_count; i++) { line >> input[i]; }

				continueRead = continueToRead(cin.getline(buffer, sizeof(buffer)));
				if (continueRead && !isWhiteSpace(buffer)) {
					stringstream line(buffer); line >> op_count;

					operations.resize(op_count);
					for (int i = 0; i < op_count && continueRead; i++) {
						continueRead = continueToRead(cin.getline(buffer, sizeof(buffer)));
						if (continueRead && !isWhiteSpace(buffer)) {
							stringstream line(buffer);
							line >> operations[i].opcode >> operations[i].arg1 >> operations[i].arg2; 
							if (operations[i].opcode == 'q')retVal++;
						}
					}
				}
			}
		}
		return retVal;
	}

	void solve()
	{
		string test_id;
		vector<int> input{}, output{};
		vector<operation_data> operations{};
		BITFacade bitf;
		int query_op_count = 0;
		while ((query_op_count = getNextTest(test_id, input, operations))) {
			bitf.init(input);
			output.resize(query_op_count);
			query_op_count = 0;
			for (auto operation : operations) {
				if (operation.opcode == 'u') { bitf.update(operation.arg1, operation.arg2); }
				else if (operation.opcode == 'q') { output[query_op_count++] = bitf.getCumulativeFrequency(operation.arg1, operation.arg2); }
			}

			//output the results;
			cout << test_id << endl;
			for (int i = 0; i < query_op_count; i++) { cout << output[i] << endl; }
		}
	}

	void open_unit_test_files() {
		freopen_s(&inStream, "unit_test_input.txt", "r", stdin);
		freopen_s(&outStream, "unit_test_output.txt", "w", stdout);
		//std::ios_base::sync_with_stdio(false);
	}

	void close_unit_test_files() {
		fclose(stdin);
		fclose(stdout);

		fclose(inStream);
		fclose(outStream);
	}
};

int main() {
	Problem problem;
	problem.solve();
	return 0;
}