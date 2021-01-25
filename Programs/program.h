#pragma once
#include "comment_handler.h"
#include <iostream>
using namespace std;

class AbstractProgram {
public:
	string Name() { return ProgramName(); }
	void Run() { 
		cout << "Waiting for input..." << endl;
		RunTests(); 
		cout << "Finished running the program." << endl;
	}
	void Run(istream inputstream, ostream outputstream) 
	{
		cout << "Taking care of comments...";

		CommentHandler::SkipComments(inputstream, outputstream);

		cout << "Reading input from file..." << endl;
		
		auto cinstreambuf_backup = cin.rdbuf();
		auto coutstreambuf_backup = cout.rdbuf();

		cin.set_rdbuf(inputstream.rdbuf());
		cout.set_rdbuf(outputstream.rdbuf());		

		RunTests();

		cin.set_rdbuf(cinstreambuf_backup);
		cout.set_rdbuf(coutstreambuf_backup);

		cout << "Finished running the program." << endl;
	}
private:
	virtual string ProgramName() = 0;
	virtual void RunTests() = 0;
};