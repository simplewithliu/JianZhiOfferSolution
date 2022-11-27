#include "header.h"

/*

给定一个二叉树的根节点 root ，和一个整数 targetSum ，求该二叉树里节点值之和等于 targetSum 的路径的数目。
路径不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。

示例 1：
输入：root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
输出：3
解释：和等于 8 的路径有 3 条。

示例 2：
输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
输出：3

提示:
二叉树的节点个数的范围是 [0,1000]
-109 <= Node.val <= 10^9
-1000 <= targetSum <= 1000

注意：本题与主站 437 题相同：https://leetcode-cn.com/problems/path-sum-iii/

*/

class Solution1 {
public:
	int pathSum(TreeNode *root, int targetSum) {
		if (!root) return 0;
		return helper(root, targetSum) + pathSum(root->left, targetSum) +
			pathSum(root->right, targetSum);
	}

private:
	int helper(TreeNode *node, int targetSum) {
		if (!node) return 0;
		int ret = 0;
		if (node->val == targetSum) ++ret;
		ret += helper(node->left, targetSum - node->val);
		ret += helper(node->right, targetSum - node->val);
		return ret;
	}
};

class Solution2 {
public:
	int pathSum(TreeNode *root, int targetSum) {
		if (!root) return 0;
		unordered_map<long long, int> prefix;
		prefix[0] = 1;
		return helper(root, targetSum, 0, prefix);
	}

private:
	int helper(TreeNode *node, int targetSum, long long cur,
		unordered_map<long long, int> &prefix) {
		if (!node) return 0;
		int ret = 0;
		cur += node->val;
		if (prefix.count(cur - targetSum)) ret = prefix[cur - targetSum];
		++prefix[cur];
		ret += helper(node->left, targetSum, cur, prefix);
		ret += helper(node->right, targetSum, cur, prefix);
		--prefix[cur];
		return ret;
	}
};
