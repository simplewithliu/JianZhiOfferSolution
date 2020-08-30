#include "header.h"

/*

我们把只包含质因子 2、3 和 5 的数称作丑数（Ugly Number）。求按从小到大的顺序的第 n 个丑数。

示例:
输入: n = 10
输出: 12
解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 是前 10 个丑数。

说明:  
1 是丑数。
n 不超过1690。

注意：本题与主站 264 题相同：https://leetcode-cn.com/problems/ugly-number-ii/

*/

class Solution {
public:
	int nthUglyNumber(int n)
	{
		if (n == 0) return 0;
		vector<int> ugly(n, 0);
		ugly[0] = 1;
		int m2 = 0, m3 = 0, m5 = 0;
		for (int i = 1; i < n; ++i)
		{
			int u2 = ugly[m2] * 2, u3 = ugly[m3] * 3, u5 = ugly[m5] * 5;
			ugly[i] = min(u2, min(u3, u5));
			if (ugly[i] == u2) ++m2;
			if (ugly[i] == u3) ++m3;
			if (ugly[i] == u5) ++m5;
		}
		return ugly[n - 1];
	}
};