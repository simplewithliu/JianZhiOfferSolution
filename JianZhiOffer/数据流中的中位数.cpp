#include "header.h"

/*

如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。
如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。
我们使用Insert()方法读取数据流，使用GetMedian()方法获取当前读取数据的中位数。

*/

class Solution {
public:
	priority_queue<int, vector<int>, less<int>> maxq;
	priority_queue<int, vector<int>, greater<int>> minq;
	void Insert(int num)
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

	double GetMedian()
	{
		if ((maxq.size() + minq.size()) & 1)
			return minq.top();
		else
			return (maxq.top() + minq.top()) / 2.0;
	}
};