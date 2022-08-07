#include "header.h"

/*

以数组intervals表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi]
请你合并所有重叠的区间，并返回一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间

示例 1：
输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
输出：[[1,6],[8,10],[15,18]]
解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6]

示例 2：
输入：intervals = [[1,4],[4,5]]
输出：[[1,5]]
解释：区间 [1,4] 和 [4,5] 可被视为重叠区间
  
提示：
1 <= intervals.length <= 10^4
intervals[i].length == 2
0 <= starti <= endi <= 10^4

*/

class Solution {
public:
	vector<vector<int>> merge(vector<vector<int>> &intervals) {
		if (intervals.empty()) return{};
		/**
		* 也可以直接使用sort(intervals.begin(), intervals.end());
		* C++ Primer 9.2.7
		*/
		sort(intervals.begin(), intervals.end(),
			[](const vector<int> &a, const vector<int> &b) {
			return a[0] < b[0];
		});
		vector<vector<int>> res;
		res.push_back(intervals[0]);
		for (auto interval : intervals) {
			if (interval[0] <= res.back()[1]) {
				res.back()[1] = max(interval[1], res.back()[1]);
			}
			else {
				res.push_back(interval);
			}
		}
		return res;
	}
};
