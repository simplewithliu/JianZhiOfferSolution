#include "header.h"

/*

剑指 Offer II 100. 三角形中最小路径之和

给定一个三角形 triangle，找出自顶向下的最小路径和。每一步只能移动到下一行中相邻的结点上。
相邻的结点 在这里指的是 下标 与 上一层结点下标 相同或者等于 上一层结点下标 + 1 的两个结点。
也就是说，如果正位于当前行的下标 i ，那么下一步可以移动到下一行的下标 i 或 i + 1 。

示例 1：
输入：triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
输出：11
解释：如下面简图所示：
2
3 4
6 5 7
4 1 8 3
自顶向下的最小路径和为 11（即，2 + 3 + 5 + 1 = 11）。

示例 2：
输入：triangle = [[-10]]
输出：-10

提示：
1 <= triangle.length <= 200
triangle[0].length == 1
triangle[i].length == triangle[i - 1].length + 1
-10^4 <= triangle[i][j] <= 10^4

进阶：你可以只使用 O(n) 的额外空间（n 为三角形的总行数）来解决这个问题吗？

注意：本题与主站 120 题相同： https://leetcode-cn.com/problems/triangle/

*/

// 备忘录
class Solution1 {
public:
	int minimumTotal(vector<vector<int>> &triangle) {
		int rows = triangle.size(), cols = triangle.size();
		vector<vector<int>> memo(rows, vector<int>(cols, INT_MAX));
		int ans = INT_MAX;
		for (int j = 0; j < cols; ++j) {
			ans = min(helper(triangle, rows - 1, j, memo), ans);
		}
		return ans;
	}

private:
	int helper(vector<vector<int>> &triangle, int i, int j,
		vector<vector<int>> &memo) {
		if (memo[i][j] != INT_MAX) return memo[i][j];
		if (i == 0) {
			return triangle[0][0];
		}
		if (j == 0) {
			return memo[i][j] = helper(triangle, i - 1, j, memo) + triangle[i][j];
		}
		if (j == triangle[i].size() - 1) {
			return memo[i][j] = helper(triangle, i - 1, j - 1, memo) + triangle[i][j];
		}
		return memo[i][j] = min(helper(triangle, i - 1, j, memo),
			helper(triangle, i - 1, j - 1, memo)) + triangle[i][j];
	}
};

// 自底而上的动态规划
class Solution2 {
public:
	int minimumTotal(vector<vector<int>> &triangle) {
		int rows = triangle.size(), cols = triangle.size();
		vector<vector<int>> dp(rows, vector<int>(cols));
		dp[0][0] = triangle[0][0];
		for (int i = 1; i < rows; ++i) {
			for (int j = 0; j <= i; ++j) {
				if (j == 0) dp[i][j] = dp[i - 1][0] + triangle[i][j];
				else if (j == i) dp[i][j] = dp[i - 1][j - 1] + triangle[i][j];
				else dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i][j];
			}
		}
		return *min_element(dp[rows - 1].begin(), dp[rows - 1].end());
	}
};

// 该题目可以反方向递推，逻辑更清晰。可参考：
// https://leetcode.cn/problems/triangle/solutions/329394/di-gui-ji-yi-hua-dp-bi-xu-miao-dong-by-sweetiee/