#include "header.h"

/*

剑指 Offer II 076. 数组中的第 k 大的数字

给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。

示例 1:
输入: [3,2,1,5,6,4], k = 2
输出: 5

示例 2:
输入: [3,2,3,1,2,4,5,5,6], k = 4
输出: 4

提示：
1 <= k <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4

注意：本题与主站 215 题相同： https://leetcode-cn.com/problems/kth-largest-element-in-an-array/

*/

// 快速划分
class Solution1 {
public:
	int findKthLargest(vector<int> &nums, int k) {
		int len = nums.size();
		int lo = 0, hi = len - 1;
		int target = len - k;
		int index = partition(nums, lo, hi);
		while (index != target) {
			if (index > target) {
				hi = index - 1;
				index = partition(nums, lo, hi);
			}
			else {
				lo = index + 1;
				index = partition(nums, lo, hi);
			}
		}
		return nums[index];
	}

private:
	int partition(vector<int> &nums, int lo, int hi) {
		swap(nums[lo], nums[lo + rand() % (hi - lo + 1)]);
		int pivot = nums[lo];
		while (lo < hi) {
			while (lo < hi) {
				if (nums[hi] > pivot) {
					--hi;
				} else {
					nums[lo++] = nums[hi];
					break;
				}
			}
			while (lo < hi) {
				if (nums[lo] < pivot) {
					++lo;
				} else {
					nums[hi--] = nums[lo];
					break;
				}
			}
		}
		nums[lo] = pivot;
		return lo;
	}
};


// 堆排序
class Solution2 {
public:
	int findKthLargest(vector<int> &nums, int k) {
		priority_queue<int, vector<int>, greater<int>> pq;
		for (int num : nums) {
			pq.push(num);
			if (pq.size() > k) pq.pop();
		}
		return pq.top();
	}
};