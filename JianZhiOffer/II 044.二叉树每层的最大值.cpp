#include "header.h"

/*

给定一棵二叉树的根节点 root ，请找出该二叉树中每一层的最大值。

示例1：
输入: root = [1,3,2,5,3,null,9]
输出: [1,3,9]
 
示例2：
输入: root = [1,2,3]
输出: [1,3]
  
提示：
二叉树的节点个数的范围是 [0,10^4]
-2^31 <= Node.val <= 2^31 - 1

注意：本题与主站 515 题相同： https://leetcode-cn.com/problems/find-largest-value-in-each-tree-row/

*/

// BFS
class Solution1 {
public:
	vector<int> largestValues(TreeNode *root) {
		if (!root) return{};
		vector<int> res;
		queue<TreeNode *> q;
		q.push(root);
		while (!q.empty()) {
			int sz = q.size(), maxNum = q.front()->val;
			while (sz--) {
				TreeNode *node = q.front();
				q.pop();
				maxNum = max(maxNum, node->val);
				if (node->left) q.push(node->left);
				if (node->right) q.push(node->right);
			}
			res.push_back(maxNum);
		}
		return res;
	}
};

// DFS
class Solution2 {
public:
	vector<int> largestValues(TreeNode *root) {
		if (!root) return{};
		vector<int> res;
		dfs(res, root, 0);
		return res;
	}

private:
	void dfs(vector<int> &res, TreeNode *node, int curHeight) {
		if (!node) return;
		if (res.size() == curHeight) res.push_back(node->val);
		else res[curHeight] = max(node->val, res[curHeight]);
		dfs(res, node->left, curHeight + 1);
		dfs(res, node->right, curHeight + 1);
	}
};