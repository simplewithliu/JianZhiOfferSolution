#include "header.h"

/*

LCR 103. 零钱兑换

给你一个整数数组 coins，表示不同面额的硬币；以及一个整数 amount，表示总金额。

计算并返回可以凑成总金额所需的 最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回 -1。

你可以认为每种硬币的数量是无限的。

示例 1：
输入：coins = [1, 2, 5], amount = 11
输出：3
解释：11 = 5 + 5 + 1

示例 2：
输入：coins = [2], amount = 3
输出：-1

示例 3：
输入：coins = [1], amount = 0
输出：0

提示：
1 <= coins.length <= 12
1 <= coins[i] <= 2^31 - 1
0 <= amount <= 10^4

注意：本题与主站 322 题相同： https://leetcode-cn.com/problems/coin-change/

*/

// 完全背包变形题
// 备忘录
class Solution1 {
private:
	vector<vector<int>> memo;

public:
	int coinChange(vector<int> &coins, int amount) {
		int len = coins.size();
		memo.resize(len + 1, vector<int>(amount + 1, -1));
		int res = helper(coins, len, amount);
		return res < INT_MAX / 2 ? res : -1;
	}

private:
	int helper(vector<int> &coins, int idx, int remains) {
		if (idx == 0) return remains == 0 ? 0 : INT_MAX / 2;
		if (memo[idx][remains] != -1) return memo[idx][remains];
		int res = 0;
		if (remains < coins[idx - 1]) {
			res = helper(coins, idx - 1, remains);
		} else {
			res = min(helper(coins, idx - 1, remains),
				helper(coins, idx, remains - coins[idx - 1]) + 1);
		}
		return memo[idx][remains] = res;
	}
};


// 自底而上的动态规划
class Solution2 {
public:
	int coinChange(vector<int> &coins, int amount) {
		int len = coins.size();
		vector<vector<int>> dp(len + 1, vector<int>(amount + 1, INT_MAX / 2));
		dp[0][0] = 0;
		for (int i = 1; i <= len; ++i) {
			for (int j = 0; j <= amount; ++j) {
				if (j < coins[i - 1]) dp[i][j] = dp[i - 1][j];
				else dp[i][j] = min(dp[i - 1][j], dp[i][j - coins[i - 1]] + 1);
			}
		}
		int res = dp[len][amount];
		return res < INT_MAX / 2 ? res : -1;
	}
};

// 优化为一维数组
class Solution3 {
public:
	int coinChange(vector<int> &coins, int amount) {
		int len = coins.size();
		vector<int> dp(amount + 1, INT_MAX / 2);
		dp[0] = 0;
		for (int coin : coins) {
			for (int i = coin; i <= amount; ++i) {
				dp[i] = min(dp[i], dp[i - coin] + 1);
			}
		}
		return dp[amount] < INT_MAX / 2 ? dp[amount] : -1;
	}
};

