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

class DaySolution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        vector<bool> dp(s.size() + 1);
        dp[0] = true;
        for (int i = 1; i <= s.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (dp[j] && find(wordDict.begin(), wordDict.end(), s.substr(j, i - j)) != wordDict.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[s.size()];
    }

    vector<string> wordBreaks2(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet;
        for (const auto& word : wordDict) {
            wordSet.insert(word);
        }

        int len = s.size();
        vector<bool> dp(len + 1);
        dp[0] = true;
        for (int i = 1; i <= len; ++i) {
            for (int j = 0; j < i; ++j) {
                if (dp[j] && wordSet.find(s.substr(j, i - j)) != wordSet.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }

        vector<string> res;
        if (dp[len]) {
            vector<string> cur;
            wordBreak2sDFS(s, 0, wordSet, res, cur, dp);
            return res;
        }
        return res;
    }

    void wordBreak2sDFS(string s, int start, unordered_set<string>& wordSet, vector<string>& res, vector<string>& cur, vector<bool>& dp) {
        if (start == s.size()) {
            stringstream  ss;
            for (auto word : cur) {
                ss << word << " ";
            }
            string tmp = ss.str();
            tmp.erase(tmp.end() - 1);
            res.push_back(tmp);
            return;
        }
        for (int i = start; i <= s.size(); ++i) {
            if (dp[i]) {
                string suffix = s.substr(start, i - start);
                if (suffix != "" && wordSet.find(suffix) != wordSet.end()) {
                    cur.push_back(suffix);
                    wordBreak2sDFS(s, i, wordSet, res, cur, dp);
                    cur.pop_back();
                }
            }
        }
    }

    int maxProduct(vector<int>& nums) {
        int len = nums.size();
        if (len == 0) return 0;
        if (len == 1) return nums[0];
        vector<vector<int>> dp(2, vector<int>(nums.size()));
        int res = nums[0];
        dp[0][0] = dp[1][0] = nums[0];
        for (int i = 1; i < len; ++i) {
            dp[0][i] = max(nums[i], max(dp[0][i - 1] * nums[i], dp[1][i - 1] * nums[i]));
            res = max(res, dp[0][i]);
            dp[1][i] = min(nums[i], min(dp[0][i - 1] * nums[i], dp[1][i - 1] * nums[i]));
        }
        return res;
    }

    vector<int> getMaxMatrix(vector<vector<int>>& matrix) {

    }
};
