#include "header.h"

/*

剑指 Offer II 077. 链表排序

给你链表的头结点 head，请将其按升序排列并返回排序后的链表。

示例 1：
输入：head = [4,2,1,3]
输出：[1,2,3,4]

示例 2：
输入：head = [-1,5,3,4,0]
输出：[-1,0,3,4,5]

示例 3：
输入：head = []
输出：[]

提示：
链表中节点的数目在范围 [0, 5 * 10^4] 内
-10^5 <= Node.val <= 10^5

进阶：你可以在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序吗？

注意：本题与主站 148 题相同：https://leetcode-cn.com/problems/sort-list/

*/

// 递归法归并
class Solution1 {
public:
	ListNode *sortList(ListNode *head) {
		if (!head || !head->next) return head;
		ListNode *pre = nullptr, *slow = head, *fast = head;
		while (fast && fast->next) {
			pre = slow;
			slow = slow->next;
			fast = fast->next->next;
		}
		pre->next = nullptr;
		ListNode *l = nullptr, *r = nullptr;
		l = sortList(head);
		r = sortList(slow);
		return merge(l, r);
	}

private:
	ListNode *merge(ListNode *l, ListNode *r) {
		ListNode *dummy = new ListNode(-1);
		ListNode *temp = dummy;
		while (l && r) {
			if (l->val <= r->val) {
				temp->next = l;
				temp = temp->next;
				l = l->next;
			} else {
				temp->next = r;
				temp = temp->next;
				r = r->next;
			}
		}
		temp->next = l ? l : r;
		temp = dummy->next;
		delete dummy;
		dummy = nullptr;
		return temp;
	}
};

// 自底而上归并
class Solution2 {
public:
	ListNode *sortList(ListNode *head) {
		if (!head || !head->next) return head;
		ListNode *dummy = new ListNode(-1);
		dummy->next = head;
		ListNode *temp = head;
		int length = 0;
		while (temp) {
			++length;
			temp = temp->next;
		}
		for (int size = 1; size < length; size <<= 1) {
			ListNode *cur = dummy->next, *left = nullptr, *right = nullptr;
			ListNode *tail = dummy;
			while (cur) {
				left = cur;
				right = cut(left, size);
				cur = cut(right, size);
				tail->next = merge(left, right);
				while (tail->next) tail = tail->next;
			}
		}
		temp = dummy->next;
		delete dummy;
		dummy = nullptr;
		return temp;
	}

private:
	ListNode *cut(ListNode *head, int n) {
		ListNode *p = head;
		while (p && --n) p = p->next;
		if (!p) return nullptr;
		ListNode *post = p->next;
		p->next = nullptr;
		return post;
	}

	ListNode *merge(ListNode *l, ListNode *r) {
		ListNode *dummy = new ListNode(-1);
		ListNode *temp = dummy;
		while (l && r) {
			if (l->val <= r->val) {
				temp->next = l;
				temp = temp->next;
				l = l->next;
			} else {
				temp->next = r;
				temp = temp->next;
				r = r->next;
			}
		}
		temp->next = l ? l : r;
		temp = dummy->next;
		delete dummy;
		dummy = nullptr;
		return temp;
	}
};
// https://leetcode.cn/problems/sort-list/solutions/9014/148-pai-xu-lian-biao-bottom-to-up-o1-kong-jian-by-/
// @author https://leetcode.cn/u/ivan_allen/