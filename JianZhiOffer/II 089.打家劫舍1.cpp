#include "header.h"

/*

LCR 089. 打家劫舍

你是一个专业的小偷，计划偷窃沿街的房屋。

每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

给定一个代表每个房屋存放金额的非负整数数组，计算你不触动警报装置的情况下，一夜之内能够偷窃到的最高金额。


示例 1：
输入：[1,2,3,1]
输出：4
解释：偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。
偷窃到的最高金额 = 1 + 3 = 4

示例 2：
输入：[2,7,9,3,1]
输出：12
解释：偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)。
偷窃到的最高金额 = 2 + 9 + 1 = 12

提示：
1 <= nums.length <= 100
0 <= nums[i] <= 400

注意：本题与主站 198 题相同： https://leetcode-cn.com/problems/house-robber/

*/

// 备忘录
class Solution1 {
private:
	vector<int> memo;

public:
	int rob(vector<int> &nums) {
		int len = nums.size();
		memo.resize(len + 1, -1);
		return helper(nums, len);
	}

private:
	int helper(vector<int> &nums, int idx) {
		if (idx <= 0) return 0;
		if (memo[idx] != -1) return memo[idx];
		return memo[idx] = max(helper(nums, idx - 1),
			                   helper(nums, idx - 2) + nums[idx - 1]);
	}
};


// 自底而上的动态规划
class Solution2 {
public:
	int rob(vector<int> &nums) {
		int len = nums.size();
		vector<int> dp(len + 1);
		dp[0] = 0, dp[1] = nums[0];
		for (int i = 2; i <= len; ++i) {
			dp[i] = max(dp[i - 1], dp[i - 2] + nums[i - 1]);
		}
		return dp[len];
	}
};

// 空间优化
class Solution3 {
public:
	int rob(vector<int> &nums) {
		int r0 = 0, r1 = 0;
		for (int num : nums) {
			int new_r = max(r1, r0 + num);
			r0 = r1;
			r1 = new_r;
		}
		return r1;
	}
};
