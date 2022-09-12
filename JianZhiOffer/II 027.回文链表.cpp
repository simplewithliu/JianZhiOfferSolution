#include "header.h"

/*

给你一个单链表的头节点 head，请你判断该链表是否为回文链表。
如果是，返回 true; 否则，返回 false。

示例 1：
输入：head = [1,2,2,1]
输出：true

示例 2：
输入：head = [1,2]
输出：false

提示：
链表中节点数目在范围[1, 10^5] 内
0 <= Node.val <= 9
   
进阶：你能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？

注意：本题与主站 234 题相同：https://leetcode-cn.com/problems/palindrome-linked-list/

*/

// 递归
class Solution1 {
private:
	ListNode *frontPointer = nullptr;

public:
	bool isPalindrome(ListNode *head) {
		frontPointer = head;
		return recursiveCheck(head);
	}

private:
	bool recursiveCheck(ListNode *node) {
		if (node) {
			if (!recursiveCheck(node->next)) return false;
			if (frontPointer->val != node->val) return false;
			frontPointer = frontPointer->next;
		}
		return true;
	}
};

// 快慢指针
class Solution2 {
public:
	bool isPalindrome(ListNode *head) {
		if (!head) return true;
		ListNode *slow = head, *fast = head, *pre = slow;
		while (fast && fast->next) {
			pre = slow;
			slow = slow->next;
			fast = fast->next->next;
		}
		pre->next = nullptr;
		ListNode *secondHead = reverse(slow), *firstHead = head;
		while (firstHead) {
			if (firstHead->val != secondHead->val) return false;
			firstHead = firstHead->next;
			secondHead = secondHead->next;
		}
		return true;
	}

private:
	ListNode *reverse(ListNode *head) {
		ListNode *pre = nullptr, *cur = head;
		while (cur) {
			ListNode *post = cur->next;
			cur->next = pre;
			pre = cur;
			cur = post;
		}
		return pre;
	}
};

