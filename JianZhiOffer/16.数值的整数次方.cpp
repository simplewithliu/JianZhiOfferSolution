#include "header.h"

/*

实现函数double Power(double base, int exponent)，求base的exponent次方。不得使用库函数，同时不需要考虑大数问题。

示例 1:
输入: 2.00000, 10
输出: 1024.00000
 
示例 2:
输入: 2.10000, 3
输出: 9.26100

示例 3:
输入: 2.00000, -2
输出: 0.25000
解释: 2-2 = 1/22 = 1/4 = 0.25
  
说明:
-100.0 < x < 100.0
n 是 32 位有符号整数，其数值范围是 [−2^31, 2^31 − 1] 。
注意：本题与主站 50 题相同：https://leetcode-cn.com/problems/powx-n/

*/

//二分法快速幂

//迭代
class Solution1 {
public:
	double myPow(double x, int n) 
	{
		if (x == 0) return 0;
		if (n == 0) return 1;
		int exp = n;
		if (n < 0)
		{
			if (n == INT_MIN)
			{
				++exp;
				exp = -exp;
				return 1.0 / (x * helper(x, exp));
			}
			exp = -exp;
		}
		double res = helper(x, exp);
		return n < 0 ? (1.0 / res) : res;
	}
	double helper(double x, int n)
	{
		double res = 1.0;
		while (n)
		{
			if (n & 1) res *= x;
			x *= x;
			n /= 2;
		}
		return res;
	}
};

//递归
class Solution2 {
public:
	double myPow(double x, int n)
	{
		if (x == 0) return 0;
		if (n == 0) return 1;
		int exp = n;
		if (n < 0)
		{
			if (n == INT_MIN)
			{
				++exp;
				exp = -exp;
				return 1.0 / (x * helper(x, exp));
			}
			exp = -exp;
		}
		double res = helper(x, exp);
		return n < 0 ? (1.0 / res) : res;
	}
	double helper(double x, int n)
	{
		if (n == 1) return x;
		double res = helper(x, n / 2);
		res *= res;
		if (n & 1) res *= x;
		return res;
	}
};