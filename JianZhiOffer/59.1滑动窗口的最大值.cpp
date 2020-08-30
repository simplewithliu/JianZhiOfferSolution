#include "header.h"

/*

给定一个数组 nums 和滑动窗口的大小 k，请找出所有滑动窗口里的最大值。

示例:
输入: nums = [1,3,-1,-3,5,3,6,7], 和 k = 3
输出: [3,3,5,5,6,7]
解释:

滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7      3
1 [3  -1  -3] 5  3  6  7       3
1  3 [-1  -3  5] 3  6  7       5
1  3  -1 [-3  5  3] 6  7       5
1  3  -1  -3 [5  3  6] 7       6
1  3  -1  -3  5 [3  6  7]      7
 
提示：
你可以假设 k 总是有效的，在输入数组不为空的情况下，1 ≤ k ≤ 输入数组的大小。
注意：本题与主站 239 题相同：https://leetcode-cn.com/problems/sliding-window-maximum/

*/

//利用双端队列实现单调队列
class Solution1 {
public:
	vector<int> maxSlidingWindow(vector<int> &nums, int k) 
	{
		int len = nums.size();
		if (nums.empty()) return {};
		vector<int> res;
		deque<int> de;
		for (int i = 0; i < k; ++i)
		{
			while (!de.empty() && nums[i] > nums[de.back()]) de.pop_back();
			de.push_back(i);
		}
		res.push_back(nums[de.front()]);
		for (int i = k; i < len; ++i)
		{
			while (!de.empty() && nums[i] > nums[de.back()]) de.pop_back();
			if (!de.empty() && de.front() == i - k) de.pop_front();
			de.push_back(i);
			res.push_back(nums[de.front()]);
		}
		return res;
	}
};

//分块动态规划(技巧性)
class Solution2 {
public:
	vector<int> maxSlidingWindow(vector<int> &nums, int k)
	{
		int len = nums.size();
		if (k == 0) return {};
		if (k == 1) return nums;
		vector<int> left(len);
		vector<int> right(len);
		left[0] = nums[0];
		right[0] = nums[len - 1];
		for (int i = 1; i < len; ++i)
		{
			//从左到右
			if (i % k == 0) left[i] = nums[i];
			else left[i] = max(left[i - 1], nums[i]);
			//从右到左
			int j = len - 1 - i;
			if ((j + 1) % k == 0) right[j] = nums[j];
			else right[j] = max(right[j + 1], nums[j]);
		}
		vector<int> res(len - k + 1);
		for (int i = 0; i < len - k + 1; ++i)
		{
			res[i] = max(left[i + k - 1], right[i]);
		}
		return res;
	}
};
//https://leetcode-cn.com/problems/sliding-window-maximum/solution/hua-dong-chuang-kou-zui-da-zhi-by-leetcode-3/