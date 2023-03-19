#include "header.h"

/*

剑指 Offer II 107. 矩阵中的距离

给定一个由 0 和 1 组成的矩阵 mat，请输出一个大小相同的矩阵，其中每一个格子是 mat 中对应位置元素到最近的 0 的距离
两个相邻元素间的距离为 1

示例 1：
输入：mat = [[0,0,0],[0,1,0],[0,0,0]]
输出：[[0,0,0],[0,1,0],[0,0,0]]

示例 2：
输入：mat = [[0,0,0],[0,1,0],[1,1,1]]
输出：[[0,0,0],[0,1,0],[1,2,1]]


提示：
m == mat.length
n == mat[i].length
1 <= m, n <= 10^4
1 <= m * n <= 10^4
mat[i][j] is either 0 or 1.
mat 中至少有一个 0

注意：本题与主站 542 题相同：https://leetcode-cn.com/problems/01-matrix/

*/

// DFS
class Solution1 {
public:
	vector<vector<int>> updateMatrix(vector<vector<int>> &mat) {
		int rows = mat.size(), cols = mat[0].size();
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (mat[i][j] == 1 && !zeroneighbor(mat, i, j)) mat[i][j] = INT_MAX;
			}
		}
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (mat[i][j] == 1) dfs(mat, i, j, 0);
			}
		}
		return mat;
	}

private:
	void dfs(vector<vector<int>> &mat, int i, int j, int last) {
		if (i >= 0 && i < mat.size() && j >= 0 && j < mat[0].size() && mat[i][j] > last) {
			if (mat[i][j] != 1 && mat[i][j] == last + 1) return;
			mat[i][j] = last + 1;
			last = mat[i][j];
			dfs(mat, i - 1, j, last);
			dfs(mat, i + 1, j, last);
			dfs(mat, i, j - 1, last);
			dfs(mat, i, j + 1, last);
		}
	}
	// Optimize to avoid Time Limit Exceeded
	bool zeroneighbor(vector<vector<int>> &mat, int i, int j) {
		int offsets[] = { 0, 1, 0, -1, 0 };
		for (int k = 0; k < 4; ++k) {
			int row = i + offsets[k], col = j + offsets[k + 1];
			if (row >= 0 && row < mat.size() && col >= 0 &&
				col < mat[0].size() && mat[row][col] == 0) {
				return true;
			}
		}
		return false;
	}
};

// https://leetcode.cn/problems/01-matrix/solutions/203433/java-dfs-10ms-ac-bu-chong-yi-ge-dfsti-jie-by-carry/
// @author https://leetcode.cn/u/carryzz/

// https://leetcode.com/problems/01-matrix/solutions/2583027/dfs-vs-bfs-which-is-better-when-to-use-them/
// @author https://leetcode.com/visase/


// BFS
class Solution2 {
public:
	vector<vector<int>> updateMatrix(vector<vector<int>> &mat) {
		int rows = mat.size(), cols = mat[0].size();
		queue<pair<int, int>> q;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (mat[i][j] != 0) mat[i][j] = INT_MAX;
				else q.push({ i, j });
			}
		}
		int offsets[] = { 0, 1, 0, -1, 0 };
		while (!q.empty()) {
			pair<int, int> p = q.front();
			q.pop();
			for (int k = 0; k < 4; ++k) {
				int row = p.first + offsets[k], col = p.second + offsets[k + 1];
				if (row >= 0 && row < rows && col >= 0 && col < cols) {
					if (mat[row][col] > mat[p.first][p.second] + 1) {
						mat[row][col] = mat[p.first][p.second] + 1;
						q.push({ row, col });
					}
				}
			}
		}
		return mat;
	}
};

// https://leetcode.com/problems/01-matrix/editorial/


// 动态规划
class Solution3 {
public:
	vector<vector<int>> updateMatrix(vector<vector<int>> &mat) {
		int rows = mat.size(), cols = mat[0].size();
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				// INT_MAX will overflow
				if (mat[i][j] != 0) mat[i][j] = 1E5;
			}
		}
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (i - 1 >= 0) mat[i][j] = min(mat[i][j], mat[i - 1][j] + 1);
				if (j - 1 >= 0) mat[i][j] = min(mat[i][j], mat[i][j - 1] + 1);
			}
		}
		for (int i = rows - 1; i >= 0; --i) {
			for (int j = cols - 1; j >= 0; --j) {
				if (i + 1 < rows) mat[i][j] = min(mat[i][j], mat[i + 1][j] + 1);
				if (j + 1 < cols) mat[i][j] = min(mat[i][j], mat[i][j + 1] + 1);
			}
		}
		return mat;
	}
};

// https://leetcode.cn/problems/01-matrix/solutions/202012/01ju-zhen-by-leetcode-solution/
// @author LeetCode官方题解


