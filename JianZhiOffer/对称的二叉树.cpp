#include "header.h"

/*

请实现一个函数，用来判断一颗二叉树是不是对称的。
注意，如果一个二叉树同此二叉树的镜像是同样的，定义其为对称的。

*/

struct TreeNode 
{
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
		val(x), left(NULL), right(NULL) {}
};

class Solution
{
public:
	bool isSymmetrical(TreeNode *pRoot)
	{
		if (!pRoot) return true;
		return trav(pRoot->left, pRoot->right);
	}
	bool trav(TreeNode *LNode, TreeNode *RNode)
	{
		if (!LNode || !RNode)
			return LNode == RNode;
		else if (LNode->val != RNode->val)
			return false;
		else
			return trav(LNode->left, RNode->right) && trav(LNode->right, RNode->left);
	}
};