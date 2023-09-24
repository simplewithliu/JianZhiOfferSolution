#include "header.h"

/*

给定一个仅包含 0 和 1, 大小为 rows x cols 的二维二进制矩阵，找出只包含 1 的最大矩形，并返回其面积

示例 1：
输入：matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
输出：6
解释：最大矩形如上图所示

示例 2：
输入：matrix = []
输出：0

示例 3：
输入：matrix = [["0"]]
输出：0

示例 4：
输入：matrix = [["1"]]
输出：1

示例 5：
输入：matrix = [["0","0"]]
输出：0

提示：
rows == matrix.length
cols == matrix[0].length
1 <= row, cols <= 200
matrix[i][j] 为 '0' 或 '1'

注意：本题与主站 85 题相同（输入参数格式不同）：https://leetcode.cn/problems/maximal-rectangle/

*/

// 前缀和 + 单调栈
class Solution {
public:
	int maximalRectangle(vector<string> &matrix) {
		if (matrix.empty() || matrix[0].empty()) return 0;
		int rows = matrix.size(), cols = matrix[0].size();
		// 每一行都添加头尾哨兵
		vector<vector<int>> sum(rows + 1, vector<int>(cols + 2, 0));
		int maxArea = 0;
		for (int i = 1; i <= rows; ++i) {
			for (int j = 1; j <= cols; ++j) {
				sum[i][j] = matrix[i - 1][j - 1] == '0' ? 0 : sum[i - 1][j] + 1;
			}
			maxArea = max(maxArea, largestRectangleArea(sum[i]));
		}
		return maxArea;
	}

private:
	int largestRectangleArea(const vector<int> &heights) {
		int ans = 0;
		stack<int> s;
		s.push(0);
		for (int i = 1; i < heights.size(); ++i) {
			while (heights[i] < heights[s.top()]) {
				int cur = s.top();
				s.pop();
				int left = s.top() + 1;
				int right = i - 1;
				ans = max(ans, (right - left + 1) * heights[cur]);
			}
			s.push(i);
		}
		return ans;
	}
};