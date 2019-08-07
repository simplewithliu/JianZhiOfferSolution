#include "header.h"

/*

给定一个数组和滑动窗口的大小，找出所有滑动窗口里数值的最大值。
例如，如果输入数组{2,3,4,2,6,2,5,1}及滑动窗口的大小3，
那么一共存在6个滑动窗口，他们的最大值分别为{4,4,6,6,6,5}。

*/

class Solution {
public:
	vector<int> maxInWindows(const vector<int> &num, unsigned int size)
	{
		int len = num.size();
		if (len < size || size < 1) return{};
		vector<int> res;
		deque<int> de;
		for (int i = 0; i < size; ++i)
		{
			while (!de.empty() && num[i] > num[de.back()])
				de.pop_back();
			de.push_back(i);
		}
		res.push_back(num[de.front()]);
		for (int i = size; i < len; ++i)
		{
			while (!de.empty() && num[i] > num[de.back()])
				de.pop_back();
			if (!de.empty() && de.front() == i - size)
				de.pop_front();
			de.push_back(i);
			res.push_back(num[de.front()]);
		}
		return res;
	}
};