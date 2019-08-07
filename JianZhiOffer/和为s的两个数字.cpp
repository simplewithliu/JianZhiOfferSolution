#include "header.h"

/*

输入一个递增排序的数组和一个数字S，在数组中查找两个数，
使得他们的和正好是S，如果有多对数字的和等于S，输出两个数的乘积最小的。

*/

class Solution {
public:
	vector<int> FindNumbersWithSum(vector<int> array, int sum)
	{
		int len = array.size();
		if (len < 2) return{};
		vector<int> res;
		int ahead = 0, behind = len - 1;
		while (ahead < behind)
		{
			int temp = array[ahead] + array[behind];
			if (temp == sum)
			{
				res.push_back(array[ahead]);
				res.push_back(array[behind]);
				break;
			}
			else if (temp < sum)
			{
				++ahead;
			}
			else
			{
				--behind;
			}
		}
		return res;
	}
};