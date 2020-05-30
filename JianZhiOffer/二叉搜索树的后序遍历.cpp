#include "header.h"

/*

输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。
如果是则输出Yes,否则输出No。假设输入的数组的任意两个数字都互不相同。

*/

class Solution {
public:
	bool VerifySquenceOfBST(vector<int> sequence)
	{
		if (sequence.empty())
			return false;
		int len = sequence.size();
		return recur(sequence, 0, len - 1);
	}
	bool recur(vector<int> &sequence, int start, int end)
	{
		int root = sequence[end];
		int i = start;
		for (; i<end; ++i)
		{
			if (sequence[i]>root)
				break;
		}
		int j = i;
		for (; j<end; ++j)
		{
			if (sequence[j]<root)
				return false;
		}

		bool left = true;
		if (i>start)
			left = recur(sequence, start, i - 1);
		bool right = true;
		if (i<end)
			right = recur(sequence, i, end - 1);
		return left&&right;
	}
};