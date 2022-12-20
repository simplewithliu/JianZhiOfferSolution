#include "header.h"

/*

给定一个二叉搜索树 root 和一个目标结果 k，如果二叉搜索树中存在两个元素且它们的和等于给定的目标结果，则返回 true。

示例 1：
输入: root = [5,3,6,2,4,null,7], k = 9
输出: true

示例 2：
输入: root = [5,3,6,2,4,null,7], k = 28
输出: false

提示:
二叉树的节点个数的范围是[1, 10^4]
-10^4 <= Node.val <= 10^4
题目数据保证，输入的 root 是一棵 有效 的二叉搜索树
-10^5 <= k <= 10^5

注意：本题与主站 653 题相同： https://leetcode-cn.com/problems/two-sum-iv-input-is-a-bst/

*/

class Solution1 {
private:
	unordered_set<int> hashSet;

public:
	bool findTarget(TreeNode *root, int k) {
		if (!root) return false;
		if (hashSet.count(root->val)) return true;
		hashSet.insert(k - root->val);
		return findTarget(root->left, k) || findTarget(root->right, k);
	}
};

// 利用BST性质，双指针
class Solution2 {
private:
	vector<int> v;
	void inorder(TreeNode *node) {
		if (!node) return;
		inorder(node->left);
		v.push_back(node->val);
		inorder(node->right);
	}

public:
	bool findTarget(TreeNode *root, int k) {
		inorder(root);
		int left = 0, right = v.size() - 1;
		while (left < right) {
			if (v[left] + v[right] == k) {
				return true;
			} else if (v[left] + v[right] < k) {
				++left;
			} else {
				--right;
			}
		}
		return false;
	}
};