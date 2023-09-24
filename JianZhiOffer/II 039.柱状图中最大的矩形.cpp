#include "header.h"

/*

LCR 039. 柱状图中最大的矩形

给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1
求在该柱状图中，能够勾勒出来的矩形的最大面积

示例 1:
输入：heights = [2,1,5,6,2,3]
输出：10
解释：最大的矩形为图中红色区域，面积为 10

示例 2：
输入： heights = [2,4]
输出： 4

提示：
1 <= heights.length <=10^5
0 <= heights[i] <= 10^4

注意：本题与主站 84 题相同： https://leetcode-cn.com/problems/largest-rectangle-in-histogram/

*/

class Solution {
public:
	int largestRectangleArea(vector<int> &heights) {
		int ans = 0;
		stack<int> s;
		// 头部哨兵
		heights.insert(heights.begin(), 0);
		// 尾部哨兵
		heights.push_back(0);
		s.push(0);
		for (int i = 0; i < heights.size(); ++i) {
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