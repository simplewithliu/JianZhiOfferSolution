#include "header.h"

/*

LCR 112. 矩阵中的最长递增路径

给定一个 m x n 整数矩阵 matrix，找出其中 最长递增路径 的长度
对于每个单元格，你可以往上，下，左，右四个方向移动
不能在 对角线 方向上移动或移动到边界外（即不允许环绕）

示例 1：
输入：matrix = [[9,9,4],[6,6,8],[2,1,1]]
输出：4
解释：最长递增路径为 [1, 2, 6, 9]

示例 2：
输入：matrix = [[3,4,5],[3,2,6],[2,2,1]]
输出：4
解释：最长递增路径是 [3, 4, 5, 6]。注意不允许在对角线方向上移动

示例 3：
输入：matrix = [[1]]
输出：1

提示：
m == matrix.length
n == matrix[i].length
1 <= m, n <= 200
0 <= matrix[i][j] <= 2^31 - 1

注意：本题与主站 329 题相同： https://leetcode-cn.com/problems/longest-increasing-path-in-a-matrix/

*/


// 参考 LeetCode 329.矩阵中的最长递增路径

// BFS + 拓扑排序
class Solution {
private:
	// 类静态成员初始化使用常量表达式，编译时可直接求值
	// https://blog.csdn.net/qq_34801642/article/details/104948850
	static constexpr int dirs[4][2] = { { -1, 0 },{ 1, 0 },{ 0, -1 },{ 0, 1 } };
	int rows;
	int cols;

public:
	int longestIncreasingPath(vector<vector<int>> &matrix) {
		if (matrix.empty() || matrix[0].empty()) return 0;
		int rows = matrix.size(), cols = matrix[0].size();
		vector<vector<int>> outDgree(rows, vector<int>(cols, 0));
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				for (auto dir : dirs) {
					int newRow = i + dir[0], newCol = j + dir[1];
					if (newRow >= 0 && newRow < rows && newCol >= 0 &&
						newCol < cols && matrix[newRow][newCol] > matrix[i][j]) {
						++outDgree[i][j];
					}
				}
			}
		}
		queue<vector<int>> q;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (outDgree[i][j] == 0) q.push({ i, j });
			}
		}
		int ans = 0;
		while (!q.empty()) {
			++ans;
			int len = q.size();
			for (int i = 0; i < len; ++i) {
				vector<int> pos = q.front();
				q.pop();
				int row = pos[0], col = pos[1];
				for (auto dir : dirs) {
					int newRow = row + dir[0], newCol = col + dir[1];
					if (newRow >= 0 && newRow < rows && newCol >= 0 &&
						newCol < cols && matrix[newRow][newCol] < matrix[row][col]) {
						if (--outDgree[newRow][newCol] == 0) q.push({ newRow, newCol });
					}
				}
			}
		}
		return ans;
	}
};

