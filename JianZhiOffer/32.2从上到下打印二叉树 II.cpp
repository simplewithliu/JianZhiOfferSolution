#include "header.h"
/*

从上到下按层打印二叉树，同一层的节点按从左到右的顺序打印，每一层打印到一行。

例如:
给定二叉树: [3,9,20,null,null,15,7],

         3
        / \
       9  20
         /  \
        15   7

返回其层次遍历结果：
[
  [3],
  [9,20],
  [15,7]
]
  
提示：
节点总数 <= 1000

注意：本题与主站 102 题相同：https://leetcode-cn.com/problems/binary-tree-level-order-traversal/

*/

class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode *root) 
	{
		if (!root)  return {};
		vector<vector<int>> res;
		queue<TreeNode *> q;
		q.push(root);
		while (!q.empty())
		{
			int len = q.size();
			vector<int> temp;
			while (len)
			{
				TreeNode *node = q.front();
				q.pop();
				temp.push_back(node->val);
				if (node->left) q.push(node->left);
				if (node->right) q.push(node->right);
				--len;
			}
			res.push_back(temp);
		}
		return res;
	}
};