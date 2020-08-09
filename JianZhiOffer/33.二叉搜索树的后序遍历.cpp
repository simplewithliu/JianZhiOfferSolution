#include "header.h"

/*

输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历结果。如果是则返回 true，否则返回 false。假设输入的数组的任意两个数字都互不相同。

参考以下这颗二叉搜索树：

    5
   / \
  2   6
 / \
1   3

示例 1：
输入: [1,6,3,2,5]
输出: false
 
示例 2：
输入: [1,3,2,6,5]
输出: true
  
提示：数组长度 <= 1000

*/

class Solution1 {
public:
	bool verifyPostorder(vector<int> &postorder) 
	{
		if (postorder.empty()) return true;
		int len = postorder.size();
		return helper(postorder, 0, len - 1);
	}
	bool helper(vector<int> &v, int start, int end)
	{
		int root = v[end];
		int i = start;
		for (; i < end; ++i) if (v[i] > root) break;
		int j = i;
		for (; j < end; ++j) if (v[j] < root) return false;
		int left = true;
		if (i > start) left = helper(v, start, i - 1);
		int right = true;
		if (i < end) right = helper(v, i, end - 1);
		return left&&right;
	}
};

class Solution2 {
public:
	bool verifyPostorder(vector<int>& postorder) 
	{
		if (postorder.empty()) return true;
		stack<int> s;
		int root = INT_MAX;
		int len = postorder.size();
		for (int i = len - 1; i >= 0; --i)
		{
			if (postorder[i] > root) return false;
			while (!s.empty() && s.top() > postorder[i])
			{
				root = s.top();
				s.pop();
			}
			s.push(postorder[i]);
		}
		return true;
	}
};