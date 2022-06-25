#include "header.h"

/*

给定一个整数数组和一个整数 k ，请找到该数组中和为 k 的连续子数组的个数。

示例 1：
输入:nums = [1,1,1], k = 2
输出: 2
解释: 此题 [1,1] 与 [1,1] 为两种不同的情况

示例 2：
输入:nums = [1,2,3], k = 3
输出: 2

提示:
1 <= nums.length <= 2 * 10^4
-1000 <= nums[i] <= 1000
-10^7 <= k <= 10^7

注意：本题与主站 560 题相同： https://leetcode-cn.com/problems/subarray-sum-equals-k/

*/


// 暴力穷举（超时）
class Solution1 {
public:
	int subarraySum(vector<int> &nums, int k) {
		int count = 0;
		int len = nums.size();
		for (int i = 0; i < len; ++i) {
			int sum = 0;
			for (int j = i; j < len; ++j) {
				sum += nums[j];
				if (sum == k) ++count;
			}
		}
		return count;
	}
};

// 前缀和（超时）
class Solution2 {
public:
	int subarraySum(vector<int> &nums, int k) {
		int count = 0;
		int len = nums.size();
		vector<int> preSum(len + 1);
		for (int i = 1; i <= len; ++i) preSum[i] = preSum[i - 1] + nums[i - 1];
		for (int left = 0; left < len; ++left) {
			for (int right = left + 1; right <= len; ++right) {
				if (preSum[right] - preSum[left] == k) ++count;
			}
		}
		return count;
	}
};

// 前缀和 + 哈希
class Solution3 {
public:
	int subarraySum(vector<int> &nums, int k) {
		// 记录相同前缀和出现的次数
		unordered_map<int, int> preSumFreq;
		preSumFreq[0] = 1;
		int preSum = 0;
		int count = 0;
		for (const auto &num : nums) {
			preSum += num;
			if (preSumFreq.count(preSum - k)) count += preSumFreq[preSum - k];
			++preSumFreq[preSum];
		}
		return count;
	}
};