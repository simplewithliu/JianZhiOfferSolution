#include "header.h"

/*

剑指 Offer II 078. 合并排序链表

给你一个链表数组，每个链表都已经按升序排列。请你将所有链表合并到一个升序链表中，返回合并后的链表。

示例 1：
输入：lists = [[1,4,5],[1,3,4],[2,6]]
输出：[1,1,2,3,4,4,5,6]
解释：链表数组如下：
[
1->4->5,
1->3->4,
2->6
]
将它们合并到一个有序链表中得到。
1->1->2->3->4->4->5->6

示例 2：
输入：lists = []
输出：[]

示例 3：
输入：lists = [[]]
输出：[]

提示：
k == lists.length
0 <= k <= 10^4
0 <= lists[i].length <= 500
-10^4 <= lists[i][j] <= 10^4
lists[i] 按 升序 排列
lists[i].length 的总和不超过 10^4

注意：本题与主站 23 题相同： https://leetcode-cn.com/problems/merge-k-sorted-lists/

*/

// 分治
class Solution1 {
public:
	ListNode *mergeKLists(vector<ListNode *> &lists) {
		if (lists.empty()) return nullptr;
		return helper(lists, 0, lists.size() - 1);
	}

private:
	ListNode *helper(vector<ListNode *> &lists, int l, int r) {
		if (l == r) return lists[l];
		int mi = l + (r - l) / 2;
		return merge(helper(lists, l, mi), helper(lists, mi + 1, r));
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

// 优先级队列
class Solution2 {
public:
	ListNode *mergeKLists(vector<ListNode *> &lists) {
		priority_queue<ListNode *, vector<ListNode *>, decltype(compare) *> pq(compare);
		ListNode *dummy = new ListNode(-1);
		ListNode *cur = dummy;
		for (auto list : lists) {
			if (list) pq.push(list);
		}
		while (!pq.empty()) {
			cur->next = pq.top();
			pq.pop();
			cur = cur->next;
			if (cur->next) pq.push(cur->next);
		}
		cur = dummy->next;
		delete dummy;
		dummy = nullptr;
		return cur;
	}

private:
	static bool compare(ListNode *node1, ListNode *node2) {
		return node1->val > node2->val;
	}
};
// https://leetcode.cn/problems/merge-k-sorted-lists/solutions/219756/he-bing-kge-pai-xu-lian-biao-by-leetcode-solutio-2/comments/1383863
// @Comments 优先队列为什么不全部放进去而是只放k个？求大佬解答
// 因为只是从k个链表的最前端比较，和后面的没有关系，所以不需要放入所有，但是由于后面的比前面大，所以全部放入也可以。
// 不过空间复杂度上升，同时由于队列中元素的增多，小顶堆的调整也会花更多的时间。