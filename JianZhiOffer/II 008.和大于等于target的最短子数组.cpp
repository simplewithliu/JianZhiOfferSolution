#include "header.h"

/*

给定一个含有 n 个正整数的数组和一个正整数 target 。
找出该数组中满足其和 ≥ target 的长度最小的连续子数组 [nums_l, nums_l+1, ..., nums_r-1, nums_r] ，并返回其长度。如果不存在符合条件的子数组，返回 0 。

示例 1：
输入：target = 7, nums = [2,3,1,2,4,3]
输出：2
解释：子数组 [4,3] 是该条件下的长度最小的子数组。

示例 2：
输入：target = 4, nums = [1,4,4]
输出：1

示例 3：
输入：target = 11, nums = [1,1,1,1,1,1,1,1]
输出：0
  
提示：
1 <= target <= 10^9
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^5
   
进阶：如果你已经实现 O(n) 时间复杂度的解法, 请尝试设计一个O(nlog(n))时间复杂度的解法。

注意：本题与主站 209 题相同：https://leetcode-cn.com/problems/minimum-size-subarray-sum/

*/

// 暴力搜索 O(n ^ 2)
class Solution1 {
public:
	int minSubArrayLen(int target, vector<int> &nums) {
		int len = nums.size();
		int res = INT_MAX;
		for (int i = 0; i < len; ++i) {
			int sum = 0;
			for (int j = i; j < len; ++j) {
				sum += nums[j];
				if (sum >= target) {
					res = min(res, j - i + 1);
					break;
				}
			}
		}
		return res == INT_MAX ? 0 : res;
	}
};

// 前缀和 + 二分 O(nlogn)
class Solution2 {
public:
	int minSubArrayLen(int target, vector<int> &nums) {
		int len = nums.size();
		vector<int> sums(len + 1, 0);
		int res = INT_MAX;
		for (int i = 1; i <= len; ++i) sums[i] = sums[i - 1] + nums[i - 1];
		for (int i = 1; i <= len; ++i) {
			int tar = sums[i - 1] + target;
			int lo_bound = lowerBound(sums, i, len, tar);
			if (lo_bound != -1) res = min(res, lo_bound - i + 1);
		}
		return res == INT_MAX ? 0 : res;
	}

private:
	int lowerBound(vector<int> &nums, int lo, int hi, int tar) {
		while (lo < hi) {
			int mi = lo + (hi - lo) / 2;
			if (nums[mi] < tar) lo = mi + 1;
			else hi = mi;
		}
		return nums[lo] >= tar ? lo : -1;
	}
};
/*
* https://leetcode.cn/problems/minimum-size-subarray-sum/solution/chang-du-zui-xiao-de-zi-shu-zu-by-leetcode-solutio/
* @author LeetCode官方题解
*/

// 双指针 O(n)
class Solution3 {
public:
	int minSubArrayLen(int target, vector<int> &nums) {
		int len = nums.size();
		int res = INT_MAX;
		int start = 0, end = 0;
		int sum = 0;
		while (end < len) {
			sum += nums[end];
			while (sum >= target) {
				res = min(res, end - start + 1);
				sum -= nums[start];
				++start;
			}
			++end;
		}
		return res == INT_MAX ? 0 : res;
	}
};
