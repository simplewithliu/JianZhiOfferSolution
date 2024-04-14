#include "header.h"

/*

LCR 090. 打家劫舍 II

你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。这个地方所有的房屋都 围成一圈，这意味着第一个房屋和最后一个房屋是紧挨着的。

同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

给定一个代表每个房屋存放金额的非负整数数组，计算你在不触动警报装置的情况下，今晚能够偷窃到的最高金额。

示例 1：
输入：nums = [2,3,2]
输出：3
解释：你不能先偷窃 1 号房屋（金额 = 2），然后偷窃 3 号房屋（金额 = 2）, 因为他们是相邻的

示例 2：
输入：nums = [1,2,3,1]
输出：4
解释：你可以先偷窃 1 号房屋（金额 = 1），然后偷窃 3 号房屋（金额 = 3）
偷窃到的最高金额 = 1 + 3 = 4

示例 3：
输入：nums = [1,2,3]
输出：3

提示：
1 <= nums.length <= 100
0 <= nums[i] <= 1000

注意：本题与主站 213 题相同：https://leetcode-cn.com/problems/house-robber-ii/

*/


class Solution1 {
public:
	int rob(vector<int> &nums) {
		int len = nums.size();
		if (len < 2) return nums[0];
		return max(rob1(nums, 1, len - 1), rob1(nums, 2, len));
	}

private:
	// 从第start个房屋开始，到第end个房屋结束
	int rob1(vector<int> &nums, int start, int end) {
		int len = nums.size();
		vector<int> dp(len + 1);
		dp[start - 1] = 0, dp[start] = nums[start - 1];
		for (int i = start + 1; i <= end; ++i) {
			dp[i] = max(dp[i - 1], dp[i - 2] + nums[i - 1]);
		}
		return dp[end];
	}
};


class Solution2 {
public:
	int rob(vector<int> &nums) {
		int len = nums.size();
		if (len < 2) return nums[0];
		return max(rob1(nums, 1, len - 1), rob1(nums, 2, len));
	}

private:
	// 从第start个房屋开始，到第end个房屋结束
	int rob1(vector<int> &nums, int start, int end) {
		int r0 = 0, r1 = nums[start - 1];
		for (int i = start + 1; i <= end; ++i) {
			int new_r = max(r1, r0 + nums[i - 1]);
			r0 = r1;
			r1 = new_r;
		}
		return r1;
	}
};

