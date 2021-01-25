#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        double result = 0.0;
        result = nums1.size()<nums2.size() ? findMedian(nums1, nums2) : findMedian(nums2,nums1);
        return result;
    }

private:
    double findMedian(vector<int>& nums1, vector<int>& nums2) {
        double result = 0.0;
        int low = 0, high = nums1.size(), totalSize = nums1.size() + nums2.size();

        while (low <= high) {
            int partitionX = (low + high) / 2;
            int partitionY = (totalSize + 1)/2 - partitionX;

            int maxLeftX = partitionX == 0 ? INT_MIN : nums1[partitionX-1];
            int minRightX = partitionX == nums1.size() ? INT_MAX : nums1[partitionX];

            int maxLeftY = partitionY == 0 ? INT_MIN : nums2[partitionY-1];
            int minRightY = partitionY == nums2.size() ? INT_MAX : nums2[partitionY];

            if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
                if (totalSize % 2 == 0) {
                    result = ((double)max(maxLeftX, maxLeftY) + (double)min(minRightX, minRightY))/2;
                }
                else {
                    result = max(maxLeftX, maxLeftY);
                }
                break;
            }
            else {
                if (maxLeftX > minRightY) { high = partitionX - 1; }
                else { low = partitionX + 1; }
            }
        }

        return result;
    }

    int findMinIndex(vector<int>& nums, int low, int high, int value) {
        int mid = (low + high) / 2;
        while (low < high) {
            if (nums[mid] <= value) { low = mid; }
            else { high = mid - 1; }
            mid = (low + high) / 2;
        }
        return mid;
    }
    inline double getMidValue(vector<int>& nums) {
        double result = 0.0;
        int n1 = nums.size();
        if (n1 > 1 && (n1 % 2 == 0)) {
            result = (nums[n1 / 2] + nums[n1 / 2 + 1]) / 2;
        }
        else {
            result = (double)nums[n1 / 2];
        }
        return result;
    }
};

int main() {
    int TC = 1;
    vector<vector<int>> nums1{ {1,2}, {},{},{1},{0},{1}, {1,2}, { 2 }, {1,2,3}, {3,3,3}, {3,3,3} }, nums2{ {3,4},  {}, {1}, {}, {0}, {1}, {2},  { 1,2 }, {1,2,3}, {2 , 2, 2}, {3,3,3} };
    Solution s;

    for (int i = 0; i < TC; i++) {
        auto res = s.findMedianSortedArrays(nums1[i], nums2[i]);
        cout << "Solution result: " << res << endl;
    }
	return 0;
}