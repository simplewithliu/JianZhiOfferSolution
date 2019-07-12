#include "header.h"

/*

二叉树的镜像

操作给定的二叉树，将其变换为源二叉树的镜像。

输入:

源二叉树
    8
   / \
  6   10
 / \  / \
5  7 9  11

输出：

镜像二叉树

    8
   /  \
  10   6
 / \  / \
11  9 7  5

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
	void Mirror(TreeNode *pRoot)
	{
		if (!pRoot) return;
		swap(pRoot->left, pRoot->right);
		Mirror(pRoot->left);
		Mirror(pRoot->right);
	}
};

