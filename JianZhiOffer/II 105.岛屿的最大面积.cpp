#include "header.h"
/*

给你一个大小为 m x n 的二进制矩阵 grid
岛屿 是由一些相邻的 1 (代表土地) 构成的组合，这里的「相邻」要求两个 1 必须在 水平或者竖直的四个方向上 相邻
你可以假设 grid 的四个边缘都被 0（代表水）包围着，岛屿的面积是岛上值为 1 的单元格的数目
计算并返回 grid 中最大的岛屿面积。如果没有岛屿，则返回面积为 0

示例 1：
输入：
grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],
		[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],
		[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
输出：6
解释：答案不应该是 11 ，因为岛屿只能包含水平或垂直这四个方向上的 1 。

示例 2：
输入：grid = [[0,0,0,0,0,0,0,0]]
输出：0

提示：
m == grid.length
n == grid[i].length
1 <= m, n <= 50
grid[i][j] 为 0 或 1

注意：本题与主站 695 题相同： https://leetcode-cn.com/problems/max-area-of-island/

*/

// DFS
class Solution1 {
public:
	int maxAreaOfIsland(vector<vector<int>> &grid) {
		int rows = grid.size(), cols = grid[0].size();
		int maxNum = 0;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				int sum = 0;
				dfs(grid, i, j, sum);
				maxNum = max(maxNum, sum);
			}
		}
		return maxNum;
	}

private:
	void dfs(vector<vector<int>> &grid, int i, int j, int &sum) {
		if (i >= 0 && i < grid.size() && j >= 0 && j < grid[0].size() && grid[i][j]) {
			grid[i][j] = 0;
			++sum;
			dfs(grid, i - 1, j, sum);
			dfs(grid, i + 1, j, sum);
			dfs(grid, i, j - 1, sum);
			dfs(grid, i, j + 1, sum);
		}
	}
};

// BFS
class Solution2 {
public:
	int maxAreaOfIsland(vector<vector<int>> &grid) {
		int rows = grid.size(), cols = grid[0].size();
		int maxNum = 0;
		int offsets[] = { 0, 1, 0, -1, 0 };
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (grid[i][j]) {
					int sum = 1;
					grid[i][j] = 0;
					queue<pair<int, int>> q;
					q.push({ i, j });
					while (!q.empty()) {
						pair<int, int> p = q.front();
						q.pop();
						for (int k = 0; k < 4; ++k) {
							int row = p.first + offsets[k], col = p.second + offsets[k + 1];
							if (row >= 0 && row < rows && col >= 0 &&
								col < cols && grid[row][col]) {
								q.push({ row, col });
								grid[row][col] = 0;
								++sum;
							}
						}
					}
					maxNum = max(maxNum, sum);
				}
			}
		}
		return maxNum;
	}
};


// 并查集
class UF {
private:
	vector<int> id;
	vector<int> count;

public:
	int maxNum = 0;
	UF(vector<vector<int>> &grid, int rows, int cols) {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				id.push_back(i * cols + j);
				if (grid[i][j]) {
					count.push_back(1);
					maxNum = 1;
				} else {
					count.push_back(0);
				}
			}
		}
	}
	int find(int x) {
		if (id[x] != x) id[x] = find(id[x]);
		return id[x];
	}
	void unionIslands(int p, int q) {
		int pRoot = find(p);
		int qRoot = find(q);
		if (pRoot == qRoot) return;
		id[pRoot] = qRoot;
		count[qRoot] += count[pRoot];
		maxNum = max(maxNum, count[qRoot]);
	}
};

class Solution3 {
public:
	int maxAreaOfIsland(vector<vector<int>> &grid) {
		int rows = grid.size(), cols = grid[0].size();
		UF uf(grid, rows, cols);
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				int land = i * cols + j;
				if (grid[i][j]) {
					if (j < cols - 1 && grid[i][j + 1]) uf.unionIslands(land, land + 1);
					if (i < rows - 1 && grid[i + 1][j]) uf.unionIslands(land, land + cols);
				}
			}
		}
		return uf.maxNum;
	}
};