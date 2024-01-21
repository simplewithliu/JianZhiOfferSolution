#include "header.h"

/*

LCR 068. 搜索插入位置

给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

请必须使用时间复杂度为 O(log n) 的算法

示例 1:
输入: nums = [1,3,5,6], target = 5
输出: 2

示例 2:
输入: nums = [1,3,5,6], target = 2
输出: 1

示例 3:
输入: nums = [1,3,5,6], target = 7
输出: 4

提示:
1 <= nums.length <= 10^4
-10^4 <= nums[i] <= 10^4
nums 为 无重复元素 的 升序 排列数组
-10^4 <= target <= 10^4

注意：本题与主站 35 题相同： https://leetcode-cn.com/problems/search-insert-position/


*/

class Solution {
public:
	int searchInsert(vector<int> &nums, int target) {
		int len = nums.size();
		int lo = 0, hi = len;
		// 在区间 nums[lo ... hi] 中搜索第 1 个大于等于 target 的元素下标
		while (lo < hi) {
			int mi = lo + (hi - lo) / 2;
			nums[mi] < target ? lo = mi + 1 : hi = mi;
		}
		return lo;
	}
};
/*

情况 1：如果当前 mid 看到的数值严格小于 target，那么 mid 以及 mid 左边的所有元素就一定不是「插入元素的位置」，
因此下一轮搜索区间是 [mid + 1 ... hi]，下一轮把 lo 移动到 mid + 1 位置，因此设置 lo = mid + 1；

情况 2：否则，如果 mid 看到的数值大于等于 target，那么 mid 可能是「插入元素的位置」，mid 的右边一定不是「插入元素的位置」。
如果 mid 的左边不存在「插入元素的位置」，我们才可以说 mid 是「插入元素的位置」。
因此下一轮搜索区间是 [lo ... mid]，下一轮把 hi 移动到 mid 位置，因此设置 hi = mid。

*/

// https://leetcode.cn/problems/search-insert-position/solutions/10969/te-bie-hao-yong-de-er-fen-cha-fa-fa-mo-ban-python-/
// @author https://leetcode.cn/u/liweiwei1419/

