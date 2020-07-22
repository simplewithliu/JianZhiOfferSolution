#include "header.h"

/*
请完成一个函数，输入一个二叉树，该函数输出它的镜像。

输入：                   镜像输出：
       4                         4
     /   \                     /   \
    2     7                   7     2
   / \   / \                 / \   / \
  1   3 6   9               9   6 3   1

示例 1：
输入：root = [4,2,7,1,3,6,9]
输出：[4,7,2,9,6,3,1]
	
限制：
0 <= 节点个数 <= 1000
注意：本题与主站 226 题相同：https://leetcode-cn.com/problems/invert-binary-tree/

*/

class Solution {
public:
	TreeNode * mirrorTree(TreeNode *root) 
	{
		if (!root) return nullptr;
		swap(root->left, root->right);
		mirrorTree(root->left);
		mirrorTree(root->right);
		return root;
	}
};