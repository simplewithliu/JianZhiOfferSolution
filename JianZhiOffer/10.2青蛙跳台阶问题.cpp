#include "header.h"

/*

一只青蛙一次可以跳上1级台阶，也可以跳上2级台阶。求该青蛙跳上一个 n 级的台阶总共有多少种跳法。
答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。

示例 1：
输入：n = 2
输出：2

示例 2：
输入：n = 7
输出：21

提示：
0 <= n <= 100

注意：本题与主站 70 题相同：https://leetcode-cn.com/problems/climbing-stairs/

*/

//自上而下备忘录
class Solution1 {
public:
	int numWays(int n) 
	{
		vector<int> memo(n + 1, 0);
		return helper(n, memo);
	}
	int helper(int n, vector<int> &memo)
	{
		if (n == 0 || n == 1) return 1;
		if (memo[n] != 0) return memo[n];
		return memo[n] = (helper(n - 1, memo) + helper(n - 2, memo)) % 1000000007;
	}
};

//自底而上动态规划
class Solution2 {
public:
	int numWays(int n)
	{
		if (n == 0 || n == 1) return 1;
		vector<int> dp(n + 1, 0);
		dp[0] = 1, dp[1] = 1;
		for (int i = 2; i <= n; ++i)
		{
			dp[i] = (dp[i - 1] + dp[i - 2]) % 1000000007;
		}
		return dp[n];
	}
};

//优化空间复杂度
class Solution3 {
public:
	int numWays(int n)
	{
		if (n == 0 || n == 1) return 1;
		int pre = 1, cur = 1;
		for (int i = 2; i <= n; ++i)
		{
			int tmp = (pre + cur) % 1000000007;
			pre = cur;
			cur = tmp;
		}
		return cur;
	}
};