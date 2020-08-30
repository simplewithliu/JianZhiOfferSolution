#include "header.h"

/*

数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组，求出这个数组中的逆序对的总数。

示例 1:
输入: [7,5,6,4]
输出: 5
  
限制：0 <= 数组长度 <= 50000

*/

class Solution {
public:
	int reversePairs(vector<int> &nums) 
	{
		if (nums.empty()) return 0;
		int count = 0;
		int len = nums.size();
		mergeSort(nums, 0, len, count);
		return count;
	}
	int mergeSort(vector<int> &data, int lo, int hi, int &count)
	{
		if (hi - lo < 2) return lo;
		int mi = (lo + hi) >> 1;
		int left = 0, right = 0;
		left = mergeSort(data, lo, mi, count);
		right = mergeSort(data, mi, hi, count);
		while (left >= lo && right >= mi)
		{
			if (data[left] > data[right])
			{
				count += right - mi + 1;
				--left;
			}
			else
			{
				--right;
			}
		}
		merge(data, lo, mi, hi);
		return hi - 1;
	}
	void merge(vector<int> &data, int lo, int mi, int hi)
	{
		int leftNum = mi - lo;
		vector<int> temp(leftNum, 0);
		for (int i = 0, j = lo; i < leftNum; ++i, ++j) temp[i] = data[j];
		int i = 0, j = mi, k = lo;
		while (i < leftNum && j < hi)
		{
			if (temp[i] <= data[j]) data[k++] = temp[i++];
			else data[k++] = data[j++];
		}
		while (i < leftNum) data[k++] = temp[i++];
	}
};