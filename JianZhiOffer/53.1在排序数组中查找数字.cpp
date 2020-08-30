#include "header.h"

/*

统计一个数字在排序数组中出现的次数。

示例 1:
输入: nums = [5,7,7,8,8,10], target = 8
输出: 2

示例 2:
输入: nums = [5,7,7,8,8,10], target = 6
输出: 0

限制：0 <= 数组长度 <= 50000
注意：本题与主站 34 题相同（仅返回值不同）：https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/

*/

class Solution {
public:
	int search(vector<int> &nums, int target) 
	{
		if (nums.empty()) return 0;
		int first = lowerBound(nums, target);
		if (first == -1) return 0;
		int second = upBound(nums, target);
		return second - first + 1;
	}
	//得到相同目标元素最左边一个
	int lowerBound(vector<int> &nums, int target)
	{
		int len = nums.size();
		int lo = 0, hi = len - 1;
		while (lo < hi)
		{
			int mi = lo + ((hi - lo) >> 1);
			(nums[mi] < target) ? lo = mi + 1 : hi = mi;
		}
		return nums[lo] == target ? lo : -1;
	}
	//得到相同目标元素最右边一个
	int upBound(vector<int> &nums, int target)
	{
		int len = nums.size();
		int lo = 0, hi = len - 1;
		while (lo < hi)
		{
			int mi = lo + ((hi - lo + 1) >> 1);
			(nums[mi] > target) ? hi = mi - 1 : lo = mi;
		}
		return nums[lo] == target ? lo : -1;
	}
};