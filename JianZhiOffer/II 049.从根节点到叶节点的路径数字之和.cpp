#include "header.h"

/*

给你一个二叉树的根节点 root ，树中每个节点都存放有一个 0 到 9 之间的数字。
每条从根节点到叶节点的路径都代表一个数字：
例如，从根节点到叶节点的路径 1 -> 2 -> 3 表示数字 123 。

计算从根节点到叶节点生成的所有数字之和。叶节点是指没有子节点的节点。

示例 1：
输入：root = [1,2,3]
输出：25
解释：
从根到叶子节点路径 1->2 代表数字 12
从根到叶子节点路径 1->3 代表数字 13
因此，数字总和 = 12 + 13 = 25

示例 2：
输入：root = [4,9,0,5,1]
输出：1026
解释：
从根到叶子节点路径 4->9->5 代表数字 495
从根到叶子节点路径 4->9->1 代表数字 491
从根到叶子节点路径 4->0 代表数字 40
因此，数字总和 = 495 + 491 + 40 = 1026

提示：
树中节点的数目在范围 [1, 1000] 内
0 <= Node.val <= 9
树的深度不超过 10

注意：本题与主站 129 题相同： https://leetcode-cn.com/problems/sum-root-to-leaf-numbers/

*/

// DFS
class Solution1 {
public:
	int sumNumbers(TreeNode *root) { return helper(root, 0); }

private:
	int helper(TreeNode *node, int preSum) {
		if (!node) return 0;
		int sum = preSum * 10 + node->val;
		if (!node->left && !node->right) {
			return sum;
		} else {
			return helper(node->left, sum) + helper(node->right, sum);
		}
	}
};

// BFS
class Solution2 {
public:
	int sumNumbers(TreeNode *root) {
		if (!root) return 0;
		int sum = 0;
		queue<TreeNode *> nodeq;
		queue<int> numq;
		nodeq.push(root);
		numq.push(root->val);
		while (!nodeq.empty()) {
			TreeNode *node = nodeq.front();
			int num = numq.front();
			nodeq.pop();
			numq.pop();
			TreeNode *left = node->left;
			TreeNode *right = node->right;
			if (!left && !right) {
				sum += num;
			} else {
				if (left) {
					nodeq.push(left);
					numq.push(num * 10 + left->val);
				}
				if (right) {
					nodeq.push(right);
					numq.push(num * 10 + right->val);
				}
			}
		}
		return sum;
	}
};