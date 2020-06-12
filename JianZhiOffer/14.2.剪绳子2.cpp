#include "header.h"

/*

给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），每段绳子的长度记为 k[0],k[1]...k[m] 。
请问 k[0]*k[1]*...*k[m] 可能的最大乘积是多少？例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。

答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。

示例 1：
输入: 2
输出: 1
解释: 2 = 1 + 1, 1 × 1 = 1

示例 2:
输入: 10
输出: 36
解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36
  
提示：
2 <= n <= 1000

*/

//快速幂求余、大数问题
class Solution {
public:
	long long quickpow(int x, int a)
	{
		long long res = 1;
		long long tmp = x;
		while (a != 0)
		{
			if (a & 1)
			{
				res *= tmp;
				res %= 1000000007;
			}
			tmp *= tmp;
			tmp %= 1000000007;
			a /= 2;
		}
		return res;
	}
	int cuttingRope(int n) 
	{
		if (n < 4) return n - 1;
		int a = n / 3, b = n % 3;
		if (b == 0) return (int)(quickpow(3, a) % 1000000007);
		if (b == 1) return (int)(quickpow(3, a - 1) * 4 % 1000000007);
		if (b == 2) return (int)(quickpow(3, a) * 2 % 1000000007);
		return 0;
	}
};
//https://leetcode-cn.com/problems/jian-sheng-zi-ii-lcof/solution/mian-shi-ti-14-ii-jian-sheng-zi-iitan-xin-er-fen-f/