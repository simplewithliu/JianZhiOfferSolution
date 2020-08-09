#include "header.h"

/*

输入一棵二叉树和一个整数，打印出二叉树中节点值的和为输入整数的所有路径。从树的根节点开始往下一直到叶节点所经过的节点形成一条路径。

示例:
给定如下二叉树，以及目标和 sum = 22，

           5
          / \
         4   8
        /   / \
       11  13  4
      /  \    / \
     7    2  5   1
 
返回:
[
 [5,4,11,2],
 [5,8,4,5]
]
  
提示：
节点总数 <= 10000

注意：本题与主站 113 题相同：https://leetcode-cn.com/problems/path-sum-ii/

*/

class Solution {
public:
	vector<vector<int>> pathSum(TreeNode *root, int sum) 
	{
		if (!root) return {};
		vector<vector<int>> res;
		vector<int> v;
		helper(root, v, res, sum);
		return res;
	}
	void helper(TreeNode *node, vector<int> &v, vector<vector<int>> &res, int sum)
	{
		if (!node) return;
		v.push_back(node->val);
		if (!node->left&&!node->right&&node->val == sum) res.push_back(v);
		helper(node->left, v, res, sum - node->val);
		helper(node->right, v, res, sum - node->val);
		v.pop_back();
	}
};