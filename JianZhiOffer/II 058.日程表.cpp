#include "header.h"

/*

剑指 Offer II 058. 日程表

实现一个 MyCalendar 类来存放你的日程安排。如果要添加的日程安排不会造成 重复预订 ，则可以存储这个新的日程安排。
当两个日程安排有一些时间上的交叉时（例如两个日程安排都在同一时间内），就会产生 重复预订 。
日程可以用一对整数 start 和 end 表示，这里的时间是半开区间，即 [start, end), 实数 x 的范围为，  start <= x < end 。

实现 MyCalendar 类：
MyCalendar() 初始化日历对象。
boolean book(int start, int end) 如果可以将日程安排成功添加到日历中而不会导致重复预订，返回 true 。否则，返回 false 并且不要将该日程安排添加到日历中。

示例：
输入：
["MyCalendar", "book", "book", "book"]
[[], [10, 20], [15, 25], [20, 30]]
输出：
[null, true, false, true]

解释：
MyCalendar myCalendar = new MyCalendar();
myCalendar.book(10, 20); // return True
myCalendar.book(15, 25); // return False ，这个日程安排不能添加到日历中，因为时间 15 已经被另一个日程安排预订了。
myCalendar.book(20, 30); // return True ，这个日程安排可以添加到日历中，因为第一个日程安排预订的每个时间都小于 20 ，且不包含时间 20 。

提示：
0 <= start < end <= 10^9
每个测试用例，调用 book 方法的次数最多不超过 1000 次。

注意：本题与主站 729 题相同： https://leetcode-cn.com/problems/my-calendar-i/

*/

// 暴力穷举
class MyCalendar1 {
private:
	vector<pair<int, int>> booked;
public:
	MyCalendar1() {}

	bool book(int start, int end) {
		for (const auto &p : booked) {
			if (p.first < end && p.second > start) return false;
		}
		booked.push_back(pair<int, int>{start, end});
		return true;
	}
};


// 二分查找
class MyCalendar2 {
private:
	set<pair<int, int>> booked;
public:
	MyCalendar2() {

	}

	bool book(int start, int end) {
		auto it = booked.lower_bound({ end,0 });
		if (it == booked.begin() || (--it)->second <= start) {
			booked.insert({ start,end });
			return true;
		}
		return false;
	}
};

// 构造线段树
struct Node {
	Node *left;
	Node *right;
	int val;
	int add;
	Node() : left(nullptr), right(nullptr), val(0), add(0) {}
};

class MyCalendar3 {
private:
	Node *root = new Node();
	int N = (int)1E9;

private:
	void pushUp(Node *node) {
		node->val = max(node->left->val, node->right->val);
	}
	void pushDown(Node *node) {
		if (!node->left) node->left = new Node();
		if (!node->right) node->right = new Node();
		if (node->add == 0) return;
		node->left->val += node->add;
		node->right->val += node->add;
		node->left->add += node->add;
		node->right->add += node->add;
		node->add = 0;
	}

	void update(Node *node, int start, int end, int l, int r, int val) {
		if (l <= start && r >= end) {
			node->val += val;
			node->add += val;
			return;
		}
		pushDown(node);
		int mid = start + (end - start) / 2;
		if (l <= mid) update(node->left, start, mid, l, r, val);
		if (r > mid) update(node->right, mid + 1, end, l, r, val);
		pushUp(node);
	}

	int query(Node *node, int start, int end, int l, int r) {
		if (l <= start && end <= r) return node->val;
		pushDown(node);
		int mid = start + (end - start) / 2, ans = 0;
		if (l <= mid) ans = query(node->left, start, mid, l, r);
		if (r > mid) ans = max(ans, query(node->right, mid + 1, end, l, r));
		return ans;
	}

public:
	MyCalendar3() {}

	bool book(int start, int end) {
		if (query(root, 0, N, start, end - 1) != 0) return false;
		update(root, 0, N, start, end - 1, 1);
		return true;
	}
};
// https://leetcode.cn/problems/my-calendar-i/solutions/1646079/by-lfool-xvpv/
// @author https://leetcode.cn/u/lfool/

/**
* Your MyCalendar object will be instantiated and called as such:
* MyCalendar* obj = new MyCalendar();
* bool param_1 = obj->book(start,end);
*/