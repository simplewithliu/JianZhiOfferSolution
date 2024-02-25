#include "header.h"

/*

LCR 082. 组合总和 II

给定一个候选人编号的集合 candidates 和一个目标数 target，找出 candidates 中所有可以使数字和为 target 的组合
candidates 中的每个数字在每个组合中只能使用 一次
注意：解集不能包含重复的组合

示例 1:
输入: candidates = [10,1,2,7,6,1,5], target = 8,
输出:
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]

示例 2:
输入: candidates = [2,5,2,1,2], target = 5,
输出:
[
[1,2,2],
[5]
]

提示:
1 <= candidates.length <= 100
1 <= candidates[i] <= 50
1 <= target <= 30

注意：本题与主站 40 题相同： https://leetcode-cn.com/problems/combination-sum-ii/

*/

class Solution {
private:
	vector<int> path;
	vector<vector<int>> res;

public:
	vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
		sort(candidates.begin(), candidates.end());
		backtrack(candidates, 0, target);
		return res;
	}

private:
	void backtrack(const vector<int> &candidates, int begin, int target) {
		if (target == 0) {
			res.push_back(path);
			return;
		}
		for (int i = begin; i < candidates.size(); ++i) {
			if (target - candidates[i] < 0) return;
			if (i > begin && candidates[i] == candidates[i - 1]) continue;
			path.push_back(candidates[i]);
			backtrack(candidates, i + 1, target - candidates[i]);
			path.pop_back();
		}
	}
};
