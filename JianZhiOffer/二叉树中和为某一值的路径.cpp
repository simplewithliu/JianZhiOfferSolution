#include "header.h"

/*

输入一颗二叉树的根节点和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。
路径定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。

*/



class Solution {
public:
	vector<vector<int>> res;
	vector<vector<int>> FindPath(TreeNode* root, int expectNumber)
	{
		if (root == nullptr)
			return {};
		vector<int> vec;
		dfs(root, expectNumber, 0, vec);
		return res;
	}
	void dfs(TreeNode *root, int number, int sum, vector<int> &vec)
	{
		vec.push_back(root->val);
		sum += root->val;
		if ((!root->left) && (!root->right))
		{
			if (sum == number)
			{
				res.push_back(vec);
				return;
			}
			else
				return;
		}
		if (root->left)
		{
			dfs(root->left, number, sum, vec);
			vec.pop_back();
		}
		if (root->right)
		{
			dfs(root->right, number, sum, vec);
			vec.pop_back();
		}
	}
};
