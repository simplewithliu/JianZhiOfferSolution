#include "header.h"

/*

给你两个非空链表来代表两个非负整数。数字最高位位于链表开始位置。它们的每个节点只存储一位数字。将这两数相加会返回一个新的链表。
你可以假设除了数字 0 之外，这两个数字都不会以零开头。

示例1：
输入：l1 = [7,2,4,3], l2 = [5,6,4]
输出：[7,8,0,7]

示例2：
输入：l1 = [2,4,3], l2 = [5,6,4]
输出：[8,0,7]

示例3：
输入：l1 = [0], l2 = [0]
输出：[0]
  
提示：
链表的长度范围为 [1, 100]
0 <= node.val <= 9
输入数据保证链表代表的数字无前导 0
   
进阶：如果输入链表不能翻转该如何解决？

*/

class Solution {
public:
	ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
		stack<int> s1, s2;
		while (l1) {
			s1.push(l1->val);
			l1 = l1->next;
		}
		while (l2) {
			s2.push(l2->val);
			l2 = l2->next;
		}
		int carry = 0;
		ListNode *node = nullptr;
		while (!s1.empty() || !s2.empty() || carry != 0) {
			int a = s1.empty() ? 0 : s1.top();
			int b = s2.empty() ? 0 : s2.top();
			if (!s1.empty()) s1.pop();
			if (!s2.empty()) s2.pop();
			int cur = a + b + carry;
			carry = cur / 10;
			cur = cur % 10;
			ListNode *temp = new ListNode(cur);
			temp->next = node;
			node = temp;
		}
		return node;
	}
};
