#include "header.h"

/*

输入整数数组 arr ，找出其中最小的 k 个数。例如，输入4、5、1、6、2、7、3、8这8个数字，则最小的4个数字是1、2、3、4。

示例 1：
输入：arr = [3,2,1], k = 2
输出：[1,2] 或者 [2,1]

示例 2：
输入：arr = [0,1,2,1], k = 1
输出：[0]

限制：
0 <= k <= arr.length <= 10000
0 <= arr[i] <= 10000

*/

//快速划分
class Solution1 {
public:
	vector<int> getLeastNumbers(vector<int> &arr, int k) 
	{
		int len = arr.size();
		if (k <= 0) return {};
		if (k > len) return {};
		if (k == len) return arr;
		int start = 0, end = len - 1;
		int index = partition(arr, start, end);
		while (index != k - 1)
		{
			if (index > k - 1)
			{
				end = index - 1;
				index = partition(arr, start, end);
			}
			else
			{
				start = index + 1;
				index = partition(arr, start, end);
			}
		}
		vector<int> res(arr.begin(), arr.begin() + k);
		return res;
	}
	int partition(vector<int> &data, int lo, int hi)
	{
		swap(data[lo], data[lo + rand() % (hi - lo + 1)]);
		int pivot = data[lo];
		while (lo < hi)
		{
			while (lo < hi)
			{
				if (pivot < data[hi])
					--hi;
				else
				{
					data[lo++] = data[hi];
					break;
				}
			}
			while (lo < hi)
			{
				if (pivot > data[lo])
					++lo;
				else
				{
					data[hi--] = data[lo];
					break;
				}
			}
		}
		data[lo] = pivot;
		return lo;
	}
};

//优先级队列
class Solution2 {
public:
	vector<int> getLeastNumbers(vector<int> &arr, int k)
	{
		int len = arr.size();
		if (k <= 0) return {};
		if (k > len) return {};
		if (k == len) return arr;
		priority_queue<int> pq;
		for (int num : arr)
		{
			if (pq.empty() || pq.size() < k || num < pq.top()) pq.push(num);
			if (pq.size() > k) pq.pop();
		}
		vector<int> res;
		for (int i = 0; i < k; ++i)
		{
			res.push_back(pq.top());
			pq.pop();
		}
		return res;
	}
};

//https://leetcode-cn.com/problems/zui-xiao-de-kge-shu-lcof/solution/tu-jie-top-k-wen-ti-de-liang-chong-jie-fa-you-lie-/