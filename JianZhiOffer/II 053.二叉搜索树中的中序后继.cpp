#include "header.h"

/*

给定一棵二叉搜索树和其中的一个节点 p ，找到该节点在树中的中序后继。如果节点没有中序后继，请返回 null 。

节点p的后继是值比p.val大的节点中键值最小的节点，即按中序遍历的顺序节点p的下一个节点。

示例 1：
输入：root = [2,1,3], p = 1
输出：2
解释：这里 1 的中序后继是 2。请注意 p 和返回值都应是 TreeNode 类型。

示例 2：
输入：root = [5,3,6,2,4,null,null,1], p = 6
输出：null
解释：因为给出的节点没有中序后继，所以答案就返回 null 了。

提示：
树中节点的数目在范围 [1, 10^4] 内。
-10^5 <= Node.val <= 10^5
树中各节点的值均保证唯一。

注意：本题与主站 285 题相同： https://leetcode-cn.com/problems/inorder-successor-in-bst/

*/

class Solution1 {
public:
	TreeNode *inorderSuccessor(TreeNode *root, TreeNode *p) {
		TreeNode *pre = nullptr;
		return inorder(root, p, pre);
	}

private:
	TreeNode *inorder(TreeNode *node, TreeNode *p, TreeNode *&pre) {
		if (!node) return nullptr;
		TreeNode *left = inorder(node->left, p, pre);
		if (left) return left;
		if (pre == p) return node;
		pre = node;
		return inorder(node->right, p, pre);
	}
};

class Solution2 {
public:
	TreeNode *inorderSuccessor(TreeNode *root, TreeNode *p) {
		if (!root) return nullptr;
		if (root->val <= p->val) return inorderSuccessor(root->right, p);
		TreeNode *left = inorderSuccessor(root->left, p);
		return left ? left : root;
	}
};