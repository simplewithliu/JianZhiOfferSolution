#include "header.h"

/*

把n个骰子扔在地上，所有骰子朝上一面的点数之和为s。输入n，打印出s的所有可能的值出现的概率。
你需要用一个浮点数数组返回答案，其中第 i 个元素代表这 n 个骰子所能掷出的点数集合中第 i 小的那个的概率。

示例 1:
输入: 1
输出: [0.16667,0.16667,0.16667,0.16667,0.16667,0.16667]
  
示例 2:
输入: 2
输出: [0.02778,0.05556,0.08333,0.11111,0.13889,0.16667,0.13889,0.11111,0.08333,0.05556,0.02778]
   
限制：1 <= n <= 11

*/

//备忘录
class Solution1 {
public:
	vector<double> twoSum(int n)
	{
		vector<double> res;
		vector<vector<int>> memo(n + 1, vector<int>(6 * n + 1, 0));
		int all = pow(6, n);
		for (int i = n; i <= 6 * n; ++i)
		{
			res.push_back(getCount(n, i, memo) * 1.0 / all);
		}
		return res;
	}
	int getCount(int n, int curSum, vector<vector<int>> &memo)
	{
		if (curSum < n) return 0;
		if (n == 1)
		{
			if (curSum <= 6) return 1;
			else return 0;
		}
		if (memo[n][curSum]) return memo[n][curSum];
		int sum = 0;
		for (int cur = 1; cur <= 6; ++cur)
		{
			sum += getCount(n - 1, curSum - cur, memo);
		}
		return memo[n][curSum] = sum;
	}
};
//getCount(1,?) = 1 ：当仅有一个骰子时，每个点数和出现的次数都是 1
//循环内cur变量表示最后一个骰子当前的点数

//自底而上动态规划
class Solution2 {
public:
	vector<double> twoSum(int n) 
	{
		vector<vector<int>> dp(n + 1, vector<int>(6 * n + 1, 0));
		for (int j = 1; j <= 6; ++j) dp[1][j] = 1;
		for (int i = 2; i <= n; ++i)
		{
			for (int j = i; j <= 6 * i; ++j)
			{
				for (int cur = 1; cur <= 6; ++cur)
				{
					if (j - cur <= 0) break;
					dp[i][j] += dp[i - 1][j - cur];
				}
			}
		}
		int all = pow(6, n);
		vector<double> res;
		for (int j = n; j <= 6 * n; ++j)
		{
			res.push_back(dp[n][j] * 1.0 / all);
		}
		return res;
	}
};
//https://leetcode-cn.com/problems/nge-tou-zi-de-dian-shu-lcof/solution/nge-tou-zi-de-dian-shu-dong-tai-gui-hua-ji-qi-yo-3/

//优化为1维数组
class Solution3 {
public:
	vector<double> twoSum(int n)
	{
		vector<int> dp(6 * n + 1, 0);
		for (int j = 1; j <= 6; ++j) dp[j] = 1;
		for (int i = 2; i <= n; ++i)
		{
			for (int j = 6 * i; j >= i; --j)
			{
				dp[j] = 0;
				for (int cur = 1; cur <= 6; ++cur)
				{
					if (j - cur < i - 1) break;
					dp[j] += dp[j - cur];
				}
			}
		}
		int all = pow(6, n);
		vector<double> res;
		for (int j = n; j <= 6 * n; ++j)
		{
			res.push_back(dp[j] * 1.0 / all);
		}
		return res;
	}
};
//https://leetcode-cn.com/problems/nge-tou-zi-de-dian-shu-lcof/solution/nge-tou-zi-de-dian-shu-dong-tai-gui-hua-ji-qi-yo-3/