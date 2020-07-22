#include "header.h"

/*

请实现一个函数按照之字形顺序打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右到左的顺序打印，第三行再按照从左到右的顺序打印，其他行以此类推。

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
  [20,9],
  [15,7]
]
 
提示：节点总数 <= 1000

*/

class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode *root) 
	{
		if (!root) return {};
		vector<vector<int>> res;
		queue<TreeNode *> q;
		q.push(root);
		bool leftToRight = true;
		while (!q.empty())
		{
			int len = q.size();
			vector<int> vec(len);
			for (int i = 0; i < len; ++i)
			{
				TreeNode *temp = q.front();
				q.pop();
				int index = leftToRight ? i : len - i - 1;
				vec[index] = temp->val;
				if (temp->left) q.push(temp->left);
				if (temp->right) q.push(temp->right);
			}
			leftToRight = !leftToRight;
			res.push_back(vec);
		}
		return res;
	}
};