#include "header.h"

/*

剑指 Offer II 095. 最长公共子序列

给定两个字符串 text1 和 text2，返回这两个字符串的 最长公共子序列 的长度。如果不存在公共子序列，返回 0
一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串
例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列
两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列

示例 1：
输入：text1 = "abcde", text2 = "ace"
输出：3
解释：最长公共子序列是 "ace" ，它的长度为 3

示例 2：
输入：text1 = "abc", text2 = "abc"
输出：3
解释：最长公共子序列是 "abc" ，它的长度为 3

示例 3：
输入：text1 = "abc", text2 = "def"
输出：0
解释：两个字符串没有公共子序列，返回 0

提示：
1 <= text1.length, text2.length <= 1000
text1 和 text2 仅由小写英文字符组成。

注意：本题与主站 1143 题相同： https://leetcode-cn.com/problems/longest-common-subsequence/

*/

// 备忘录
class Solution1 {
public:
	int longestCommonSubsequence(string text1, string text2) {
		int len1 = text1.size(), len2 = text2.size();
		vector<vector<int>> memo(len1 + 1, vector<int>(len2 + 1, -1));
		return helper(text1, text2, len1, len2, memo);
	}

private:
	int helper(string &s1, string &s2, int m, int n,
		       vector<vector<int>> &memo) {
		if (m == 0 || n == 0) return 0;
		if (memo[m][n] != -1) return memo[m][n];
		if (s1[m - 1] == s2[n - 1]) memo[m][n] = 1 + helper(s1, s2, m - 1, n - 1, memo);
		else memo[m][n] = max(helper(s1, s2, m - 1, n, memo), helper(s1, s2, m, n - 1, memo));
		return memo[m][n];
	}
};

// 自底而上的动态规划
class Solution2 {
public:
	int longestCommonSubsequence(string text1, string text2) {
		int len1 = text1.size(), len2 = text2.size();
		vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
		for (int i = 1; i <= len1; ++i) {
			for (int j = 1; j <= len2; ++j) {
				if (text1[i - 1] == text2[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
				else dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
			}
		}
		return dp[len1][len2];
	}
};