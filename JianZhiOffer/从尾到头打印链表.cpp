#include "header.h"

/*

输入一个链表，按链表值从尾到头的顺序返回一个ArrayList,不要破坏链表结构。

*/

struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
		val(x), next(NULL) {}
};

class Solution {
public:
	vector<int> printListFromTailToHead(ListNode *head)
	{
		if (!head) return{};
		vector<int> res;
		stack<int> s;
		ListNode *pNode = head;
		while (pNode)
		{
			s.push(pNode->val);
			pNode = pNode->next;
		}
		while (!s.empty())
		{
			res.push_back(s.top());
			s.pop();
		}
		return res;
	}
};