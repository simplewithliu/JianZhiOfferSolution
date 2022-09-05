#include "header.h"

/*

给定一个单链表 L 的头节点 head ，单链表 L 表示为：
L0 → L1 → … → Ln-1 → Ln 
请将其重新排列后变为：
L0 → Ln → L1 → Ln-1 → L2 → Ln-2 → …
不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

示例 1:
输入: head = [1,2,3,4]
输出: [1,4,2,3]
  
示例 2:
输入: head = [1,2,3,4,5]
输出: [1,5,2,4,3]

提示：
链表的长度范围为 [1, 5 * 10^4]
1 <= node.val <= 1000
    
注意：本题与主站 143 题相同：https://leetcode-cn.com/problems/reorder-list/ 

*/

class Solution {
public:
	void reorderList(ListNode *head) {
		if (!head) return;
		ListNode *slow = head, *fast = head;
		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
		}
		ListNode *middle = slow, *postmid = slow->next;
		middle->next = nullptr;
		postmid = reverse(postmid);

		ListNode *l1 = head, *l2 = postmid;
		while (l1 && l2) {
			ListNode *post1 = l1->next;
			ListNode *post2 = l2->next;
			l1->next = l2;
			l2->next = post1;
			l1 = post1;
			l2 = post2;
		}
	}

private:
	ListNode *reverse(ListNode *head) {
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