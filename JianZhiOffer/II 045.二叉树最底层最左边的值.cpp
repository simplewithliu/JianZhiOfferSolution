#include "header.h"

/*

给定一个二叉树的根节点 root，请找出该二叉树的 最底层 最左边 节点的值。
假设二叉树中至少有一个节点。

示例 1:
输入: root = [2,1,3]
输出: 1

示例 2:
输入: [1,2,3,4,null,5,6,null,null,7]
输出: 7

提示:
二叉树的节点个数的范围是 [1,10^4]
-2^31 <= Node.val <= 2^31 - 1 

注意：本题与主站 513 题相同： https://leetcode-cn.com/problems/find-bottom-left-tree-value/

*/

// BFS
class Solution1 {
public:
	int findBottomLeftValue(TreeNode *root) {
		queue<TreeNode *> q;
		int res = 0;
		q.push(root);
		while (!q.empty()) {
			TreeNode *temp = q.front();
			q.pop();
			if (temp->right) q.push(temp->right);
			if (temp->left) q.push(temp->left);
			res = temp->val;
		}
		return res;
	}
};

// DFS
class Solution2 {
private:
	void dfs(TreeNode *node, int height, int &curVal, int &curHeight) {
		if (!node) return;
		++height;
		dfs(node->left, height, curVal, curHeight);
		dfs(node->right, height, curVal, curHeight);
		if (height > curHeight) {
			curHeight = height;
			curVal = node->val;
		}
	}

public:
	int findBottomLeftValue(TreeNode *root) {
		int curVal = 0, curHeight = 0;
		dfs(root, 0, curVal, curHeight);
		return curVal;
	}
};