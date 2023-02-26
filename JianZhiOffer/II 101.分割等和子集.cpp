#include "header.h"

/*

剑指 Offer II 101. 分割等和子集

给你一个只包含正整数的非空数组nums，请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

示例 1：
输入：nums = [1,5,11,5]
输出：true
解释：数组可以分割成 [1, 5, 5] 和 [11]

示例 2：
输入：nums = [1,2,3,5]
输出：false
解释：数组不能分割成两个元素和相等的子集。

提示：
1 <= nums.length <= 200
1 <= nums[i] <= 100

注意：本题与主站 416 题相同： https://leetcode-cn.com/problems/partition-equal-subset-sum/

*/

// 转换为 0-1背包 问题

// 备忘录
class Solution1 {
public:
	bool canPartition(vector<int> &nums) {
		int len = nums.size();
		int sum = accumulate(nums.begin(), nums.end(), 0);
		if (sum & 1) return false;
		vector<vector<char>> memo(len + 1, vector<char>((sum / 2) + 1, -1));
		return helper(nums, len, sum / 2, memo);
	}

private:
	bool helper(vector<int> &nums, int idx, int target, vector<vector<char>> &memo) {
		if (target == 0) return true;
		else if (idx == 0 || target < 0) return false;
		if (memo[idx][target] != -1) return memo[idx][target];
		memo[idx][target] = helper(nums, idx - 1, target - nums[idx - 1], memo) ||
							helper(nums, idx - 1, target, memo);
		return memo[idx][target];
	}
};

// 自底而上的动态规划
class Solution2 {
public:
	bool canPartition(vector<int> &nums) {
		int len = nums.size();
		int sum = accumulate(nums.begin(), nums.end(), 0);
		if (sum & 1) return false;
		int target = sum / 2;
		vector<vector<char>> dp(len + 1, vector<char>(target + 1, false));
		for (int i = 0; i <= len; ++i) {
			for (int j = 0; j <= target; ++j) {
				if (i == 0 && j == 0) dp[i][j] = true;
				else if (i == 0) dp[i][j] = false;
				else if (j == 0) dp[i][j] = true;
				else if (j < nums[i - 1]) dp[i][j] = dp[i - 1][j];
				else dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
			}
		}
		return dp[len][target];
	}
};