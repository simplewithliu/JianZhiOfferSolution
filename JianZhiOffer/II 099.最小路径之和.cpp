#include "header.h"

/*

剑指 Offer II 099. 最小路径之和

给定一个包含非负整数的 m x n 网格 grid，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
说明：每次只能向下或者向右移动一步。

示例 1：
输入：grid = [[1,3,1],[1,5,1],[4,2,1]]
输出：7
解释：因为路径 1→3→1→1→1 的总和最小。

示例 2：
输入：grid = [[1,2,3],[4,5,6]]
输出：12

提示：
m == grid.length
n == grid[i].length
1 <= m, n <= 200
0 <= grid[i][j] <= 100

注意：本题与主站 64 题相同： https://leetcode-cn.com/problems/minimum-path-sum/

*/

// 备忘录
class Solution1 {
public:
	int minPathSum(vector<vector<int>> &grid) {
		int rows = grid.size(), cols = grid[0].size();
		vector<vector<int>> memo(rows, vector<int>(cols));
		return helper(grid, rows - 1, cols - 1, memo);
	}

private:
	int helper(vector<vector<int>> &grid, int i, int j,
		vector<vector<int>> &memo) {
		if (memo[i][j] != 0) return memo[i][j];
		if (i == 0 && j == 0) return grid[i][j];
		if (i == 0) return memo[i][j] = grid[i][j] + helper(grid, i, j - 1, memo);
		if (j == 0) return memo[i][j] = grid[i][j] + helper(grid, i - 1, j, memo);
		memo[i][j] = min(helper(grid, i - 1, j, memo), helper(grid, i, j - 1, memo)) + grid[i][j];
		return memo[i][j];
	}
};

// 自底而上的动态规划
class Solution2 {
public:
	int minPathSum(vector<vector<int>> &grid) {
		int rows = grid.size(), cols = grid[0].size();
		vector<vector<int>> dp(rows, vector<int>(cols));
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (i == 0 && j == 0) dp[i][j] = grid[i][j];
				else if (i == 0) dp[i][j] = dp[i][j - 1] + grid[i][j];
				else if (j == 0) dp[i][j] = dp[i - 1][j] + grid[i][j];
				else dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
			}
		}
		return dp[rows - 1][cols - 1];
	}
};
