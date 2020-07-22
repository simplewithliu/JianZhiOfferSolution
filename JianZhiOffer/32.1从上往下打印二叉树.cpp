#include "header.h"

/*

从上到下打印出二叉树的每个节点，同一层的节点按照从左到右的顺序打印。

例如:
给定二叉树: [3,9,20,null,null,15,7],

      3
     / \
    9  20
   / \
  15  7

返回：[3,9,20,15,7]
  
提示：节点总数 <= 1000

*/

class Solution {
public:
	vector<int> levelOrder(TreeNode *root) 
	{
		if (!root) return {};
		queue<TreeNode *> q;
		vector<int> res;
		q.push(root);
		while (!q.empty())
		{
			TreeNode *temp = q.front();
			q.pop();
			res.push_back(temp->val);
			if (temp->left) q.push(temp->left);
			if (temp->right) q.push(temp->right);
		}
		return res;
	}
};