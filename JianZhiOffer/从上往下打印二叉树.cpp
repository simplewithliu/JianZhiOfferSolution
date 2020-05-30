#include "header.h"


struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
		val(x), left(NULL), right(NULL) {}
};


/*

从上往下打印出二叉树的每个节点，同层节点从左至右打印。

*/

class Solution1 {
public:
	vector<int> PrintFromTopToBottom(TreeNode *root)
	{
		if (!root) return{};
		queue<TreeNode *> q;
		vector<int> res;
		q.push(root);
		while (!q.empty())
		{
			TreeNode *temp = q.front();
			q.pop();
			res.push_back(temp->val);
			if (temp->left)
				q.push(temp->left);
			if (temp->right)
				q.push(temp->right);
		}
		return res;
	}
};

/*

从上到下按层打印二叉树，同一层结点从左至右输出。每一层输出一行。

*/

class Solution2 {
public:
	vector<vector<int>> Print(TreeNode *pRoot)
	{
		if (!pRoot) return{};
		vector<vector<int>> res;
		queue<TreeNode *> q;
		q.push(pRoot);
		while (!q.empty())
		{
			int len = q.size();
			vector<int> temp;
			while (len)
			{
				TreeNode *node = q.front();
				q.pop();
				temp.push_back(node->val);
				if (node->left)
					q.push(node->left);
				if (node->right)
					q.push(node->right);
				--len;
			}
			res.push_back(temp);
		}
		return res;
	}
};


/*

请实现一个函数按照之字形打印二叉树，即第一行按照从左到右的顺序打印，
第二层按照从右至左的顺序打印，
第三行按照从左到右的顺序打印，其他行以此类推。

*/

class Solution {
public:
	vector<vector<int>> Print(TreeNode *pRoot)
	{
		if (!pRoot) return {};
		stack<TreeNode *> s1;
		stack<TreeNode *> s2;
		vector<vector<int>> res;
		s1.push(pRoot);
		bool left = true;
		while (!s1.empty() || !s2.empty())
		{
			int len = left ? s1.size() : s2.size();
			stack<TreeNode *> &s = left ? s1 : s2;
			vector<int> temp;
			while (len)
			{
				TreeNode *node = s.top();
				s.pop();
				temp.push_back(node->val);
				if (left)
				{
					if (node->left)
						s2.push(node->left);
					if (node->right)
						s2.push(node->right);
				}
				else
				{
					if (node->right)
						s1.push(node->right);
					if (node->left)
						s1.push(node->left);
				}
				--len;
			}
			res.push_back(temp);
			left = !left;
		}
		return res;
	}
};
