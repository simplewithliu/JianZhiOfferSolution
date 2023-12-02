#include "header.h"

/*

LCR 065. 单词的压缩编码

单词数组words的有效编码由任意助记字符串 s 和下标数组 indices 组成，且满足：
words.length == indices.length
助记字符串 s 以 '#' 字符结尾
对于每个下标 indices[i]，s 的一个从 indices[i] 开始、到下一个 '#' 字符结束（但不包括 '#'）的子字符串恰好与words[i]相等

给你一个单词数组 words ，返回成功对 words 进行编码的最小助记字符串 s 的长度

示例 1：
输入：words = ["time", "me", "bell"]
输出：10
解释：一组有效编码为 s = "time#bell#" 和 indices = [0, 2, 5] 。
words[0] = "time" ，s 开始于 indices[0] = 0 到下一个 '#' 结束的子字符串，如加粗部分所示 "time#bell#"
words[1] = "me" ，s 开始于 indices[1] = 2 到下一个 '#' 结束的子字符串，如加粗部分所示 "time#bell#"
words[2] = "bell" ，s 开始于 indices[2] = 5 到下一个 '#' 结束的子字符串，如加粗部分所示 "time#bell#"

示例 2：
输入：words = ["t"]
输出：2
解释：一组有效编码为 s = "t#" 和 indices = [0]

提示：
1 <= words.length <= 2000
1 <= words[i].length <= 7
words[i] 仅由小写字母组成


注意：本题与主站 820 题相同： https://leetcode-cn.com/problems/short-encoding-of-words/

*/


// DFS遍历节点

struct TrieNode1 {
	int childNum;
	vector<TrieNode1 *> children;
	TrieNode1() : childNum(0), children(26, nullptr) {}
};

class Trie1 {
public:
	TrieNode1 *root;
	int total = 0;

	Trie1() { root = new TrieNode1(); }

	void insert(const string &word) {
		TrieNode1 *cur = root;
		for (int i = word.size() - 1; i >= 0; --i) {
			char id = word[i] - 'a';
			if (!cur->children[id]) {
				cur->children[id] = new TrieNode1();
				++cur->childNum;
			}
			cur = cur->children[id];
		}
	}

	void searchLeaf(TrieNode1 *cur, int len) {
		if (cur->childNum == 0) total += len;
		for (const auto &child : cur->children) {
			if (child) searchLeaf(child, len + 1);
		}
	}
};

class Solution {
public:
	int minimumLengthEncoding(vector<string> &words) {
		Trie1 t;
		for (const auto &word : words) t.insert(word);
		t.searchLeaf(t.root, 1);
		return t.total;
	}
};



// 哈希表记录节点

struct TrieNode2 {
	int childNum;
	vector<TrieNode2 *> children;
	TrieNode2() : childNum(0), children(26, nullptr) {}
};

class Trie2 {
public:
	TrieNode2 *root;

	Trie2() { root = new TrieNode2(); }

	TrieNode2 *insert(const string &word) {
		TrieNode2 *cur = root;
		for (int i = word.size() - 1; i >= 0; --i) {
			char id = word[i] - 'a';
			if (!cur->children[id]) {
				cur->children[id] = new TrieNode2();
				++cur->childNum;
			}
			cur = cur->children[id];
		}
		return cur;
	}
};

class Solution2 {
public:
	int minimumLengthEncoding(vector<string> &words) {
		Trie2 t;
		unordered_map<TrieNode2 *, int> nodes_map;
		for (int i = 0; i < words.size(); ++i) {
			TrieNode2 *cur = t.insert(words[i]);
			nodes_map[cur] = i;
		}
		int res = 0;
		for (const auto &p : nodes_map) {
			if (p.first->childNum == 0) res += words[p.second].size() + 1;
		}
		return res;
	}
};
