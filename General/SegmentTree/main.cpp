#include <iostream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "segment_tree.h"

using namespace std;

class Problem {
private:
	struct operation_data { char opcode; int arg1, arg2, arg3; };

	string test_case_id{};
	vector<int> input{};
	vector<string> output{};
	vector<operation_data> operations{};
	segment_tree stree;
	FILE *inStream = nullptr, *outStream = nullptr;

public:
	Problem() { open_unit_test_files(); }
	~Problem() { close_unit_test_files(); }

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

	bool isLineRead(istream& instream) {
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

	string readNextValidLine() {
		string retVal{};
		bool lineReadSuccessfully = false;
		char buffer[1024]{};

		while ((lineReadSuccessfully = isLineRead(cin.getline(buffer, sizeof(buffer)))) && isWhiteSpace(buffer));
		if (lineReadSuccessfully) retVal = buffer;

		return retVal;
	}

	int readNextTest() {
		int test_type_code = 0, count = 0;
		string prevLineRead{}, lineRead{};

		//skip all corrupted input or whitespace only lines from input file until you get back to the next valid test case.
		lineRead = readNextValidLine();
		while (!lineRead.empty() && lineRead[0] != '#') { lineRead = readNextValidLine(); }

		//skip all lines starting with '#' and use only the last of these lines for valid test input. Other lines can be treated as comments.
		while (!lineRead.empty() && lineRead[0] == '#') { prevLineRead = lineRead;  lineRead = readNextValidLine(); }

		//read test case id and test type code.
		if (!prevLineRead.empty() && prevLineRead[0] == '#') { stringstream line(prevLineRead); line >> test_case_id >> test_type_code; }

		//read input data
		if (!lineRead.empty()) {
			stringstream line(lineRead); line >> count; input.resize(count);
			lineRead = readNextValidLine();
			if (!lineRead.empty()) {
				line.str("");
				line.clear();
				line << lineRead;
				for (int i = 0; i < count; i++) { line >> input[i]; }
			}
		}

		//read the operations to be performed
		lineRead = readNextValidLine();
		if (!lineRead.empty()) {
			stringstream line(lineRead); line >> count;
			operations.resize(count);
			for (int i = 0; i < count; i++) {
				lineRead = readNextValidLine();
				if (!lineRead.empty()) {
					line.str("");
					line.clear();
					line << lineRead;
					line >> operations[i].opcode >> operations[i].arg1;
					if (!line.eof()) line >> operations[i].arg2;
					if (!line.eof()) line >> operations[i].arg3;
				}
			}
		}

		return test_type_code;
	}

	void performUpdate(int test_type_code, operation_data data) {
		switch (test_type_code) {
		case 1:
		case 2:
		case 3:
		case 4:
			stree.update(1,0,input.size()-1, data.arg1-1, data.arg2);
			break;
		case 5:
		case 6:
		case 7:
		case 8:
			stree.update(1, 0, input.size()-1, data.arg1-1, data.arg2-1, data.arg3);
			break;
		default:
			break;
		}
	}

	string performQuery(int test_type_code, operation_data data) {
		stringstream result{};
		int testSingleBitMethod = 0;
		switch (test_type_code) {
		case 1:
		case 5:
			result << stree.getFrequency(1,0,input.size()-1, data.arg1-1);
			break;
		case 2:
		case 6:
			result << stree.getCumulativeFrequency(1, 0, input.size()-1, data.arg1-1);
			break;
		case 3:
		case 7:
			for (int i = data.arg1-1; i < data.arg2; i++) { result << stree.getFrequency(1, 0, input.size()-1, i) << (i != data.arg2-1 ? " " : ""); }
			break;
		case 4:
		case 8:
			result << stree.getCumulativeFrequency(1, 0, input.size()-1, data.arg1-1, data.arg2-1);
			break;		
		default:
			break;
		}

		return result.str();
	}

	void solve()
	{
		int test_type_code = 0;
		while ((test_type_code = readNextTest()) != 0) {
			stree.init(input);
			output.clear();
			for (auto operation : operations) {
				if (operation.opcode == 'u') { performUpdate(test_type_code, operation); }
				else if (operation.opcode == 'q') { output.push_back(performQuery(test_type_code, operation)); }
			}

			//output the results;
			cout << test_case_id << endl;
			for (int i = 0; i < output.size(); i++) { cout << output[i] << endl; }
		}
	}
};

int main() {
	Problem problem;
	problem.solve();
	return 0;
}