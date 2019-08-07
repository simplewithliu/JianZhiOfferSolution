#include "header.h"

/*

给定一棵二叉搜索树，请找出其中的第k个的结点。
例如,(5，3，7，2，4，6，8)中，按结点数值大小顺序第三个结点的值为4。

*/


struct TreeNode 
{
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
		val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	TreeNode * KthNode(TreeNode *pRoot, int k)
	{
		int num = 0;
		return travIn(pRoot, num, k);
	}
	TreeNode * travIn(TreeNode *node, int &num, int k)
	{
		if (!node) return nullptr;
		TreeNode *temp;
		temp = travIn(node->left, num, k);
		if (temp)
			return temp;
		num += 1;
		if (num == k)
			return node;
		temp = travIn(node->right, num, k);
		if (temp)
			return temp;
		return nullptr;
	}
};
