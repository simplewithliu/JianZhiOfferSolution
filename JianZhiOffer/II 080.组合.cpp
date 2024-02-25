#include "header.h"

/*

LCR 080. 组合

给定两个整数 n 和 k，返回范围 [1, n] 中所有可能的 k 个数的组合。
你可以按 任何顺序 返回答案。

示例 1：
输入：n = 4, k = 2
输出：
[
[2,4],
[3,4],
[2,3],
[1,2],
[1,3],
[1,4],
]

示例 2：
输入：n = 1, k = 1
输出：[[1]]

提示：
1 <= n <= 20
1 <= k <= n

注意：本题与主站 77 题相同： https://leetcode-cn.com/problems/combinations/

*/


class Solution {
public:
	vector<vector<int>> combine(int n, int k) {
		vector<vector<int>> res;
		if (k <= 0 || n < k) return res;
		vector<int> path;
		backtrack(n, k, 1, path, res);
		return res;
	}

private:
	void backtrack(int n, int k, int start, vector<int> &path,
		vector<vector<int>> &res) {
		if (path.size() == k) {
			res.push_back(path);
			return;
		}
		for (int i = start; i <= n - (k - path.size()) + 1; ++i) {
			path.push_back(i);
			backtrack(n, k, i + 1, path, res);
			path.pop_back();
		}
	}
};
