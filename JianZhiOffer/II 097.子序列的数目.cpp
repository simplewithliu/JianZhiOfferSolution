#include "header.h"

/*

剑指 Offer II 097. 子序列的数目

给定一个字符串 s 和一个字符串 t ，计算在 s 的子序列中 t 出现的个数。
字符串的一个子序列是指，通过删除一些（也可以不删除）字符且不干扰剩余字符相对位置所组成的新字符串。（例如，"ACE" 是 "ABCDE" 的一个子序列，而 "AEC" 不是）
题目数据保证答案符合 32 位带符号整数范围。

示例 1：
输入：s = "rabbbit", t = "rabbit"
输出：3
解释：
如下图所示, 有 3 种可以从 s 中得到 "rabbit" 的方案。

示例 2：
输入：s = "babgbag", t = "bag"
输出：5
解释：
如下图所示, 有 5 种可以从 s 中得到 "bag" 的方案。

提示：
0 <= s.length, t.length <= 1000
s 和 t 由英文字母组成

注意：本题与主站 115 题相同： https://leetcode-cn.com/problems/distinct-subsequences/

*/

// 备忘录
class Solution1 {
public:
	int numDistinct(string s, string t) {
		int sLen = s.size(), tLen = t.size();
		vector<vector<int>> memo(sLen + 1, vector<int>(tLen + 1, -1));
		return helper(s, sLen, t, tLen, memo);
	}

private:
	int helper(string &s, int i, string &t, int j, vector<vector<int>> &memo) {
		if (j == 0) return 1;
		if (i == 0) return 0;
		if (memo[i][j] != -1) return memo[i][j];
		int count = 0;
		if (s[i - 1] == t[j - 1]) {
			count = helper(s, i - 1, t, j, memo) + helper(s, i - 1, t, j - 1, memo);
		} else {
			count = helper(s, i - 1, t, j, memo);
		}
		return memo[i][j] = count;
	}
};

// 自底而上的动态规划
class Solution2 {
public:
	int numDistinct(string s, string t) {
		int sLen = s.size(), tLen = t.size();
		vector<vector<unsigned int>> dp(sLen + 1, vector<unsigned int>(tLen + 1));
		for (int i = 0; i <= sLen; ++i) {
			for (int j = 0; j <= tLen; ++j) {
				if (j == 0) {
					dp[i][j] = 1;
				} else if (i == 0) {
					dp[i][j] = 0;
				} else {
					// 这里计算的中间结果可能超过int大小
					// 自底而上计算，子字符串中存在这种情况
					if (s[i - 1] == t[j - 1]) dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
					else dp[i][j] = dp[i - 1][j];
				}
			}
		}
		return dp[sLen][tLen];
	}
};

// https://leetcode.cn/problems/distinct-subsequences/solutions/661537/shou-hua-tu-jie-xiang-jie-liang-chong-ji-4r2y/
// @author https://leetcode.cn/u/xiao_ben_zhu/