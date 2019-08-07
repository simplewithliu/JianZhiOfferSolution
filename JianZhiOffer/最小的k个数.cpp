#include "header.h"

/*

输入n个整数，找出其中最小的K个数。
例如输入4,5,1,6,2,7,3,8这8个数字，则最小的4个数字是1,2,3,4,。

*/

class Solution {
public:
	vector<int> GetLeastNumbers_Solution(vector<int> input, int k)
	{
		int len = input.size();
		if (k <= 0) return{};
		if (k > len) return{};
		if (k == len) return input;
		int start = 0, end = len - 1;
		int index = partition(input, start, end);
		while (index != k - 1)
		{
			if (index > k - 1)
			{
				end = index - 1;
				index = partition(input, start, end);
			}
			else
			{
				start = index + 1;
				index = partition(input, index + 1, len - 1);
			}
		}
		vector<int> res;
		for (int i = 0; i < k; ++i)
		{
			res.push_back(input[i]);
		}
		return res;
	}
	int partition(vector<int> &data, int lo, int hi)
	{
		swap(data[lo], data[lo + rand() % (hi - lo + 1)]);
		int pivot = data[lo];
		while (lo < hi)
		{
			while (lo < hi)
			{
				if (pivot < data[hi])
					--hi;
				else
				{
					data[lo++] = data[hi];
					break;
				}
			}
			while (lo < hi)
			{
				if (pivot>data[lo])
					++lo;
				else
				{
					data[hi--] = data[lo];
					break;
				}
			}
		}
		data[lo] = pivot;
		return lo;
	}
};

