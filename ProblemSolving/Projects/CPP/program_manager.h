#pragma once
#include "programdata.h"
#include <string>
#include <vector>

using namespace std;

class program {
public:
	void run(bool redirectIO = true)
	{
		programdata_reader inputReader(getInputFilename());
		programdata_reader expectedOutputReader(getExpectedOutputFilename());
		programdata_writer outputWriter(getOutputFilename());

		expectedOutputReader.open(false);
		vector<string> comments = expectedOutputReader.readComments();
		expectedOutputReader.close();

		inputReader.open(redirectIO);
		outputWriter.open(redirectIO);

		/*inputReader.open(static_cast<iostream&>(std::cin));
		outputWriter.open(static_cast<iostream&>(std::cout));*/

		outputWriter.writeComments(comments);
		comments = inputReader.readComments();

		inputReader.close(); inputReader.open(redirectIO);
		inputReader.skiplines(comments.size());

		runTests(inputReader, outputWriter);

		inputReader.close();
		outputWriter.close();
	}

private:	
	virtual string getInputFilename() = 0;
	virtual string getExpectedOutputFilename() = 0;
	virtual string getOutputFilename() = 0;
	virtual void runTests(programdata_reader& inputReader, programdata_writer& outputWriter) = 0;
};