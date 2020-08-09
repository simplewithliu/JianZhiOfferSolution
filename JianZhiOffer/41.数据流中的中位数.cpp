#include "header.h"

/*

如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。
如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。
例如，[2,3,4] 的中位数是 3，[2,3] 的中位数是 (2 + 3) / 2 = 2.5

设计一个支持以下两种操作的数据结构：
void addNum(int num) - 从数据流中添加一个整数到数据结构中。
double findMedian() - 返回目前所有元素的中位数。

示例 1：
输入：
["MedianFinder","addNum","addNum","findMedian","addNum","findMedian"]
[[],[1],[2],[],[3],[]]
输出：[null,null,null,1.50000,null,2.00000]

示例 2：
输入：
["MedianFinder","addNum","findMedian","addNum","findMedian"]
[[],[2],[],[3],[]]
输出：[null,null,2.00000,null,2.50000]
 
限制：最多会对 addNum、findMedia进行 50000 次调用。
注意：本题与主站 295 题相同：https://leetcode-cn.com/problems/find-median-from-data-stream/

*/

class MedianFinder {
public:
	priority_queue<int, vector<int>, less<int>> maxq;
	priority_queue<int, vector<int>, greater<int>> minq;
	/** initialize your data structure here. */
	MedianFinder() {}

	void addNum(int num) 
	{
		if (maxq.size() != minq.size())
		{
			minq.push(num);
			maxq.push(minq.top());
			minq.pop();
		}
		else
		{
			maxq.push(num);
			minq.push(maxq.top());
			maxq.pop();
		}
	}

	double findMedian() 
	{
		return maxq.size() != minq.size() ? minq.top() : (minq.top() + maxq.top()) / 2.0;
	}
};

/**
* Your MedianFinder object will be instantiated and called as such:
* MedianFinder* obj = new MedianFinder();
* obj->addNum(num);
* double param_2 = obj->findMedian();
*/

//另一种详细的实现方法
class Solution {
public:
	priority_queue<int, vector<int>, less<int>> maxq;
	priority_queue<int, vector<int>, greater<int>> minq;
	void addNum(int num)
	{
		if ((maxq.size() + minq.size()) & 1)
		{
			if (!minq.empty() && num > minq.top())
			{
				int temp = minq.top();
				minq.pop();
				maxq.push(temp);
				minq.push(num);
			}
			else
			{
				maxq.push(num);
			}
		}
		else
		{
			if (!maxq.empty() && num < maxq.top())
			{
				int temp = maxq.top();
				maxq.pop();
				minq.push(temp);
				maxq.push(num);
			}
			else
			{
				minq.push(num);
			}
		}
	}

	double findMedian()
	{
		if ((maxq.size() + minq.size()) & 1)
			return minq.top();
		else
			return (maxq.top() + minq.top()) / 2.0;
	}
};