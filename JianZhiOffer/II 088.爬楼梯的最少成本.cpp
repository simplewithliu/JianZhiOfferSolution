#include "header.h"

/*

剑指 Offer II 088. 爬楼梯的最少成本

给你一个整数数组 cost，其中 cost[i] 是从楼梯第 i 个台阶向上爬需要支付的费用。一旦你支付此费用，即可选择向上爬一个或者两个台阶。
你可以选择从下标为 0 或下标为 1 的台阶开始爬楼梯。
请你计算并返回达到楼梯顶部的最低花费。

示例 1：
输入：cost = [10,15,20]
输出：15
解释：你将从下标为 1 的台阶开始。
- 支付 15 ，向上爬两个台阶，到达楼梯顶部。
总花费为 15 。

示例 2：
输入：cost = [1,100,1,1,1,100,1,1,100,1]
输出：6
解释：你将从下标为 0 的台阶开始。
- 支付 1 ，向上爬两个台阶，到达下标为 2 的台阶。
- 支付 1 ，向上爬两个台阶，到达下标为 4 的台阶。
- 支付 1 ，向上爬两个台阶，到达下标为 6 的台阶。
- 支付 1 ，向上爬一个台阶，到达下标为 7 的台阶。
- 支付 1 ，向上爬两个台阶，到达下标为 9 的台阶。
- 支付 1 ，向上爬一个台阶，到达楼梯顶部。
总花费为 6 。

提示：
2 <= cost.length <= 1000
0 <= cost[i] <= 999

注意：本题与主站 746 题相同： https://leetcode-cn.com/problems/min-cost-climbing-stairs/

*/

// 备忘录
class Solution1 {
public:
	int minCostClimbingStairs(vector<int> &cost) {
		int len = cost.size();
		vector<int> memo(len);
		return min(helper(cost, len - 1, memo), helper(cost, len - 2, memo));
	}

private:
	int helper(vector<int> &cost, int n, vector<int> &memo) {
		if (n == 0 || n == 1) return cost[n];
		if (memo[n] != 0) return memo[n];
		return memo[n] = min(helper(cost, n - 1, memo), helper(cost, n - 2, memo)) + cost[n];
	}
};

// 自底而上的动态规划
class Solution2 {
public:
	int minCostClimbingStairs(vector<int> &cost) {
		int len = cost.size();
		vector<int> dp(len);
		dp[0] = cost[0], dp[1] = cost[1];
		for (int i = 2; i < len; ++i) dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];
		return min(dp[len - 1], dp[len - 2]);
	}
};

// 优化空间复杂度
class Solution3 {
public:
	int minCostClimbingStairs(vector<int> &cost) {
		int len = cost.size();
		int first = cost[0];
		int second = cost[1];
		for (int i = 2; i < len; ++i) {
			int cur = min(first, second) + cost[i];
			first = second;
			second = cur;
		}
		return min(first, second);
	}
};