#include "header.h"

/*

LCR 066. 键值映射

设计一个 map，满足以下几点：
字符串表示键，整数表示值
返回具有前缀等于给定字符串的键的值的总和

实现一个 MapSum 类：

MapSum() 初始化 MapSum 对象

void insert(String key, int val) 插入 key-val 键值对，字符串表示键 key，整数表示值 val
如果键 key 已经存在，那么原来的键值对 key-value 将被替代成新的键值对

int sum(string prefix) 返回所有以该前缀 prefix 开头的键 key 的值的总和

示例 1：
输入：
["MapSum", "insert", "sum", "insert", "sum"]
[[], ["apple", 3], ["ap"], ["app", 2], ["ap"]]
输出：
[null, null, 3, null, 5]
解释：
MapSum mapSum = new MapSum();
mapSum.insert("apple", 3);
mapSum.sum("ap");           // 返回 3 (apple = 3)
mapSum.insert("app", 2);
mapSum.sum("ap");           // 返回 5 (apple + app = 3 + 2 = 5)

提示：
1 <= key.length, prefix.length <= 50
key 和 prefix 仅由小写英文字母组成
1 <= val <= 1000
最多调用 50 次 insert 和 sum

注意：本题与主站 677 题相同： https://leetcode-cn.com/problems/map-sum-pairs/

*/

// DFS遍历节点

struct TrieNode1 {
	int val;
	vector<TrieNode1 *> children;
	TrieNode1() : val(0), children(26, nullptr) {}
};

class Trie1 {
private:
	TrieNode1 *root;

public:
	Trie1() { root = new TrieNode1(); }

	void insert(const string &word, int val) {
		TrieNode1 *cur = root;
		for (const auto &c : word) {
			char i = c - 'a';
			if (!cur->children[i]) {
				cur->children[i] = new TrieNode1();
			}
			cur = cur->children[i];
		}
		cur->val = val;
	}

	TrieNode1 *searchPrefix(const string &word) {
		TrieNode1 *cur = root;
		for (const auto &c : word) {
			char i = c - 'a';
			cur = cur->children[i];
			if (!cur) return nullptr;
		}
		return cur;
	}

	int searchLeaf(TrieNode1 *node) {
		if (!node) return 0;
		int res = node->val;
		for (const auto &child : node->children) {
			res += searchLeaf(child);
		}
		return res;
	}

};

class MapSum1 {
private:
	Trie1 t;

public:
	MapSum1() {}

	void insert(string key, int val) { t.insert(key, val); }

	int sum(string prefix) {
		TrieNode1 *cur = t.searchPrefix(prefix);
		return cur == nullptr ? 0 : t.searchLeaf(cur);
	}
};



// 哈希表记录节点

struct TrieNode2 {
	int val;
	vector<TrieNode2 *> children;
	TrieNode2() : val(0), children(26, nullptr) {}
};

class Trie2 {
private:
	TrieNode2 *root;
	unordered_map<string, int> m;

public:
	Trie2() { root = new TrieNode2(); }

	void insert(const string &word, int val) {
		TrieNode2 *cur = root;
		int tmp = val;
		if (m.count(word)) tmp -= m[word];
		m[word] = val;
		for (const auto &c : word) {
			char i = c - 'a';
			if (!cur->children[i]) {
				cur->children[i] = new TrieNode2();
			}
			cur = cur->children[i];
			cur->val += tmp;
		}
	}

	int searchPrefixVal(const string &word) {
		TrieNode2 *cur = root;
		for (const auto &c : word) {
			char i = c - 'a';
			cur = cur->children[i];
			if (!cur) return 0;
		}
		return cur->val;
	}
};

class MapSum2 {
private:
	Trie2 t;

public:
	MapSum2() {}

	void insert(string key, int val) { t.insert(key, val); }

	int sum(string prefix) { return t.searchPrefixVal(prefix); }
};

/**
* Your MapSum object will be instantiated and called as such:
* MapSum* obj = new MapSum();
* obj->insert(key,val);
* int param_2 = obj->sum(prefix);
*/
