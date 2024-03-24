#include "header.h"

/*

LCR 104. 组合总和 Ⅳ

给你一个由 不同 整数组成的数组 nums，和一个目标整数 target
请你从 nums 中找出并返回总和为 target 的元素组合的个数
题目数据保证答案符合 32 位整数范围

示例 1：
输入：nums = [1,2,3], target = 4
输出：7
解释：
所有可能的组合为：
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)
请注意，顺序不同的序列被视作不同的组合

示例 2：
输入：nums = [9], target = 3
输出：0

提示：
1 <= nums.length <= 200
1 <= nums[i] <= 1000
nums 中的所有元素 互不相同
1 <= target <= 1000

进阶：如果给定的数组中含有负数会发生什么？问题会产生何种变化？如果允许负数出现，需要向题目中添加哪些限制条件？

注意：本题与主站 377 题相同：https://leetcode-cn.com/problems/combination-sum-iv/

*/

class Solution1 {
private:
	vector<int> memo;

public:
	int combinationSum4(vector<int> &nums, int target) {
		memo.resize(target + 1, -1);
		return helper(nums, target);
	}
	int helper(const vector<int> &nums, int target) {
		if (target < 0) return 0;
		if (target == 0) return 1;
		if (memo[target] != -1) return memo[target];
		int res = 0;
		for (int i = 0; i < nums.size(); ++i) {
			res += helper(nums, target - nums[i]);
		}
		return memo[target] = res;
	}
};

class Solution2 {
public:
	int combinationSum4(vector<int> &nums, int target) {
		vector<int> dp(target + 1, 0);
		dp[0] = 1;
		for (int i = 1; i <= target; ++i) {
			for (const int n : nums) {
				if (i >= n) dp[i] = (dp[i] + (unsigned int)(dp[i - n])) % INT_MAX;
			}
		}
		return dp[target];
	}
};

