#include "header.h"

/*

输入一个链表，反转链表后，输出新链表的表头。

*/


//移动三个指针
class Solution1 {
public:
	ListNode * ReverseList(ListNode *pHead)
	{
		if (!pHead) return nullptr;
		ListNode *pre = nullptr;
		ListNode *cur = pHead;
		while (cur)
		{
			ListNode *post = cur->next;
			cur->next = pre;
			pre = cur;
			cur = post;
		}
		return pre;
	}
};


//递归
class Solution2 {
public:
	ListNode * ReverseList(ListNode *pHead)
	{
		if (!pHead || !pHead->next)
			return pHead;
		ListNode *preNode = ReverseList(pHead->next);
		pHead->next->next = pHead;
		pHead->next = nullptr;
		return preNode;
	}
};


//区间翻转法
class Solution3 {
public:
	ListNode *ReverseList(ListNode *pHead)
	{
		if (!pHead) return nullptr;
		ListNode *dummy = new ListNode(-1);
		dummy->next = pHead;
		reverse(dummy, nullptr);
		ListNode *newHead = dummy->next;
		delete dummy;
		return newHead;
	}
	void reverse(ListNode *ahead, ListNode *behind)
	{
		ListNode *start = ahead->next;
		ListNode *then = start->next;
		ListNode *pre = ahead;
		while (then != behind)
		{
			start->next = then->next;
			then->next = pre->next;
			pre->next = then;
			then = start->next;
		}
	}
};