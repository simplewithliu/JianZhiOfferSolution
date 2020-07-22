#include "header.h"

/*

输入两个递增排序的链表，合并这两个链表并使新链表中的节点仍然是递增排序的。

示例1：
输入：1->2->4, 1->3->4
输出：1->1->2->3->4->4

限制：0 <= 链表长度 <= 1000

注意：本题与主站 21 题相同：https://leetcode-cn.com/problems/merge-two-sorted-lists/

*/

//迭代法
class Solution1 {
public:
	ListNode * mergeTwoLists(ListNode *l1, ListNode *l2) 
	{
		if (!l1) return l2;
		if (!l2) return l1;
		ListNode *dummy = new ListNode(-1);
		ListNode *pNode1 = l1;
		ListNode *pNode2 = l2;
		ListNode *pre = dummy;
		while (pNode1&&pNode2)
		{
			if (pNode1->val <= pNode2->val)
			{
				pre->next = pNode1;
				pNode1 = pNode1->next;
			}
			else
			{
				pre->next = pNode2;
				pNode2 = pNode2->next;
			}
			pre = pre->next;
		}
		if (pNode1) pre->next = pNode1;
		else pre->next = pNode2;
		pNode1 = dummy->next;
		delete dummy;
		return pNode1;
	}
};

//递归方法
class Solution2 {
public:
	ListNode * mergeTwoLists(ListNode *l1, ListNode *l2)
	{
		if (!l1) return l2;
		else if (!l2) return l1;
		ListNode *pMergedHead = nullptr;
		if (l1->val <= l2->val)
		{
			pMergedHead = l1;
			pMergedHead->next = mergeTwoLists(l1->next, l2);
		}
		else
		{
			pMergedHead = l2;
			pMergedHead->next = mergeTwoLists(l1, l2->next);
		}
		return pMergedHead;
	}
};