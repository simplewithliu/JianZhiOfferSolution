#include "header.h"

/*

输入两个单调递增的链表，输出两个链表合成后的链表，
当然我们需要合成后的链表满足单调不减规则。

*/

struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
		val(x), next(NULL) {}
};

//迭代方法
class Solution1 {
public:
	ListNode * Merge(ListNode *pHead1, ListNode *pHead2)
	{
		if (!pHead1) return pHead2;
		if (!pHead2) return pHead1;
		ListNode *pre = new ListNode(-1);
		ListNode *pNode1 = pHead1;
		ListNode *pNode2 = pHead2;
		ListNode *preNode = pre;
		while (pNode1&&pNode2)
		{
			if (pNode1->val <= pNode2->val)
			{
				preNode->next = pNode1;
				pNode1 = pNode1->next;
			}
			else
			{
				preNode->next = pNode2;
				pNode2 = pNode2->next;
			}
			preNode = preNode->next;
		}
		if (pNode1)
			preNode->next = pNode1;
		else
			preNode->next = pNode2;
		pNode1 = pre->next;
		delete pre;
		return pNode1;
	}
};


//递归方法
class Solution {
public:
	ListNode * Merge(ListNode *pHead1, ListNode *pHead2)
	{
		if (pHead1 == nullptr)
			return pHead2;
		else if (pHead2 == nullptr)
			return pHead1;

		ListNode *pMergedHead = nullptr;
		if (pHead1->val<pHead2->val)
		{
			pMergedHead = pHead1;
			pMergedHead->next = Merge(pHead1->next, pHead2);
		}
		else
		{
			pMergedHead = pHead2;
			pMergedHead->next = Merge(pHead1, pHead2->next);
		}
		return pMergedHead;
	}
};