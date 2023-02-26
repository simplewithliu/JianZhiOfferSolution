#include "header.h"

/*

剑指 Offer II 102. 加减的目标值

给你一个整数数组 nums 和一个整数 target，向数组中的每个整数前添加 '+' 或 '-' ，然后串联起所有整数，可以构造一个表达式
例如，nums = [2, 1] ，可以在 2 之前添加 '+' ，在 1 之前添加 '-' ，然后串联起来得到表达式 "+2-1"
返回可以通过上述方法构造的、运算结果等于 target 的不同 表达式 的数目

示例 1：
输入：nums = [1,1,1,1,1], target = 3
输出：5
解释：一共有 5 种方法让最终目标和为 3 。
-1 + 1 + 1 + 1 + 1 = 3
+1 - 1 + 1 + 1 + 1 = 3
+1 + 1 - 1 + 1 + 1 = 3
+1 + 1 + 1 - 1 + 1 = 3
+1 + 1 + 1 + 1 - 1 = 3

示例 2：
输入：nums = [1], target = 1
输出：1

提示：
1 <= nums.length <= 20
0 <= nums[i] <= 1000
0 <= sum(nums[i]) <= 1000
-1000 <= target <= 1000

注意：本题与主站 494 题相同： https://leetcode-cn.com/problems/target-sum/

*/

// 转换为 0-1背包 问题

// 备忘录
class Solution1 {
public:
	int findTargetSumWays(vector<int> &nums, int target) {
		int sum = accumulate(nums.begin(), nums.end(), 0);
		if (sum < abs(target)) return 0;
		if ((sum - target) & 1) return 0;
		int len = nums.size(), neg = (sum - target) / 2;
		vector<vector<int>> memo(len + 1, vector<int>(neg + 1, -1));
		return helper(nums, len, neg, memo);
	}

private:
	int helper(vector<int> &nums, int idx, int target, vector<vector<int>> &memo) {
		if (idx == 0) return target == 0 ? 1 : 0;
		if (target < 0) return 0;
		if (memo[idx][target] != -1) return memo[idx][target];
		memo[idx][target] = helper(nums, idx - 1, target, memo) +
							helper(nums, idx - 1, target - nums[idx - 1], memo);
		return memo[idx][target];
	}
};


// 自底而上的动态规划
class Solution2 {
public:
	int findTargetSumWays(vector<int> &nums, int target) {
		int sum = accumulate(nums.begin(), nums.end(), 0);
		if (sum < abs(target)) return 0;
		if ((sum - target) & 1) return 0;
		int len = nums.size(), neg = (sum - target) / 2;
		vector<vector<int>> dp(len + 1, vector<int>(neg + 1, -1));
		for (int i = 0; i <= len; ++i) {
			for (int j = 0; j <= neg; ++j) {
				if (i == 0 && j == 0) dp[i][j] = 1;
				else if (i == 0) dp[i][j] = 0;
				else if (j < nums[i - 1]) dp[i][j] = dp[i - 1][j];
				else dp[i][j] = dp[i - 1][j] + dp[i - 1][j - nums[i - 1]];
			}
		}
		return dp[len][neg];
	}
};

// https://leetcode.cn/problems/target-sum/solutions/816361/mu-biao-he-by-leetcode-solution-o0cp/
// @author LeetCode官方题解

// https://leetcode.cn/problems/target-sum/solutions/816711/gong-shui-san-xie-yi-ti-si-jie-dfs-ji-yi-et5b/comments/976370
// @author https://leetcode.cn/u/seven-w/