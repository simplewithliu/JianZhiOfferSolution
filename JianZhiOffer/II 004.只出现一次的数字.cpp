#include "header.h"

/*

给你一个整数数组 nums，除某个元素仅出现一次外，其余每个元素都恰出现三次。请你找出并返回那个只出现了一次的元素。

示例 1：
输入：nums = [2, 2, 3, 2]
输出：3

示例 2：
输入：nums = [0, 1, 0, 1, 0, 1, 100]
输出：100

提示：
1 <= nums.length <= 3 * 10^4
- 2^31 <= nums[i] <= 2^31 - 1
nums中，除某个元素仅出现一次外，其余每个元素都恰出现三次

进阶：你的算法应该具有线性时间复杂度。你可以不使用额外空间来实现吗？

注意：本题与主站 137 题相同：https://leetcode-cn.com/problems/single-number-ii/

*/



// 位运算
class Solution1 {
public:
	int singleNumber(vector<int> &nums) {
		int res = 0;
		for (int i = 0; i < 32; ++i) {
			int sum = 0;
			for (auto n : nums) {
				if ((n >> i) & 1) ++sum;
			}
			res |= (sum % 3) << i;
		}
		return res;
	}
};

// 状态机（技巧性）
class Solution2 {
public:
	int singleNumber(vector<int> &nums) {
		int one = 0, two = 0;
		for (auto n : nums) {
			one = one ^ n & ~two;
			two = two ^ n & ~one;
		}
		return one;
	}
};
/*
* https://leetcode.cn/problems/single-number-ii/solution/single-number-ii-mo-ni-san-jin-zhi-fa-by-jin407891/
* @author https://leetcode.cn/u/jyd/
*/
