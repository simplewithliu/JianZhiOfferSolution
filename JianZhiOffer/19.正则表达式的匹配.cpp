#include "header.h"

/*

请实现一个函数用来匹配包含'.'和'*'的正则表达式。模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次（含0次）。
在本题中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，但与"aa.a"和"ab*a"均不匹配。

示例 1:
输入:
s = "aa"
p = "a"
输出: false
解释: "a" 无法匹配 "aa" 整个字符串。

示例 2:
输入:
s = "aa"
p = "a*"
输出: true
解释: 因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。

示例 3:
输入:
s = "ab"
p = ".*"
输出: true
解释: ".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。

示例 4:
输入:
s = "aab"
p = "c*a*b"
输出: true
解释: 因为 '*' 表示零个或多个，这里 'c' 为 0 个, 'a' 被重复一次。因此可以匹配字符串 "aab"。

示例 5:
输入:
s = "mississippi"
p = "mis*is*p*."
输出: false

s 可能为空，且只包含从 a-z 的小写字母。
p 可能为空，且只包含从 a-z 的小写字母以及字符 . 和 *，无连续的 '*'。
注意：本题与主站 10 题相同：https://leetcode-cn.com/problems/regular-expression-matching/

*/

//备忘录
class Solution1 {
public:
	bool isMatch(string s, string p) 
	{
		int sLen = s.size(), pLen = p.size();
		vector<vector<char>> memo(sLen + 1, vector<char>(pLen + 1, -1));
		return helper(0, s, 0, p, memo);
	}
	bool helper(int i, string &s, int j, string &p, vector<vector<char>> &memo)
	{
		if (memo[i][j] != -1) return memo[i][j];
		int sLen = s.size(), pLen = p.size();
		if (j == pLen) return memo[i][j] = (i == sLen);
		if (j + 1 < pLen && p[j + 1] == '*')
		{
			if (helper(i, s, j + 2, p, memo) || (i < sLen && (p[j] == '.' || s[i] == p[j]) && helper(i + 1, s, j, p, memo))) return memo[i][j] = true;
		}
		else
		{
			if (i < sLen && ((p[j] == '.' || s[i] == p[j]) && helper(i + 1, s, j + 1, p, memo))) return memo[i][j] = true;
		}
		return memo[i][j] = false;
	}
};


//动态规划
class Solution2 {
public:
	bool isMatch(string s, string p)
	{
		int sLen = s.size(), pLen = p.size();
		vector<vector<char>> dp(sLen + 1, vector<char>(pLen + 1, false));
		dp[0][0] = true;
		for (int j = 2; j <= pLen; ++j)
		{
			dp[0][j] = dp[0][j - 2] && p[j - 1] == '*';
		}
		for (int i = 1 ; i <=sLen; ++i)
		{
			for (int j = 1; j <= pLen; ++j)
			{
				if (p[j - 1] == '*')
				{
					dp[i][j] = dp[i][j - 2] || ((s[i - 1] == p[j - 2] || p[j - 2] == '.') && dp[i - 1][j]);
				}
				else
				{
					if (s[i - 1] == p[j - 1] || p[j - 1] == '.') dp[i][j] = dp[i - 1][j - 1];
				}
			}
		}
		return dp[sLen][pLen];
	}
};