#include "header.h"

/*

剑指 Offer II 094.最少回文分割

给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是回文。返回符合要求的最少分割次数 。

示例 1：
输入：s = "aab"
输出：1
解释：只需一次分割就可将 s 分割成 ["aa","b"] 这样两个回文子串。

示例 2：
输入：s = "a"
输出：0

示例 3：
输入：s = "ab"
输出：1

提示：
1 <= s.length <= 2000
s 仅由小写英文字母组成

注意：本题与主站 132 题相同： https://leetcode-cn.com/problems/palindrome-partitioning-ii/

*/

// 备忘录
class Solution1 {
public:
	int minCut(string s) {
		int len = s.size();
		vector<vector<char>> isPal(len, vector<char>(len, false));
		for (int palLen = 1; palLen <= len; ++palLen) {
			for (int i = 0; i <= len - palLen; ++i) {
				int j = i + palLen - 1;
				isPal[i][j] = (s[i] == s[j] && (palLen < 3 || isPal[i + 1][j - 1]));
			}
		}
		vector<int> memo(len, -1);
		return helper(s, len - 1, isPal, memo);
	}

private:
	int helper(string &s, int end, vector<vector<char>> &isPal, vector<int> &memo) {
		if (memo[end] != -1) return memo[end];
		int len = s.size();
		if (isPal[0][end]) return 0;
		int minNum = INT_MAX;
		for (int i = end; i >= 0; --i) {
			if (isPal[i][end]) minNum = min(minNum, 1 + helper(s, i - 1, isPal, memo));
		}
		return memo[end] = minNum;
	}
};

// 自底而上的动态规划
class Solution2 {
public:
	int minCut(string s) {
		int len = s.size();
		vector<vector<char>> isPal(len, vector<char>(len, false));
		for (int palLen = 1; palLen <= len; ++palLen) {
			for (int i = 0; i <= len - palLen; ++i) {
				int j = i + palLen - 1;
				isPal[i][j] = (s[i] == s[j] && (palLen < 3 || isPal[i + 1][j - 1]));
			}
		}
		vector<int> dp(len + 1, -1);
		for (int i = 0; i < len; ++i) {
			int minNum = INT_MAX;
			for (int j = 0; j <= i; ++j) {
				if (isPal[j][i]) minNum = min(minNum, dp[j] + 1);
			}
			dp[i + 1] = minNum;
		}
		return dp[len];
	}
};
