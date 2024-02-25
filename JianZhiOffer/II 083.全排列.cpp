#include "header.h"

/*

LCR 083. 全排列

给定一个不含重复数字的数组 nums，返回其所有可能的全排列
你可以 按任意顺序 返回答案

示例 1：
输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

示例 2：
输入：nums = [0,1]
输出：[[0,1],[1,0]]

示例 3：
输入：nums = [1]
输出：[[1]]

提示：
1 <= nums.length <= 6
-10 <= nums[i] <= 10
nums 中的所有整数 互不相同

注意：本题与主站 46 题相同：https://leetcode-cn.com/problems/permutations/

*/

class Solution {
private:
	vector<vector<int>> res;
	vector<int> path;
	int used = 0;

public:
	vector<vector<int>> permute(vector<int> &nums) {
		backtrack(nums);
		return res;
	}

private:
	void backtrack(const vector<int> &nums) {
		if (path.size() == nums.size()) {
			res.push_back(path);
			return;
		}
		for (int i = 0; i < nums.size(); ++i) {
			if (used & (1 << i)) continue;
			path.push_back(nums[i]);
			used |= (1 << i);
			backtrack(nums);
			path.pop_back();
			used &= ~(1 << i);
		}
	}
};

