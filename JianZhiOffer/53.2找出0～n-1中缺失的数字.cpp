#include "header.h"

/*

一个长度为n-1的递增排序数组中的所有数字都是唯一的，并且每个数字都在范围0～n-1之内。
在范围0～n-1内的n个数字中有且只有一个数字不在该数组中，请找出这个数字。

示例 1:
输入: [0,1,3]
输出: 2

示例 2:
输入: [0,1,2,3,4,5,6,7,9]
输出: 8
  
限制：1 <= 数组长度 <= 10000

*/

class Solution {
public:
	int missingNumber(vector<int> &nums) 
	{
		int len = nums.size();
		int lo = 0, hi = len;
		while (lo < hi)
		{
			int mi = lo + ((hi - lo) >> 1);
			nums[mi] == mi ? lo = mi + 1 : hi = mi;
		}
		return lo;
	}
};
//https://leetcode-cn.com/problems/que-shi-de-shu-zi-lcof/solution/c-onolgnfang-fa-jie-da-by-yizhe-shi/