#include "header.h"


/*

输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。
假设输入的前序遍历和中序遍历的结果中都不含重复的数字。
例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回。

*/

struct TreeNode {
	int val;
    TreeNode *left;
	TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution {
public:
	TreeNode * reConstructBinaryTree(vector<int> pre, vector<int> vin)
	{
		if (pre.empty() || vin.empty()) return nullptr;
		return ConstructCore(pre, 0, vin, 0, vin.size() - 1);
	}
	TreeNode * ConstructCore(vector<int> &pre, int startPre, vector<int> &vin, int startIn, int endIn)
	{
		if (startIn > endIn)
			return nullptr;
		TreeNode *root = new TreeNode(pre[startPre]);
		for (int i = startIn; i <= endIn; ++i)
		{
			if (vin[i] == root->val)
			{
				root->left = ConstructCore(pre, startPre + 1, vin, startIn, i - 1);
				root->right = ConstructCore(pre, i - startIn + startPre + 1, vin, i + 1, endIn);//i-startIn代表左子树的长度，所以i-startIn+startPre+1代表右子树先序遍历的起点。
				break;
			}
		}
		return root;
	}
};