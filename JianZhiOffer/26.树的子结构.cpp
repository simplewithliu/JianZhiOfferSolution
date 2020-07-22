#include "header.h"

/*

输入两棵二叉树A和B，判断B是不是A的子结构。(约定空树不是任意一个树的子结构)

B是A的子结构， 即A中有出现和B相同的结构和节点值。

例如:
给定的树 A:                给定的树 B：
        3                     4 				             				        
	   / \                   /
      4   5                 1
	 / \
    1   2                      
返回 true，因为 B 与 A 的一个子树拥有相同的结构和节点值。

示例 1：
输入：A = [1,2,3], B = [3,1]
输出：false

示例 2：
输入：A = [3,4,5,1,2], B = [4,1]
输出：true

限制：0 <= 节点个数 <= 10000

*/

class Solution {
public:
	bool isSubStructure(TreeNode *A, TreeNode *B) 
	{
		if (!A || !B) return false;
		bool res = false;
		if (A->val == B->val) res = trav(A, B);
		if (!res) res = isSubStructure(A->left, B);
		if (!res) res = isSubStructure(A->right, B);
		return res;
	}
	bool trav(TreeNode *node1, TreeNode *node2)
	{
		if (!node2) return true;
		else if (!node1) return false;
		else if (node1->val != node2->val) return false;
		else return trav(node1->left, node2->left) && trav(node1->right, node2->right);
	}
};