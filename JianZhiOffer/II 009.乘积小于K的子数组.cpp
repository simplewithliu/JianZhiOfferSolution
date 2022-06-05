#include "header.h"

/*

给定一个正整数数组nums和整数k，请找出该数组内乘积严格小于k的连续的子数组的个数。

示例 1:
输入: nums = [10,5,2,6], k = 100
输出: 8
解释: 8 个乘积小于 100 的子数组分别为: [10], [5], [2], [6], [10,5], [5,2], [2,6], [5,2,6]。
需要注意的是 [10,5,2] 并不是乘积小于100的子数组。

示例 2:
输入: nums = [1,2,3], k = 0
输出: 0

提示: 
1 <= nums.length <= 3 * 10^4
1 <= nums[i] <= 1000
0 <= k <= 10^6

注意：本题与主站 713 题相同：https://leetcode-cn.com/problems/subarray-product-less-than-k/ 

*/

// 暴力法（超时）
class Solution1 {
public:
	int numSubarrayProductLessThanK(vector<int> &nums, int k) {
		if (k <= 1) return 0;
		int len = nums.size();
		int res = 0;
		for (int i = 0; i < len; ++i) {
			int j = i, product = 1;
			while (j < len && product < k) {
				product *= nums[j];
				++j;
			}
			res += product < k ? j - i : j - i - 1;
		}
		return res;
	}
};

// 对数前缀和 + 二分
class Solution2 {
public:
	int numSubarrayProductLessThanK(vector<int> &nums, int k) {
		if (k <= 1) return 0;
		int len = nums.size();
		double target = log(k);
		vector<double> sums(len + 1, 0);
		for (int i = 1; i <= len; ++i) sums[i] = sums[i - 1] + log(nums[i - 1]);
		int res = 0;
		for (int i = 1; i <= len; ++i) {
			double tar = sums[i - 1] + target;
			int up_bound = upperBound(sums, i, len, tar);
			if (up_bound != -1) res += up_bound - i + 1;
		}
		return res;
	}

private:
	int upperBound(vector<double> &nums, int lo, int hi, double tar) {
		while (lo < hi) {
			int mi = lo + (hi - lo + 1) / 2;
			if (nums[mi] < tar) lo = mi;
			else hi = mi - 1;
		}
		return nums[lo] < tar ? lo : -1;
	}
};

// 双指针
class Solution3 {
public:
	int numSubarrayProductLessThanK(vector<int> &nums, int k) {
		if (k <= 1) return 0;
		int len = nums.size();
		int product = 1;
		int start = 0, end = 0;
		int res = 0;
		while (end < len) {
			product *= nums[end];
			while (start <= end && product >= k) {
				product /= nums[start];
				++start;
			}
			res += end - start + 1;
			++end;
		}
		return res;
	}
};
