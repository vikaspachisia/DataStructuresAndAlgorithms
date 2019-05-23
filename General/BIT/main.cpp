//write this in geeks for geeks.
#include <iostream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include "bit.h"
#include "bitfacade.h"

using namespace std;

class Problem {
private:
	struct operation_data { char opcode; int arg1, arg2, arg3; };

	string test_case_id{};
	vector<int> input{};
	vector<string> output{};
	vector<operation_data> operations{};
	BIT bit{};
	BITFacade bit_facade{};
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
		if(lineReadSuccessfully) retVal = buffer;

		return retVal;
	}

	int readNextTest() {		
		int test_type_code = 0, count = 0;
		string prevLineRead{}, lineRead{};

		//skip all corrupted input or whitespace only lines from input file until you get back to the next valid test case.
		lineRead = readNextValidLine();
		while(!lineRead.empty() && lineRead[0] != '#'){ lineRead = readNextValidLine(); }

		//skip all lines starting with '#' and use only the last of these lines for valid test input. Other lines can be treated as comments.
		while (!lineRead.empty() && lineRead[0] == '#') { prevLineRead = lineRead;  lineRead = readNextValidLine(); }

		//read test case id and test type code.
		if (!prevLineRead.empty() && prevLineRead[0] == '#') { stringstream line(prevLineRead); line >> test_case_id >> test_type_code;  }

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
			bit.update(data.arg1, data.arg2);
			break;		
		case 5:
		case 6:
		case 7:
		case 8:
			bit_facade.update(data.arg1, data.arg2, data.arg3);
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
			result << bit.getFrequency(data.arg1);
			break;
		case 2:
			result << bit.getCumulativeFrequency(data.arg1);
			break;
		case 3:
			for (int i = data.arg1; i <= data.arg2; i++) { result << bit.getFrequency(i) << (i != data.arg2 ? " " : ""); }
			break;
		case 4:
			result << bit.getCumulativeFrequency(data.arg1, data.arg2);
			break;
		case 5:
			result << bit_facade.getFrequency(data.arg1);
			break;
		case 6:
			result << bit_facade.getCumulativeFrequency(data.arg1);
			break;
		case 7:
			for (int i = data.arg1; i <= data.arg2; i++) { result << bit_facade.getFrequency(i) << (i!=data.arg2? " ":""); }
			break;
		case 8:
			result << bit_facade.getCumulativeFrequency(data.arg1, data.arg2);
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
			bit.init(input);
			bit_facade.init(input);
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