#include "header.h"

/*

LCR 086. 分割回文串

给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是 回文串
返回 s 所有可能的分割方案

回文串 是正着读和反着读都一样的字符串

示例 1：
输入：s = "aab"
输出：[["a","a","b"],["aa","b"]]

示例 2：
输入：s = "a"
输出：[["a"]]

提示：
1 <= s.length <= 16
s 仅由小写英文字母组成

注意：本题与主站 131 题相同： https://leetcode-cn.com/problems/palindrome-partitioning/

*/

// 此题目可直接参考 LeetCode 131 的提交
class Solution {
private:
	vector<vector<char>> isPal;
	vector<vector<string>> res;
	vector<string> path;

public:
	vector<vector<string>> partition(string s) {
		int len = s.size();
		isPal.resize(len, vector<char>(len, false));
		for (int palLen = 1; palLen <= len; ++palLen) {
			for (int i = 0; i <= len - palLen; ++i) {
				int j = i + palLen - 1;
				isPal[i][j] =
					(s[i] == s[j] && (palLen < 3 || isPal[i + 1][j - 1]));
			}
		}
		backtrack(s, 0);
		return res;
	}

private:
	void backtrack(const string &s, int idx) {
		if (idx == s.size()) {
			res.push_back(path);
			return;
		}
		for (int j = idx; j < s.size(); ++j) {
			if (isPal[idx][j]) {
				path.push_back(s.substr(idx, j - idx + 1));
				backtrack(s, j + 1);
				path.pop_back();
			}
		}
	}
};
