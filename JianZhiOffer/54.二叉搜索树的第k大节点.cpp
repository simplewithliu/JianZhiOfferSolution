#include "header.h"

/*

给定一棵二叉搜索树，请找出其中第k大的节点。

示例 1:
输入: root = [3,1,4,null,2], k = 1
     3
    / \
   1   4
    \
     2
输出: 4
	
示例 2:
输入: root = [5,3,6,2,4,null,null,1], k = 3
	   5
	  / \
     3   6
    / \
   2   4
  /
 1
输出: 4
	 
限制：1 ≤ k ≤ 二叉搜索树元素个数

*/

class Solution {
public:
	int kthLargest(TreeNode *root, int k)
	{
		int count = 0;
		int res = 0;
		helper(root, k, res, count);
		return res;
	}
	void helper(TreeNode *node, int k, int &res, int &count)
	{
		if (!node) return;
		helper(node->right, k, res, count);
		if (++count == k) res = node->val;
		helper(node->left, k, res, count);
	}
};