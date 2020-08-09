#include "header.h"

/*

数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。你可以假设数组是非空的，并且给定的数组总是存在多数元素。

示例 1:
输入: [1, 2, 3, 2, 2, 2, 5, 4, 2]
输出: 2
   
限制：1 <= 数组长度 <= 50000
注意：本题与主站 169 题相同：https://leetcode-cn.com/problems/majority-element/

*/

//基于快速划分的方法，时间复杂度平均可以达到O(n)
class Solution1 {
public:
	int majorityElement(vector<int> &nums) 
	{
		int len = nums.size();
		int lo = 0, hi = len - 1;
		int mi = len >> 1;
		int index = partition(nums, lo, hi);
		while (index != mi)
		{
			if (index > mi)
			{
				hi = index - 1;
				index = partition(nums, lo, hi);
			}
			else
			{
				lo = index + 1;
				index = partition(nums, lo, hi);
			}
		}
		if (check(nums, nums[mi])) return nums[mi];
		else throw runtime_error("ERROR!");
	}
	int partition(vector<int> &nums, int lo, int hi)
	{
		swap(nums[lo], nums[lo + rand() % (hi - lo + 1)]);
		int pivot = nums[lo];
		while (lo < hi)
		{
			while (lo < hi)
			{
				if (pivot < nums[hi]) --hi;
				else
				{
					nums[lo++] = nums[hi];
					break;
				}
			}
			while (lo < hi)
			{
				if (pivot > nums[lo]) ++lo;
				else
				{
					nums[hi--] = nums[lo];
					break;
				}
			}
		}
		nums[lo] = pivot;
		return lo;
	}
	//如果不保证存在多数元素，需要检查
	bool check(vector<int> &numbers, int num)
	{
		int times = 0;
		for (int i = 0; i < numbers.size(); ++i)
			if (numbers[i] == num) ++times;
		if (times * 2 <= numbers.size())
			return false;
		else
			return true;
	}
};

//基于数组特点的灵活方法
class Solution2 {
public:
	int majorityElement(vector<int> &nums)
	{
		if (nums.empty()) return 0;
		int cur = nums[0], times = 1;
		int len = nums.size();
		for (int i = 1; i < len; ++i)
		{
			if (times == 0)
			{
				cur = nums[i];
				times = 1;
			}
			else if (nums[i] == cur) ++times;
			else --times;
		}
		times = 0;
		for (int n : nums) if (n == cur) ++times;
		if (times > len / 2) return cur;
		else throw runtime_error("ERROR!");
	}
};