#include "header.h"

/*

请实现一个函数用来匹配包括'.'和'*'的正则表达式。
模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次（包含0次）。 
在本题中，匹配是指字符串的所有字符匹配整个模式。
例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，但是与"aa.a"和"ab*a"均不匹配。

*/


//递归的方法
class Solution1 {
public:
	bool match(char *str, char *pattern)
	{
		if (!str || !pattern) return false;
		if (*pattern == '\0'&&*str != '\0') return false;
		if (*str == '\0'&&*pattern == '\0') return true;
		if (*(pattern + 1) != '*')
		{
			if (*str == *pattern || (*str != '\0'&&*pattern == '.'))
			{
				return match(++str, ++pattern);
			}
			else
			{
				return false;
			}
		}
		else
		{
			if (*str == *pattern || (*str != '\0'&&*pattern == '.'))
			{
				return match(str, pattern + 2) || match(++str, pattern);
			}
			else
			{
				return match(str, pattern + 2);
			}
		}
	}
};

//动态规划的方法
class Solution2 {
public:
	bool match(char *s, char *p)
	{
		if (!s || !p) return false;
		int sLen = strlen(s), pLen = strlen(p);
		vector<vector<bool>> dp(sLen + 1, vector<bool>(pLen + 1, false));
		dp[0][0] = true;
		for (int j = 1; j < dp[0].size(); ++j)
		{
			if (p[j - 1] == '*')
			{
				if (dp[0][j - 2]) dp[0][j] = true;
			}
		}
		for (int i = 1; i < dp.size(); ++i)
		{
			for (int j = 1; j < dp[0].size(); ++j)
			{
				if (s[i - 1] == p[j - 1] || p[j - 1] == '.')
					dp[i][j] = dp[i - 1][j - 1];
				if (p[j - 1] == '*')
				{
					if (s[i - 1] != p[j - 2] && p[j - 2] != '.')
						dp[i][j] = dp[i][j - 2];
					else
						dp[i][j] = dp[i - 1][j] || dp[i][j - 1] || dp[i][j - 2];
				}
			}
		}
		return dp[sLen][pLen];
	}
};
//https://leetcode.com/problems/regular-expression-matching/discuss/5651/Easy-DP-Java-Solution-with-detailed-Explanation