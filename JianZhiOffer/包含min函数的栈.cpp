#include "header.h"

/*

定义栈的数据结构，请在该类型中实现一个能够得到栈中所含最小元素的min函数（时间复杂度应为O（1））。

*/

class Solution {
public:
	stack<int> s;
	stack<int> mins;
	void push(int value)
	{
		s.push(value);
		if (!mins.empty())
		{
			if (value < mins.top())
				mins.push(value);
			else
				mins.push(mins.top());
		}
		else
		{
			mins.push(value);
		}
	}
	void pop()
	{
		if (!s.empty() && !mins.empty())
		{
			s.pop();
			mins.pop();
		}
	}
	int top()
	{
		if (!s.empty())
			return s.top();
		else
			return 0;
	}
	int min()
	{
		if (!mins.empty())
			return mins.top();
		else
			return 0;
	}
};