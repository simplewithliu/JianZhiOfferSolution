#include "header.h"

/*

输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否可能为该栈的弹出顺序。
假设压入栈的所有数字均不相等。例如序列1,2,3,4,5是某栈的压入顺序，序列4,5,3,2,1是该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。
（注意：这两个序列的长度是相等的)

*/

class Solution {
public:
	bool IsPopOrder(vector<int> pushV, vector<int> popV)
	{
		int len1 = pushV.size();
		int len2 = popV.size();
		if (len1 != len2) return false;
		stack<int> s;
		s.push(pushV[0]);
		int i = 0, j = 0;
		while (i<len1)
		{
			if (s.top() != popV[j])
			{
				++i;
				if (i == len1)
					return false;
				s.push(pushV[i]);
			}
			else
			{
				s.pop();
				++j;
				if (j == len2)
					return true;
			}
		}
		return false;
	}
};
