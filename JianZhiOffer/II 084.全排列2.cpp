#include "header.h"

/*

LCR 084. 全排列 II

给定一个可包含重复数字的整数集合 nums，按任意顺序 返回它所有不重复的全排列

示例 1：
输入：nums = [1,1,2]
输出：
[[1,1,2],
[1,2,1],
[2,1,1]]

示例 2：
输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

提示：
1 <= nums.length <= 8
-10 <= nums[i] <= 10

注意：本题与主站 47 题相同： https://leetcode-cn.com/problems/permutations-ii/

*/

class Solution {
private:
	vector<vector<int>> res;
	vector<int> path;
	int used = 0;

public:
	vector<vector<int>> permuteUnique(vector<int> &nums) {
		int len = nums.size();
		sort(nums.begin(), nums.end());
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
			if (i > 0 && nums[i] == nums[i - 1] && !(used & (1 << (i - 1)))) {
				continue;
			}
			path.push_back(nums[i]);
			used |= (1 << i);
			backtrack(nums);
			path.pop_back();
			used &= ~(1 << i);
		}
	}
};

