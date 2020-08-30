#include "header.h"

/*

我们可以用2*1的小矩形横着或者竖着去覆盖更大的矩形。
请问用n个2*1的小矩形无重叠地覆盖一个2*n的大矩形，总共有多少种方法？

*/

class Solution {
public:
	int rectCover(int number)
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