#include "header.h"

/*

给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。
 
示例 1：
输入：head = [1,2,3,4,5]
输出：[5,4,3,2,1]

示例 2：
输入：head = [1,2]
输出：[2,1]
 
示例 3：
输入：head = []
输出：[]
  
提示：
链表中节点的数目范围是 [0, 5000]
-5000 <= Node.val <= 5000
   
进阶：链表可以选用迭代或递归方式完成反转。你能否用两种方法解决这道题？

*/

// 双指针迭代
class Solution1 {
public:
	ListNode *reverseList(ListNode *head) {
		if (!head) return nullptr;
		ListNode *pre = nullptr;
		ListNode *cur = head;
		while (cur) {
			ListNode *post = cur->next;
			cur->next = pre;
			pre = cur;
			cur = post;
		}
		return pre;
	}
};

// 头插法
class Solution2 {
public:
	ListNode *reverseList(ListNode *head) {
		if (!head) return nullptr;
		ListNode *dummy = new ListNode(-1);
		dummy->next = head;
		reverse(dummy, nullptr);
		return dummy->next;
	}

private:
	void reverse(ListNode *front, ListNode *behind) {
		ListNode *start = front->next;
		ListNode *then = start->next;
		ListNode *pre = front;
		while (then != behind) {
			start->next = then->next;
			then->next = pre->next;
			pre->next = then;
			then = start->next;
		}
	}
};

// 递归
class Solution3 {
public:
	ListNode *reverseList(ListNode *head) {
		if (!head || !head->next) return head;
		ListNode *preNode = reverseList(head->next);
		head->next->next = head;
		head->next = nullptr;
		return preNode;
	}
};