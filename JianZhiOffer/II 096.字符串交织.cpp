#include "header.h"

/*

剑指 Offer II 096. 字符串交织

给定三个字符串 s1、s2、s3，请你帮忙验证 s3 是否是由 s1 和 s2 交错组成的。

两个字符串 s 和 t 交错的定义与过程如下，其中每个字符串都会被分割成若干非空子字符串：
s = s1 + s2 + ... + sn
t = t1 + t2 + ... + tm
|n - m| <= 1
交错 是 s1 + t1 + s2 + t2 + s3 + t3 + ... 或者 t1 + s1 + t2 + s2 + t3 + s3 + ...
注意：a + b 意味着字符串 a 和 b 连接。

示例 1：
输入：s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
输出：true

示例 2：
输入：s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
输出：false

示例 3：
输入：s1 = "", s2 = "", s3 = ""
输出：true

提示：
0 <= s1.length, s2.length <= 100
0 <= s3.length <= 200
s1、s2、和 s3 都由小写英文字母组成

进阶：您能否仅使用 O(s2.length) 额外的内存空间来解决它?

注意：本题与主站 97 题相同： https://leetcode-cn.com/problems/interleaving-string/

*/


// 备忘录
class Solution1 {
public:
	bool isInterleave(string s1, string s2, string s3) {
		int len1 = s1.size(), len2 = s2.size(), len3 = s3.size();
		if (len1 + len2 != len3) return false;
		vector<vector<char>> memo(len1 + 1, vector<char>(len2 + 1, -1));
		return helper(s1, len1, s2, len2, s3, len3, memo);
	}

private:
	bool helper(string &s1, int i, string &s2, int j, string &s3, int k,
		        vector<vector<char>> &memo) {
		if (i == 0) return s2.substr(0, j) == s3.substr(0, k);
		if (j == 0) return s1.substr(0, i) == s3.substr(0, k);
		if (memo[i][j] != -1) return memo[i][j];
		memo[i][j] = (s1[i - 1] == s3[k - 1] && helper(s1, i - 1, s2, j, s3, k - 1, memo)) ||
			         (s2[j - 1] == s3[k - 1] && helper(s1, i, s2, j - 1, s3, k - 1, memo));
		return memo[i][j];
	}
};

// 自底而上的动态规划
class Solution2 {
public:
	bool isInterleave(string s1, string s2, string s3) {
		int len1 = s1.size(), len2 = s2.size(), len3 = s3.size();
		if (len3 != len1 + len2) return false;
		vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, false));
		for (int i = 0; i <= len1; ++i) {
			for (int j = 0; j <= len2; ++j) {
				if (i == 0 && j == 0) dp[i][j] = true;
				else if (i == 0) dp[i][j] = dp[i][j - 1] && s2[j - 1] == s3[i + j - 1];
				else if (j == 0) dp[i][j] = dp[i - 1][j] && s1[i - 1] == s3[i + j - 1];
				else dp[i][j] = (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1]) ||
					            (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
			}
		}
		return dp[len1][len2];
	}
};

// https://leetcode.cn/problems/interleaving-string/solutions/335373/jiao-cuo-zi-fu-chuan-by-leetcode-solution/
// @author 力扣官方题解