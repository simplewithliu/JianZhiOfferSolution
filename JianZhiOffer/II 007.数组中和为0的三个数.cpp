#include "header.h"

/*

给定一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c，使得 a + b + c = 0 ？
请找出所有和为 0 且 不重复 的三元组。

示例 1：
输入：nums = [-1,0,1,2,-1,-4]
输出：[[-1,-1,2],[-1,0,1]]

示例 2：
输入：nums = []
输出：[]

示例 3：
输入：nums = [0]
输出：[]
  
提示：
0 <= nums.length <= 3000
-10^5 <= nums[i] <= 10^5
   
注意：本题与主站 15 题相同：https://leetcode-cn.com/problems/3sum/

*/

class Solution {
public:
	vector<vector<int>> threeSum(vector<int> &nums) {
		sort(nums.begin(), nums.end());
		vector<vector<int>> res;
		int len = nums.size();
		for (int i = 0; i < len - 2; ++i) {
			if (i == 0 || (i > 0 && nums[i] != nums[i - 1])) {
				int lo = i + 1, hi = len - 1, sum = 0 - nums[i];
				while (lo < hi) {
					if (nums[lo] + nums[hi] == sum) {
						res.push_back({ nums[i], nums[lo], nums[hi] });
						while (lo < hi && nums[lo] == nums[lo + 1])
							++lo;
						while (lo < hi && nums[hi] == nums[hi - 1])
							--hi;
						++lo, --hi;
					} else if (nums[lo] + nums[hi] < sum) {
						++lo;
					} else {
						--hi;
					}
				}
			}
		}
		return res;
	}
};