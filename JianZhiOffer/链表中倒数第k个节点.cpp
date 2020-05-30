#include "header.h"

/*

输入一个链表，输出该链表中倒数第k个结点。

*/

struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
		val(x), next(NULL) {}
};

class Solution {
public:
	ListNode * FindKthToTail(ListNode *pListHead, unsigned int k)
	{
		if (!pListHead || k<0) return nullptr;
		ListNode *ahead = pListHead;
		while (k > 0)
		{
			if (!ahead) return nullptr;
			ahead = ahead->next;
			--k;
		}
		ListNode *behind = pListHead;
		while (ahead)
		{
			behind = behind->next;
			ahead = ahead->next;
		}
		return behind;
	}
};