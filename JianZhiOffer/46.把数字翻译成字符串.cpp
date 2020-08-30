#include "header.h"
/*

给定一个数字，我们按照如下规则把它翻译为字符串：0 翻译成 “a” ，1 翻译成 “b”，……，11 翻译成 “l”，……，25 翻译成 “z”。一个数字可能有多个翻译。
请编程实现一个函数，用来计算一个数字有多少种不同的翻译方法。

示例 1:
输入: 12258
输出: 5
解释: 12258有5种不同的翻译，分别是"bccfi", "bwfi", "bczi", "mcfi"和"mzi"
  
提示：0 <= num < 2^31

*/

//普通递归
class Solution1 {
public:
	int translateNum(int num)
	{
		string strNum = to_string(num);
		return helper(strNum, 0);
	}
	int helper(string &strNum, int idx)
	{
		int len = strNum.size();
		if (idx >= len - 1) return 1;
		string temp = strNum.substr(idx, 2);
		if (stoi(temp) >= 10 && stoi(temp) <= 25) return helper(strNum, idx + 1) + helper(strNum, idx + 2);
		else return helper(strNum, idx + 1);
	}
};

//备忘录
class Solution2 {
public:
	int translateNum(int num)
	{
		string strNum = to_string(num);
		int len = strNum.size();
		vector<int> memo(len, 0);
		return helper(strNum, 0, memo);
	}
	int helper(string &strNum, int idx, vector<int> &memo)
	{
		int len = strNum.size();
		if (idx >= len - 1) return 1;
		if (memo[idx] != 0) return memo[idx];
		string temp = strNum.substr(idx, 2);
		if (stoi(temp) >= 10 && stoi(temp) <= 25) memo[idx] = helper(strNum, idx + 1, memo) + helper(strNum, idx + 2, memo);
		else memo[idx] = helper(strNum, idx + 1, memo);
		return memo[idx];
	}
};

//自底而上的动态规划
class Solution3 {
public:
	int translateNum(int num)
	{
		string strNum = to_string(num);
		int len = strNum.size();
		vector<int> dp(len + 1, 0);
		dp[0] = 1;
		dp[1] = 1;
		for (int i = 2; i <= len; ++i)
		{
			int temp = stoi(strNum.substr(i - 2, 2));
			if (temp >= 10 && temp <= 25) dp[i] = dp[i - 1] + dp[i - 2];
			else dp[i] = dp[i - 1];
		}
		return dp[len];
	}
};

//优化空间复杂度
class Solution4 {
public:
	int translateNum(int num)
	{
		string strNum = to_string(num);
		int len = strNum.size();
		int cur = 1;
		int prev = 1;
		for (int i = 2; i <= len; ++i)
		{
			int temp = stoi(strNum.substr(i - 2, 2));
			if (temp >= 10 && temp <= 25)
			{
				int m = cur;
				cur = prev + cur;
				prev = m;
			}
			else
			{
				prev = cur;
			}
		}
		return cur;
	}
};