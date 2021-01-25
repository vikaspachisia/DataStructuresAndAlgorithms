#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>

using namespace std;

#pragma region Abstractions

/*
A base class that is responsible to manage the data for the program.
Basically it is responsible for reading from input test files,
writing to ouput results file and sanitizing corruput data if possible.
This base class does not do much. The specialized classes will actually do the reading and the writing.
*/
class AbstractTestData {
	
public:		
	int lineNumber() { return line_number; }
	string filepath() { return m_filepath; }
	string filepathfull() { return m_filepathroot + m_filepath; }
	void open(bool redirect_stdio) { if (!m_datastream.is_open()) { internalOpen(redirect_stdio); } }
	void close() { if (m_datastream.is_open()) { m_datastream.close(); } }
	fstream& getStream() { return m_datastream; }

protected:
	string getDataFilepath() const { return m_datafilepath; }

protected:
	static const int linewidth = 1024; //a line of test data should not go beyond this size.	
	int line_number = 0;
	fstream m_datastream{ };
	string m_datafilepath{};

private:
	virtual void internalOpen(bool redirect_stdio) = 0;
};

#pragma endregion

#pragma region Implementations

/*
This class can be used to read input for the program from a file or from standard console.
When redirection is enabled, the standard input such as 'stdin' or 'std::cin' will also be redirected from the file.
*/
class TestDataReader : public AbstractTestData {
private:
	string lastLine{};
public:
	programdata_reader(string filepath) : programdata(filepath) { }

	vector<string> readComments() {
		vector<string> retVal{};

		if (lastLine.empty()) lastLine = readNextValidLine();
		while (lastLine.length() > 1 && lastLine.at(0) == '/' && lastLine.at(1) == '/') {
			retVal.push_back(lastLine);
			line_number++;
			lastLine = readNextValidLine();
		}

		return retVal;
	}

	bool readLine(stringstream& linebuf) {
		bool retVal = false;

		linebuf.clear(); linebuf.str("");
		if (lastLine.empty()) lastLine = readNextValidLine();
		if (!lastLine.empty()) {
			retVal = true;
			line_number++;
			linebuf << lastLine;
			lastLine = readNextValidLine();
		}
		return retVal;
	}

	void skiplines(int count) {
		for (int i = 0; i < count; i++) readNextValidLine();
	}
	//Lines read so far.
	int linesRead() { return line_number; }

private:
	void internalOpen(bool redirect_stdio) override {
		m_datastream.open(filepathfull(), ios::in);
		if (redirect_stdio) { cin.set_rdbuf(m_datastream.rdbuf()); }
	}

	inline bool isWhiteSpace(const char buffer[]) {
		string str(buffer);
		str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
		str.erase(str.find_last_not_of(' ') + 1);         //surfixing spaces

		return str.empty();
	}

	bool isLineRead() {
		bool retVal = true;
		if (m_datastream.eof() || m_datastream.fail() || m_datastream.bad()) retVal = false;
		return retVal;
	}

	string readNextValidLine() {
		string retVal{};
		bool lineReadSuccessfully = false;
		char buffer[linewidth]{};
		
		m_datastream.getline(buffer, sizeof(buffer));
		while ((lineReadSuccessfully = isLineRead()) && isWhiteSpace(buffer)) { m_datastream.getline(buffer, sizeof(buffer)); }
		if (lineReadSuccessfully) retVal = buffer;

		return retVal;
	}
};

/*
The writer class can be used to write the output of the program to a file.
When redirection is enabled, the standard output such as 'stdout' or 'std::cout' will also be redirected to the file.
*/
class TestDataWriter : public AbstractTestData {
public:
	programdata_writer(string filepath) :programdata(filepath) { }

	/*
	write text as comments. comments start with '//'.
	A common scenario is to read comments from expected output file and write them into the actual output file.
	This way comparing actual output with expected output becomes easy.
	Also understanding the output becomes easy by reading those comments.
	*/
	void writeComments(const vector<string>& comments) {
		for (auto comment : comments) {
			if (comment[0] == '/' && comment[1] == '/')m_datastream << comment << endl;
			else if (comment[0] = '/')m_datastream << "/" << comment << endl;
			else m_datastream << "//" << comment << endl;
		}
	}

	/*
	write the list of items one each on a line.
	*/
	template <typename T>
	void writeLine(const vector<T>& items) {
		for (auto item : items) {
			m_datastream << item << endl;
		}
	}

	/*
	write the list of items on a line separated by the 'separator' character.
	generally used to write space separated items on a line.
	Tip: use '\n' as sperator to write each item on a different line.
	Tip: use '' as separator character to ignore the separator.
	*/
	template <typename T>
	void write(const vector<T>& items, char separator = ' ') {
		for (auto item : items) {
			m_datastream << item << separator;
		}
	}

	/*
	write a single item onto the current line.
	*/
	template <typename T>
	void write(const T& item) {
		m_datastream << item;
	}

	/*
	write a single item onto the current line and move to the next line.
	*/
	template <typename T>
	void writeLine(const T& item) {
		m_datastream << item << endl;
	}

private:
	bool isLineWritten() {
		bool retVal = false;
		if (m_datastream.eof() || m_datastream.fail() || m_datastream.bad()) retVal = false;
		return retVal;
	}

	void internalOpen(bool redirect_stdio) override {
		m_datastream.open(filepathfull(), ios::out);
		if (redirect_stdio)cout.set_rdbuf(m_datastream.rdbuf());
	}
};

#pragma endregion