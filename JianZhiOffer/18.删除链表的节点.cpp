#include "header.h"

/*

给定单向链表的头指针和一个要删除的节点的值，定义一个函数删除该节点。返回删除后的链表的头节点。

示例 1:
输入: head = [4,5,1,9], val = 5
输出: [4,1,9]
解释: 给定你链表中值为 5 的第二个节点，那么在调用了你的函数之后，该链表应变为 4 -> 1 -> 9.

示例 2:
输入: head = [4,5,1,9], val = 1
输出: [4,5,9]
解释: 给定你链表中值为 1 的第三个节点，那么在调用了你的函数之后，该链表应变为 4 -> 5 -> 9.

说明：
题目保证链表中节点的值互不相同
若使用 C 或 C++ 语言，你不需要 free 或 delete 被删除的节点

*/

class Solution1 {
public:
	ListNode * deleteNode(ListNode *head, int val)
	{
		if (!head) return nullptr;
		ListNode *dummy = new ListNode(-1);
		dummy->next = head;
		ListNode *pre = dummy, *cur = head;
		while (cur)
		{
			if (cur->val == val)
			{
				pre->next = cur->next;
				//delete cur;
				break;
			}
			pre = cur;
			cur = cur->next;
		}
		ListNode *temp = dummy->next;
		//delete dummy;
		return temp;
	}
};

//Linus方法
class Solution2 {
public:
	ListNode * deleteNode(ListNode *head, int val)
	{
		if (!head) return nullptr;
		ListNode **cur = &head;
		ListNode *temp = nullptr;
		while (*cur)
		{
			if ((*cur)->val == val)
			{
				temp = *cur;
				*cur = (*cur)->next;
				//delete temp;
				break;
			}
			cur = &((*cur)->next);
		}
		return head;
	}
};
//1.首先二级指针cur指向head空间，head存放着一级指针作为头指针，所以*cur此时如果改变，head中存放的地址也改变了
//2.cur向后移动，每次移动均指向存放下一个指针的next空间
//https://leetcode-cn.com/problems/shan-chu-lian-biao-de-jie-dian-lcof/solution/linusda-lao-de-jie-jue-fang-an-by-adjwang/