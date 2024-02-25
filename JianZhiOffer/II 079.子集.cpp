#include "header.h"

/*

LCR 079. 子集

给你一个整数数组 nums，数组中的元素 互不相同
返回该数组所有可能的子集（幂集）

解集 不能 包含重复的子集，你可以按 任意顺序 返回解集

示例 1：
输入：nums = [1,2,3]
输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

示例 2：
输入：nums = [0]
输出：[[],[0]]

提示：
1 <= nums.length <= 10
-10 <= nums[i] <= 10
nums 中的所有元素 互不相同

注意：本题与主站 78 题相同： https://leetcode-cn.com/problems/subsets/

*/

class Solution {
private:
	vector<vector<int>> res;

public:
	vector<vector<int>> subsets(vector<int> &nums) {
		vector<int> path;
		backtrack(nums, path, 0);
		return res;
	}

private:
	void backtrack(vector<int> &nums, vector<int> &path, int start) {
		res.push_back(path);
		for (int i = start; i < nums.size(); ++i) {
			path.push_back(nums[i]);
			backtrack(nums, path, i + 1);
			path.pop_back();
		}
	}
};

