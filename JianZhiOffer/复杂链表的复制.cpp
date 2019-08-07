#include "header.h"

/*

输入一个复杂链表（每个节点中有节点值，以及两个指针，一个指向下一个节点，另一个特殊指针指向任意一个节点），
返回结果为复制后复杂链表的head。

*/


struct RandomListNode {
	int label;
	struct RandomListNode *next, *random;
	RandomListNode(int x) :
		label(x), next(NULL), random(NULL) {}
};

class Solution {
public:
	RandomListNode * Clone(RandomListNode *pHead)
	{
		if (!pHead) return nullptr;
		RandomListNode *node = pHead;
		RandomListNode *newnode = nullptr;
		while (node)
		{
			newnode = new RandomListNode(node->label);
			newnode->next = node->next;
			node->next = newnode;
			node = newnode->next;
		}
		node = pHead;
		newnode = pHead->next;
		while (node)
		{
			if (node->random)
				newnode->random = node->random->next;
			node = node->next->next;
			if (newnode->next)
				newnode = newnode->next->next;
		}
		node = pHead;
		newnode = pHead->next;
		RandomListNode *pNewHead = newnode;
		while (node)
		{
			node->next = node->next->next;
			if (newnode->next)
				newnode->next = newnode->next->next;
			node = node->next;
			newnode = newnode->next;
		}
		return pNewHead;
	}
};