#include "header.h"

/*

Trie（发音类似 "try"）或者说 前缀树 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。

这一数据结构有相当多的应用情景，例如自动补完和拼写检查。

请你实现 Trie 类：
Trie() 初始化前缀树对象。
void insert(String word) 向前缀树中插入字符串 word
boolean search(String word) 如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回false
boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix，返回 true；否则，返回false

示例：
输入
["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
[[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
输出
[null, null, true, false, true, null, true]

解释
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // 返回 True
trie.search("app");     // 返回 False
trie.startsWith("app"); // 返回 True
trie.insert("app");
trie.search("app");     // 返回 True


提示：
1 <= word.length, prefix.length <= 2000
word 和 prefix 仅由小写英文字母组成
insert、search 和 startsWith 调用次数总计不超过 3 * 10^4 次

注意：本题与主站 208 题相同：https://leetcode-cn.com/problems/implement-trie-prefix-tree/

*/

struct TrieNode {
	bool isWord;
	vector<TrieNode *> children;
	TrieNode() : isWord(false), children(26, nullptr) {}
};

class Trie {
private:
	TrieNode *root;

public:
	Trie() { root = new TrieNode(); }

	void insert(string word) {
		TrieNode *cur = root;
		int len = word.size();
		for (int i = 0; i < len; ++i) {
			char c = word[i] - 'a';
			if (!cur->children[c]) {
				cur->children[c] = new TrieNode();
			}
			cur = cur->children[c];
		}
		cur->isWord = true;
	}

	bool search(string word) {
		TrieNode *cur = root;
		int len = word.size();
		for (int i = 0; i < len; ++i) {
			char c = word[i] - 'a';
			if (!cur->children[c]) return false;
			cur = cur->children[c];
		}
		return cur->isWord;
	}

	bool startsWith(string prefix) {
		TrieNode *cur = root;
		int len = prefix.size();
		for (int i = 0; i < len; ++i) {
			char c = prefix[i] - 'a';
			if (!cur->children[c]) return false;
			cur = cur->children[c];
		}
		return true;
	}
};

// https://blog.csdn.net/m0_46202073/article/details/107253959

/**
* Your Trie object will be instantiated and called as such:
* Trie* obj = new Trie();
* obj->insert(word);
* bool param_2 = obj->search(word);
* bool param_3 = obj->startsWith(prefix);
*/

