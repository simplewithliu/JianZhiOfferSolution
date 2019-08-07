#include "header.h"

/*

求出任意非负整数区间中1出现的次数（从1 到 n 中1出现的次数）。
例如，1~13中包含1的数字有1、10、11、12、13因此共出现6次。

*/


class Solution {
public:
	int NumberOf1Between1AndN_Solution(int n)
	{
		int count = 0;
		long long i = 1;
		for (i = 1; i <= n; i *= 10)
		{
			int a = n / i, b = n % i;
			count += (a + 8) / 10 * i + (a % 10 == 1)*(b + 1);
		}
		return count;
	}
};