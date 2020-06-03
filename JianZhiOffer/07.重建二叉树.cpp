#include "header.h"


/*

输入某二叉树的前序遍历和中序遍历的结果，请重建该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。

例如，给出

前序遍历 preorder = [3,9,20,15,7]

中序遍历 inorder = [9,3,15,20,7]

返回如下的二叉树：

     3
    / \
   9  20
     /  \
    15   7
  
限制：0 <= 节点个数 <= 5000
注意：本题与主站 105 题重复：https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

*/

class Solution {
public:
	TreeNode * buildTree(vector<int> &preorder, vector<int> &inorder) 
	{
		if (preorder.empty() || inorder.empty()) return nullptr;
		int len = inorder.size();
		return helper(preorder, 0, inorder, 0, len - 1);
	}
	TreeNode * helper(vector<int> &preorder, int startPre, vector<int> &inorder, int startIn, int endIn)
	{
		if (startIn > endIn) return nullptr;
		TreeNode *root = new TreeNode(preorder[startPre]);
		for (int i = startIn; i <= endIn; ++i)
		{
			if (inorder[i] == root->val)
			{
				root->left = helper(preorder, startPre + 1, inorder, startIn, i - 1);
				root->right = helper(preorder, i - startIn + startPre + 1, inorder, i + 1, endIn);//i-startIn代表左子树的长度，所以i-startIn+startPre+1代表右子树先序遍历的起点。
				break;
			}
		}
		return root;
	}
};