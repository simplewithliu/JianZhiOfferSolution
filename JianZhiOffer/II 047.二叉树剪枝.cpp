#include "header.h"

/*

给你二叉树的根结点root，此外树的每个结点的值要么是0，要么是1。
返回移除了所有不包含1的子树的原二叉树。
节点node的子树为node本身加上所有node的后代。

示例 1：
输入：root = [1,null,0,0,1]
输出：[1,null,0,null,1]
解释：
只有红色节点满足条件“所有不包含 1 的子树”。右图为返回的答案。

示例 2：
输入：root = [1,0,1,0,0,0,1]
输出：[1,null,1,null,1]

示例 3：
输入：root = [1,1,0,1,1,0,1,0]
输出：[1,1,0,1,1,null,1]

提示：
树中节点的数目在范围 [1, 200] 内
Node.val 为 0 或 1

注意：本题与主站 814 题相同：https://leetcode-cn.com/problems/binary-tree-pruning/

*/

class Solution {
public:
	TreeNode *pruneTree(TreeNode *root) {
		if (!root) return nullptr;
		root->left = pruneTree(root->left);
		root->right = pruneTree(root->right);
		if (!root->left && !root->right && !root->val) return nullptr;
		return root;
	}
};

/**

问题本身并不困难，但是其中的一个提交中，因为对不使用的节点执行了delete导致报错：

https://leetcode.cn/problems/pOCWxh/submissions/381722333/

当删除delete语句后，提交便通过了，对于节点不能delete，官方解答中有评论给出观点：

https://leetcode.cn/problems/binary-tree-pruning/solutions/1683846/er-cha-shu-jian-zhi-by-leetcode-solution-k336/comments/1663951

也就是说内存不是我们自己分配的，在只是拿到一个指针的情况下是不能去贸然释放它的。同时查找一些资料如下：

[1] https://www.zhihu.com/question/509145076

[2] https://www.zhihu.com/question/25542360

[3] https://segmentfault.com/q/1010000009987587

*/
