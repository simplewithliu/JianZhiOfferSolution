#include "header.h"

/*

在一个 m*n 的棋盘的每一格都放有一个礼物，每个礼物都有一定的价值（价值大于 0）。
你可以从棋盘的左上角开始拿格子里的礼物，并每次向右或者向下移动一格、直到到达棋盘的右下角。
给定一个棋盘及其上面的礼物的价值，请计算你最多能拿到多少价值的礼物？

示例 1:
输入:
[
  [1,3,1],
  [1,5,1],
  [4,2,1]
]
输出: 12
解释: 路径 1→3→5→2→1 可以拿到最多价值的礼物

提示：
0 < grid.length <= 200
0 < grid[0].length <= 200

*/

//备忘录
class Solution1 {
public:
	int maxValue(vector<vector<int>> &grid)
	{
		if (grid.empty() || grid[0].empty()) return 0;
		int rows = grid.size(), cols = grid[0].size();
		vector<vector<int>> memo(rows, vector<int>(cols, 0));
		return helper(grid, 0, 0, memo);
	}
	int helper(vector<vector<int>> &grid, int i, int j, vector<vector<int>> &memo)
	{
		int rows = grid.size(), cols = grid[0].size();
		if (i == rows || j == cols) return 0;
		if (memo[i][j] != 0) return memo[i][j];
		memo[i][j] = max(helper(grid, i + 1, j, memo), helper(grid, i, j + 1, memo)) + grid[i][j];
		return memo[i][j];
	}
};

//自底而上动态规划
class Solution2 {
public:
	int maxValue(vector<vector<int>> &grid)
	{
		if (grid.empty() || grid[0].empty()) return 0;
		int rows = grid.size(), cols = grid[0].size();
		vector<vector<int>> dp(rows + 1, vector<int>(cols + 1, 0));
		for (int i = 1; i <= rows; ++i)
		{
			for (int j = 1; j <= cols; ++j)
			{
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + grid[i - 1][j - 1];
			}
		}
		return dp[rows][cols];
	}
};