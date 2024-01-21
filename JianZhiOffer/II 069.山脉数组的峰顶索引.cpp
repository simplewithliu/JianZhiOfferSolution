#include "header.h"

/*

LCR 069. 山脉数组的峰顶索引

符合下列属性的数组 arr 称为山脉数组:
arr.length >= 3
存在 i（0 < i < arr.length - 1）使得:
arr[0] < arr[1] < ... arr[i-1] < arr[i]
arr[i] > arr[i+1] > ... > arr[arr.length - 1]
给你由整数组成的山脉数组 arr，返回满足 arr[0] < arr[1] < ... arr[i - 1] < arr[i] > arr[i + 1] > ... > arr[arr.length - 1] 的下标 i

你必须设计并实现时间复杂度为 O(log(n)) 的解决方案。

示例 1：
输入：arr = [0,1,0]
输出：1

示例 2：
输入：arr = [0,2,1,0]
输出：1

示例 3：
输入：arr = [0,10,5,2]
输出：1

提示：
3 <= arr.length <= 10^5
0 <= arr[i] <= 10^6
题目数据保证 arr 是一个山脉数组

注意：本题与主站 852 题相同：https://leetcode-cn.com/problems/peak-index-in-a-mountain-array/

*/


class Solution1 {
public:
	int peakIndexInMountainArray(vector<int> &arr) {
		int len = arr.size();
		int lo = 0, hi = len - 1;
		while (lo < hi) {
			int mi = lo + (hi - lo) / 2;
			arr[mi] < arr[mi + 1] ? lo = mi + 1 : hi = mi;
		}
		return lo;
	}
};


// 三分法
class Solution2 {
public:
	int peakIndexInMountainArray(vector<int> &arr) {
		int len = arr.size();
		int lo = 0, hi = len - 1;
		while (lo < hi) {
			int m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
			if (arr[m1] > arr[m2]) hi = m2 - 1;
			else lo = m1 + 1;
		}
		return lo;
	}
};
// https://leetcode.cn/problems/peak-index-in-a-mountain-array/solutions/828434/gong-shui-san-xie-er-fen-san-fen-cha-zhi-5gfv/
// @author https://leetcode.cn/u/ac_oier/

