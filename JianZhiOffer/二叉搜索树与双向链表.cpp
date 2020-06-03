#include "header.h"

/*

输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。
要求不能创建任何新的结点，只能调整树中结点指针的指向。

*/

class Solution {
public:
	TreeNode * Convert(TreeNode *pRootOfTree)
	{
		if (!pRootOfTree) return nullptr;
		TreeNode *node = pRootOfTree;
		TreeNode *lastnode = nullptr;
		travIn(node, lastnode);
		while (node->left)
		{
			node = node->left;
		}
		return node;
	}
	void travIn(TreeNode *node, TreeNode *&lastnode)
	{
		if (!node) return;
		travIn(node->left, lastnode);
		node->left = lastnode;
		if (lastnode)
			lastnode->right = node;
		lastnode = node;
		travIn(node->right, lastnode);
	}
};
