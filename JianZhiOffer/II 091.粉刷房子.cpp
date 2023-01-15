#include "header.h"

/*

假如有一排房子共n个，每个房子可以被粉刷成红色、蓝色或者绿色这三种颜色中的一种，你需要粉刷所有的房子并且使其相邻的两个房子颜色不能相同。
当然，因为市场上不同颜色油漆的价格不同，所以房子粉刷成不同颜色的花费成本也是不同的。
每个房子粉刷成不同颜色的花费是以一个 n x 3 的正整数矩阵 costs 来表示的。
例如，costs[0][0] 表示第 0 号房子粉刷成红色的成本花费；costs[1][2] 表示第 1 号房子粉刷成绿色的花费，以此类推。
请计算出粉刷完所有房子最少的花费成本。

示例 1：
输入: costs = [[17,2,17],[16,16,5],[14,3,19]]
输出: 10
解释: 将 0 号房子粉刷成蓝色，1 号房子粉刷成绿色，2 号房子粉刷成蓝色。最少花费: 2 + 5 + 3 = 10。

示例 2：
输入: costs = [[7,6,2]]
输出: 2

提示:
costs.length == n
costs[i].length == 3
1 <= n <= 100
1 <= costs[i][j] <= 20

注意：本题与主站 256 题相同：https://leetcode-cn.com/problems/paint-house/

*/

// 备忘录
class Solution1 {
public:
	int minCost(vector<vector<int>> &costs) {
		int len = costs.size();
		vector<vector<int>> memo(len, vector<int>(3));
		return min(helper(costs, len - 1, 0, memo),
			       min(helper(costs, len - 1, 1, memo),
					   helper(costs, len - 1, 2, memo)));
	}

private:
	int helper(vector<vector<int>> &costs, int i, int color,
		vector<vector<int>> &memo) {
		if (i < 0) return 0;
		if (memo[i][color] != 0) return memo[i][color];
		memo[i][color] = min(helper(costs, i - 1, (color + 1) % 3, memo),
			                 helper(costs, i - 1, (color + 2) % 3, memo)) +
			             costs[i][color];
		return memo[i][color];
	}
};

// 自底而上动态规划
class Solution2 {
public:
	int minCost(vector<vector<int>> &costs) {
		vector<int> dp(3);
		int len = costs.size();
		for (int j = 0; j < 3; ++j) dp[j] = costs[0][j];
		for (int i = 1; i < len; ++i) {
			vector<int> tmp(3);
			for (int j = 0; j < 3; ++j) {
				tmp[j] = min(dp[(j + 1) % 3], dp[(j + 2) % 3]) + costs[i][j];
			}
			dp = tmp;
		}
		return *min_element(dp.begin(), dp.end());
	}
};