#include "header.h"

/*

请你设计并实现一个满足 LRU(最近最少使用)缓存 约束的数据结构。
实现 LRUCache 类：
LRUCache(int capacity) 以正整数作为容量 capacity初始化LRU缓存
int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回-1。
void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值value；如果不存在，则向缓存中插入该组 key-value。如果插入操作导致关键字数量超过capacity，则应该逐出最久未使用的关键字。

函数 get 和 put 必须以O(1)的平均时间复杂度运行。

示例：

输入
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]

输出
[null, null, null, 1, null, -1, null, -1, 3, 4]

解释
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // 缓存是 {1=1}
lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
lRUCache.get(1);    // 返回 1
lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
lRUCache.get(2);    // 返回 -1 (未找到)
lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
lRUCache.get(1);    // 返回 -1 (未找到)
lRUCache.get(3);    // 返回 3
lRUCache.get(4);    // 返回 4
  
提示：
1 <= capacity <= 3000
0 <= key <= 10000
0 <= value <= 10^5
最多调用 2 * 10^5 次 get 和 put

*/

struct Node {
	int mKey;
	int mVal;
	Node *prev;
	Node *next;
	Node() : mKey(0), mVal(0), prev(nullptr), next(nullptr) {}
	Node(int k, int v) : mKey(k), mVal(v), prev(nullptr), next(nullptr) {}
};

class DLink {
private:
	Node *head;
	Node *tail;
	int size;

public:
	DLink() : head(new Node(0, 0)), tail(new Node(0, 0)), size(0) {
		head->next = tail;
		tail->prev = head;
	}

	void addLast(Node *node) {
		node->prev = tail->prev;
		node->next = tail;
		tail->prev->next = node;
		tail->prev = node;
		++size;
	}

	void remove(Node *node) {
		node->prev->next = node->next;
		node->next->prev = node->prev;
		--size;
	}

	Node *removeFirst() {
		if (head->next == tail) return nullptr;
		Node *first = head->next;
		remove(first);
		return first;
	}

	int getSize() { return size; }
};

class LRUCache {
private:
	unordered_map<int, Node *> m;
	DLink dlink;
	int cap;

private:
	void makeRecent(int key, int val) {
		Node *node = m[key];
		node->mVal = val;
		dlink.remove(node);
		dlink.addLast(node);
	}
	void addRecent(int key, int val) {
		Node *node = new Node(key, val);
		dlink.addLast(node);
		m[key] = node;
	}
	void removeLRU() {
		Node *node = dlink.removeFirst();
		m.erase(node->mKey);
		delete node;
	}

public:
	LRUCache(int capacity) { cap = capacity; }

	int get(int key) {
		if (!m.count(key)) return -1;
		int val = m[key]->mVal;
		makeRecent(key, val);
		return val;
	}

	void put(int key, int value) {
		if (m.count(key)) {
			makeRecent(key, value);
		} else {
			if (dlink.getSize() == cap) removeLRU();
			addRecent(key, value);
		}
	}
};

/**
* Your LRUCache object will be instantiated and called as such:
* LRUCache* obj = new LRUCache(capacity);
* int param_1 = obj->get(key);
* obj->put(key,value);
*/