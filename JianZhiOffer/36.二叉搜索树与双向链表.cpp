#include "header.h"

/*

输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的循环双向链表。要求不能创建任何新的节点，只能调整树中节点指针的指向。
我们希望将二叉搜索树转化为双向循环链表。链表中的每个节点都有一个前驱和后继指针。对于双向循环链表，第一个节点的前驱是最后一个节点，最后一个节点的后继是第一个节点。
特别地，我们希望可以就地完成转换操作。当转化完成以后，树中节点的左指针需要指向前驱，树中节点的右指针需要指向后继。还需要返回链表中的第一个节点的指针。

注意：本题与主站 426 题相同：https://leetcode-cn.com/problems/convert-binary-search-tree-to-sorted-doubly-linked-list/
注意：此题对比原题有改动。

*/

// Definition for a Node.
class Node 
{
public:
	int val;
	Node *left;
	Node *right;

	Node() {}

	Node(int _val) 
	{
		val = _val;
		left = NULL;
		right = NULL;
	}

	Node(int _val, Node *_left, Node *_right) 
	{
		val = _val;
		left = _left;
		right = _right;
	}
};

//lastNode作为引用，始终绑定该指针变量，记住上一次中序遍历的节点
class Solution {
public:
	Node * treeToDoublyList(Node *root)
	{
		if (!root) return nullptr;
		Node *node = root;
		Node *lastNode = nullptr;
		travIn(node, lastNode);
		while (node->left) node = node->left;
		node->left = lastNode;
		lastNode->right = node;
		return node;
	}
	void travIn(Node *node, Node *&lastNode)
	{
		if (!node) return;
		travIn(node->left, lastNode);
		node->left = lastNode;
		if (lastNode) lastNode->right = node;
		lastNode = node;
		travIn(node->right, lastNode);
	}
};