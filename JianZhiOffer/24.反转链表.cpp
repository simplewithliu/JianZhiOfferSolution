#include "header.h"

/*

定义一个函数，输入一个链表的头节点，反转该链表并输出反转后链表的头节点。

示例:
输入: 1->2->3->4->5->NULL
输出: 5->4->3->2->1->NULL
  
限制：0 <= 节点个数 <= 5000

注意：本题与主站 206 题相同：https://leetcode-cn.com/problems/reverse-linked-list/

*/

//移动三个指针
class Solution1 {
public:
	ListNode * reverseList(ListNode *head)
	{
		if (!head) return nullptr;
		ListNode *pre = nullptr;
		ListNode *cur = head;
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
	ListNode * reverseList(ListNode *head)
	{
		if (!head || !head->next) return head;
		ListNode *preNode = reverseList(head->next);
		head->next->next = head;
		head->next = nullptr;
		return preNode;
	}
};

//区间翻转法
class Solution3 {
public:
	ListNode * reverseList(ListNode *head)
	{
		if (!head) return nullptr;
		ListNode *dummy = new ListNode(-1);
		dummy->next = head;
		reverse(dummy, nullptr);
		ListNode *newHead = dummy->next;
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