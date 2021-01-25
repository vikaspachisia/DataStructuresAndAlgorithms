#pragma once
#include "program.h"
#include <string>
#include <vector>

using namespace std;

class program_bit : public program {
private:
	struct operation_data { char opcode; int arg1, arg2, arg3; };
	
	vector<int> input{};
	vector<string> output{};
	vector<operation_data> operations{};	
	BIT bit;
	BITFacade bit_facade;

	string getInputFilename() override { return "bit_input.txt"; }
	string getOutputFilename() override { return "bit_output.txt"; }
	string getExpectedOutputFilename() override { return "bit_output_expected.txt"; }

	//The core function that reads the input, executes the algorithm on the data structure and produces the output.
	void runTests(programdata_reader& inputReader, programdata_writer& outputWriter) override {
		string test_id{};
		int test_type = 0, count = 0;
		stringstream linebuf;

		while (true) {
			if (inputReader.readLine(linebuf)) { linebuf >> test_id >> test_type; } else { break; }
			if (inputReader.readLine(linebuf)) { linebuf >> count; input.resize(count); } else { break; }
			if (inputReader.readLine(linebuf)) { for (int i = 0; i < count; i++) { linebuf >> input[i]; } }	else { break; }
			if (inputReader.readLine(linebuf)) { linebuf >> count; operations.resize(count); } else { break; }
			for (int i = 0; i < count; i++) {
				if (inputReader.readLine(linebuf)) { linebuf >> operations[i].opcode >> operations[i].arg1; }
				if (!linebuf.eof()) { linebuf >> operations[i].arg2; }
				if (!linebuf.eof()) { linebuf >> operations[i].arg3; }
			}

			bit.init(input);
			bit_facade.init(input);
			output.clear();
			for (auto operation : operations) {
				if (operation.opcode == 'u') { performUpdate(test_type, operation); }
				else if (operation.opcode == 'q') { output.push_back(performQuery(test_type, operation)); }
			}

			//output the results;
			outputWriter.getStream() << test_id << " " << test_type << endl;
			//outputWriter.writeLine(test_id + (" " + test_type));
			outputWriter.writeLine(output);

			/*cout << test_id << endl;
			for (int i = 0; i < output.size(); i++) { cout << output[i] << endl; }*/
		}
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
			for (int i = data.arg1; i <= data.arg2; i++) { result << bit_facade.getFrequency(i) << (i != data.arg2 ? " " : ""); }
			break;
		case 8:
			result << bit_facade.getCumulativeFrequency(data.arg1, data.arg2);
			break;
		default:
			break;
		}

		return result.str();
	}
};