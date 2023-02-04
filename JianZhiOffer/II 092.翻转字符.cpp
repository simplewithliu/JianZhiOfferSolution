#include "header.h"

/*

剑指 Offer II 092. 翻转字符

如果一个二进制字符串，是以一些 0（可能没有 0）后面跟着一些 1（也可能没有 1）的形式组成的，那么该字符串是单调递增的
给你一个二进制字符串 s，你可以将任何 0 翻转为 1 或者将 1 翻转为 0
返回使 s 单调递增的最小翻转次数。

示例 1：
输入：s = "00110"
输出：1
解释：翻转最后一位得到 00111

示例 2：
输入：s = "010110"
输出：2
解释：翻转得到 011111，或者是 000111

示例 3：
输入：s = "00011000"
输出：2
解释：翻转得到 00000000

提示：
1 <= s.length <= 10^5
s[i] 为 '0' 或 '1'

注意：本题与主站 926 题相同： https://leetcode-cn.com/problems/flip-string-to-monotone-increasing/


*/

// 备忘录
class Solution1 {
public:
	int minFlipsMonoIncr(string s) {
		int len = s.size();
		vector<vector<int>> memo(len + 1, vector<int>(2, -1));
		return min(helper(s, len, '0', memo), helper(s, len, '1', memo));
	}

private:
	int helper(string &s, int idx, char c, vector<vector<int>> &memo) {
		if (idx == 0) return 0;
		if (memo[idx][c - '0'] != -1) return memo[idx][c - '0'];
		if (c == '0') {
			return memo[idx][c - '0'] = helper(s, idx - 1, '0', memo) + (s[idx - 1] == '1');
		} else {
			return memo[idx][c - '0'] = min(helper(s, idx - 1, '0', memo),
				                            helper(s, idx - 1, '1', memo)) + (s[idx - 1] == '0');
		}
	}
};

// 自底而上的动态规划
class Solution2 {
public:
	int minFlipsMonoIncr(string s) {
		int len = s.size();
		vector<vector<int>> dp(len, vector<int>(2, 0));
		dp[0][0] = s[0] == '1' ? 1 : 0;
		dp[0][1] = s[0] == '0' ? 1 : 0;
		for (int i = 1; i < len; ++i) {
			dp[i][0] = dp[i - 1][0] + (s[i] == '1' ? 1 : 0);
			dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + (s[i] == '0' ? 1 : 0);
		}
		return min(dp[len - 1][0], dp[len - 1][1]);
	}
};

// https://leetcode.cn/problems/flip-string-to-monotone-increasing/solutions/1592230/jiang-zi-fu-chuan-fan-zhuan-dao-dan-diao-stjd 
// @author 力扣官方题解

