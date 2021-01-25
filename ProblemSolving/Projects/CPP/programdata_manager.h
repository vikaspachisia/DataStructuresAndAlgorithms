#pragma once
#include "programdata.h"
#include <string>
#include <map>

using namespace std;

class programdata_manager {
public:
	static shared_ptr<programdata_manager> instance() {
		if (!m_instance) {
			m_instance = make_shared<programdata_manager>();
		}
		return m_instance;
	}

	string getInputFilename(const programdata& programData) {
		return programData.getName() + "_" + m_inputFilenames[""];
	}
	string getOutputFilename(const programdata& programData) {
		return programData.getName() + "_" + m_outputFilenames[""];
	}
	string getExpectedOutputFilename(const programdata& programData) {
		return programData.getName() + "_" + m_expectedOutputFilenames[""];
	}
	string getDirectoryRelative() {
		return "..\\..\\..\\DataFiles";
	}
	string getDirectoryAbsolute(){
	}
private:
	programdata_manager(){
		initFilenames();
	}

	void initFilenames() {
		m_inputFilenames[""] = "input.txt";
		m_outputFilenames[""] = "output.txt";
		m_expectedOutputFilenames[""] = "output_expected.txt";

		m_inputFilenames["temp"] = "temp_input.txt";
		m_outputFilenames["temp"] = "temp_output.txt";
		m_expectedOutputFilenames["temp"] = "temp_output_expected.txt";
	}
private:
	static shared_ptr<programdata_manager> m_instance;

	map<string, string> m_inputFilenames;
	map<string, string> m_outputFilenames;
	map<string, string> m_expectedOutputFilenames;
};