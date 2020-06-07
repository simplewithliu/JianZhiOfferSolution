#include "header.h"

/*

给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），每段绳子的长度记为 k[0],k[1]...k[m-1] 。
请问 k[0]*k[1]*...*k[m-1] 可能的最大乘积是多少？例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。

示例 1：
输入: 2
输出: 1
解释: 2 = 1 + 1, 1 × 1 = 1

示例 2:
输入: 10
输出: 36
解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36

提示：
2 <= n <= 58
注意：本题与主站 343 题相同：https://leetcode-cn.com/problems/integer-break/

*/

//备忘录算法
class Solution1 {
public:
	int cuttingRope(int n) 
	{
		if (n == 0 || n == 1) return n;
		vector<int> memo(n + 1);
		return helper(n, memo);
	}
	int helper(int n, vector<int> &memo)
	{
		if (n == 0 || n == 1) return n;
		if (memo[n] != 0) return memo[n];
		int res = 0;
		for (int i = 1; i < n; ++i)
		{
			res = max(res, max(i * (n - i), i * helper(n - i, memo)));
		}
		return memo[n] = res;
	}
};

//自底而上的动态规划
class Solution2 {
public:
	int cuttingRope(int n) 
	{
		if (n == 0 || n == 1) return n;
		vector<int> dp(n + 1);
		dp[1] = 1;
		for (int i = 2; i <= n; ++i)
		{
			for (int j = 1; j < i; ++j)
			{
				dp[i] = max(dp[i], max(j * (i - j), j * dp[i - j]));
			}
		}
		return dp[n];
	}
};

//动态规划优化
//最终结果由1,2,3组成，根据这个规律优化复杂度
class Solution3 {
public:
	int cuttingRope(int n)
	{
		if (n == 0 || n == 1) return n;
		vector<int> dp(3);
		dp[0] = 0, dp[1] = 1, dp[2] = 1;
		for (int i = 3; i <= n; ++i)
		{
			int t1 = 1 * max(dp[(i - 1) % 3], i - 1);
			int t2 = 2 * max(dp[(i - 2) % 3], i - 2);
			int t3 = 3 * max(dp[(i - 3) % 3], i - 3);
			dp[i % 3] = max(t1, max(t2, t3));
		}
		return dp[n % 3];
	}
};
//https://leetcode-cn.com/problems/jian-sheng-zi-lcof/solution/mian-shi-ti-14-i-jian-sheng-zi-tan-xin-si-xiang-by/