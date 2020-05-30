#include "header.h"

/*

一只青蛙一次可以跳上1级台阶，也可以跳上2级。
求该青蛙跳上一个n级的台阶总共有多少种跳法（先后次序不同算不同的结果）。

*/

class Solution1 {
public:
	int jumpFloor(int number)
	{
		if (number == 0) return 0;
		if (number == 1) return 1;
		vector<int> dp(number + 1, 0);
		dp[1] = 1;
		dp[2] = 2;
		int num = 3;
		while (num <= number)
		{
			dp[num] = dp[num - 1] + dp[num - 2];
			num += 1;
		}
		return dp[number];
	}
};

/*

一只青蛙一次可以跳上1级台阶，也可以跳上2级……它也可以跳上n级。
求该青蛙跳上一个n级的台阶总共有多少种跳法。

*/

class Solution2 {
public:
	int jumpFloorII(int number)
	{
		if (number == 0) return 0;
		if (number == 1) return 1;
		vector<int> dp(number + 1, 0);
		dp[1] = 1;
		int num = 2;
		while (num <= number)
		{
			for (int i = 1; i < num; ++i)
				dp[num] += dp[i];
			dp[num] += 1;
			num += 1;
		}
		return dp[number];
	}
};