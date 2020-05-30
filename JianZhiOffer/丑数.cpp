#include "header.h"

/*

把只包含质因子2、3和5的数称作丑数（Ugly Number）。
例如6、8都是丑数，但14不是，因为它包含质因子7。 
习惯上我们把1当做是第一个丑数。求按从小到大的顺序的第N个丑数。

*/

class Solution {
public:
	int GetUglyNumber_Solution(int index)
	{
		if (index == 0) return 0;
		vector<int> ugly(index, 0);
		ugly[0] = 1;
		int m2 = 0, m3 = 0, m5 = 0;
		for (int i = 1; i < index; ++i)
		{
			ugly[i] = minOfnum(ugly[m2] * 2, ugly[m3] * 3, ugly[m5] * 5);
			while (ugly[m2] * 2 <= ugly[i])
				++m2;
			while (ugly[m3] * 3 <= ugly[i])
				++m3;
			while (ugly[m5] * 5 <= ugly[i])
				++m5;
		}
		return ugly[index - 1];
	}
	int minOfnum(int a, int b, int c)
	{
		int minnum = a < b ? a : b;
		minnum = minnum < c ? minnum : c;
		return minnum;
	}
};