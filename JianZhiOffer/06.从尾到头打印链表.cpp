#include "header.h"

/*

输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）。

示例 1：
输入：head = [1,3,2]
输出：[2,3,1]

限制：0 <= 链表长度 <= 10000

*/

class Solution1 {
public:
	vector<int> reversePrint(ListNode *head) 
	{
		if (!head) return {};
		vector<int> res;
		stack<int> s;
		ListNode *node = head;
		while (node)
		{
			s.push(node->val);
			node = node->next;
		}
		while (!s.empty())
		{
			res.push_back(s.top());
			s.pop();
		}
		return res;
	}
};

class Solution2 {
public:
	vector<int> reversePrint(ListNode *head) 
	{
		vector<int> res;
		helper(head, res);
		return res;
	}
	void helper(ListNode *node,vector<int> &res)
	{
		if (!node) return;
		helper(node->next, res);
		res.push_back(node->val);
	}
};