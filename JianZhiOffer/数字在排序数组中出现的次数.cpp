#include "header.h"

/*

统计一个数字在排序数组中出现的次数。

*/

class Solution {
public:
	int GetNumberOfK(vector<int> data, int k)
	{
		return bisearch(data, k) - bisearch(data, k - 1);
	}
	int bisearch(vector<int> &data, int k)
	{
		int lo = 0, hi = data.size();
		while (lo < hi)
		{
			int mi = (lo + hi) >> 1;
			(data[mi]>k) ? hi = mi : lo = mi + 1;
		}
		return lo;
	}
};