#pragma once
#include <map>
#include <sstream>
#include <list>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <ctime>

using namespace std;

class solutionDP {
public:
	int maxSubArray(vector<int>& nums) {
		int res = nums[0];
		vector<int> dp(nums);
		for (int i = 1; i < nums.size(); ++i) {
			dp[i] = max(dp[i - 1] + dp[i], dp[i]);
			res = max(dp[i], res);
		}
		return res;
	}

	int lengthOfLIS(vector<int>& nums) {
		if (nums.size() == 0) return 0;
		int res = 1;
		vector<int> dp(nums.size(), 1);
		for (int i = 1; i<nums.size(); ++i) {
			for (int j = 0; j < i; ++j) {
				if (nums[i] > nums[j]) {
					dp[i] = max(dp[i], dp[j] + 1);
					res = max(res, dp[i]);
				}
			}
		}
		return res;
	}

	int maxEnvelopes(vector<vector<int>>& envelopes) {
		sort(envelopes.begin(), envelopes.end(), [](const auto& a, const auto& b) {
			return a[0] == b[0] ? a[1] > b[1]:a[0] < b[0];
			});
		vector<int> dp(envelopes.size(), 1);
		int res = 1;
		for (int i = 1; i < envelopes.size(); ++i) {
			for (int j = 0; j < i; ++j) {
				if (envelopes[i][1] > envelopes[j][1]) {
					dp[i] = max(dp[j] + 1, dp[i]);
				}
				res = max(res, dp[i]);
			}
		}
		return res;
	}

	int maxProduct(vector<int>& nums) {

	}
};