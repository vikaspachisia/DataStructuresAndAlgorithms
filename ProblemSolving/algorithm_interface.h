#include <iostream>
#include <string>
#include <vector>

using namespace std;

class algorithm {
public:
	void run(istream& input, ostream& output) {
		

		if(comments.size() > 0 && )
		runTests(input, output)
	}

private:
	vector<string> readComments(iostream& dataStream) {
		string line{};		
		int commentsLineCount = 0;
		bool commentsReadCompleted = false;

		auto currposition = dataStream.cur;
		while (getline(input, line) && !commentsReadCompleted)
		{
			//use any fancy method to find if the line starts with a block comment. But the following suffices for now.
			if (line.length() >= 2 && line[0] == '/' && line[1] == '*') {
				comments.push_back(line);
				while (getline(input, line) && !commentsReadCompleted) {
					//If the input is corrupted then read the entire input but ignore the content.
					//This will help avoid running the program on corrupted input and also avoid consuming too much memory.
					if (line.length() >= 2 && line[0] == '*' && line[1] == '/') { comments.push_back(line); commentsReadCompleted = true; }
					else { if (commentsLineCount < 100) { comments.push_back(line); commentsLineCount++; } }
				}
			}
		}
		dataStream.
	}
	
	void runTests(istream& input, ostream& output) = 0;

private:
	vector<string> comments{};
};