#pragma once
#include "program.h"
#include <iostream>
#include <vector>

using namespace std;

class three_sum {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> answer;
        int numsSize = nums.size();
        sort(nums.begin(), nums.end());
        for (int i = 0; i < numsSize - 2; i++) {
            if (i > 0 && nums[i] == nums[i - 1])continue;

            int currentElement = nums[i];
            int low = i + 1, high = numsSize - 1;
            while (low < high)
            {
                bool lowChanged = false;
                if (low > i + 1) {
                    while (low < high && nums[low] == nums[low - 1]) { low++; lowChanged = true; }
                }
                if (!lowChanged && high < numsSize - 1) {
                    while (high > low && nums[high] == nums[high + 1]) { high--; }
                }

                if (low < high) {
                    int currentSum = currentElement + nums[low] + nums[high];
                    if (currentSum == 0) {
                        answer.push_back(vector<int>{currentElement, nums[low], nums[high]});
                        low++;
                        high--;
                    }
                    else if (currentSum < 0) {
                        low++;
                    }
                    else {
                        high--;
                    }
                }
            }
        }
        //sort(answer.begin(), answer.end());
        //answer.erase(unique(answer.begin(), answer.end()), answer.end());

        return answer;
    }
};

class program_threesum : public program {
private:
    three_sum algo;
	string getInputFilename() override { return "3Sum_input.txt"; }
	string getOutputFilename() override { return "3Sum_output.txt"; }
	string getExpectedOutputFilename() override { return "3Sum_output_expected.txt"; }

	void runTests(programdata_reader& reader, programdata_writer& writer) override {
		int N;
		vector<vector<int>> A(100001);
        vector<vector<int>> ANS;
        //update code to read input and run tests.        
	}
};
