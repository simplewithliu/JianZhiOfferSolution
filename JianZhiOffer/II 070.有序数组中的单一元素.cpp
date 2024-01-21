#include "header.h"

/*

LCR 070. 有序数组中的单一元素

给你一个仅由整数组成的有序数组，其中每个元素都会出现两次，唯有一个数只会出现一次
请你找出并返回只出现一次的那个数

你设计的解决方案必须满足 O(log n) 时间复杂度和 O(1) 空间复杂度

示例 1:
输入: nums = [1,1,2,3,3,4,4,8,8]
输出: 2

示例 2:
输入: nums =  [3,3,7,7,10,11,11]
输出: 10

提示:
1 <= nums.length <= 10^5
0 <= nums[i] <= 10^5

注意：本题与主站 540 题相同：https://leetcode-cn.com/problems/single-element-in-a-sorted-array/

*/

class Solution1 {
public:
	int singleNonDuplicate(vector<int> &nums) {
		int len = nums.size();
		int lo = 0, hi = len - 1;
		while (lo < hi) {
			int mi = lo + (hi - lo) / 2;
			if (mi & 1) {
				if (mi - 1 >= 0 && nums[mi - 1] == nums[mi]) lo = mi + 1;
				else hi = mi;
			} else {
				if (mi + 1 < len && nums[mi] == nums[mi + 1]) lo = mi + 1;
				else hi = mi;
			}
		}
		return nums[lo];
	}
};


class Solution2 {
public:
	int singleNonDuplicate(vector<int> &nums) {
		int len = nums.size();
		int lo = 0, hi = len - 1;
		while (lo < hi) {
			int mi = lo + (hi - lo) / 2;
			nums[mi] == nums[mi ^ 1] ? lo = mi + 1 : hi = mi;
		}
		return nums[lo];
	}
};

