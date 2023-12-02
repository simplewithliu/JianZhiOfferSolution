#include "header.h"

/*

LCR 064. 实现一个魔法字典

设计一个使用单词列表进行初始化的数据结构，单词列表中的单词 互不相同

如果给出一个单词，请判定能否只将这个单词中一个字母换成另一个字母，使得所形成的新单词存在于你构建的字典中

实现 MagicDictionary 类：
MagicDictionary() 初始化对象
void buildDict(String[] dictionary) 使用字符串数组 dictionary 设定该数据结构，dictionary 中的字符串互不相同
bool search(String searchWord) 给定一个字符串 searchWord，判定能否只将字符串中 一个 字母换成另一个字母，使得所形成的新字符串能够与字典中的任一字符串匹配。
如果可以，返回 true；否则返回 false

示例：
输入
["MagicDictionary", "buildDict", "search", "search", "search", "search"]
[[], [["hello", "leetcode"]], ["hello"], ["hhllo"], ["hell"], ["leetcoded"]]
输出
[null, null, false, true, false, false]
解释
MagicDictionary magicDictionary = new MagicDictionary();
magicDictionary.buildDict(["hello", "leetcode"]);
magicDictionary.search("hello"); // 返回 False
magicDictionary.search("hhllo"); // 将第二个 'h' 替换为 'e' 可以匹配 "hello" ，所以返回 True
magicDictionary.search("hell"); // 返回 False
magicDictionary.search("leetcoded"); // 返回 False

提示：
1 <= dictionary.length <= 100
1 <= dictionary[i].length <= 100
dictionary[i] 仅由小写英文字母组成
dictionary 中的所有字符串 互不相同
1 <= searchWord.length <= 100
searchWord 仅由小写英文字母组成
buildDict 仅在 search 之前调用一次
最多调用 100 次 search

注意：本题与主站 676 题相同： https://leetcode-cn.com/problems/implement-magic-dictionary/


*/


struct TrieNode {
	bool isWord;
	vector<TrieNode *> children;
	TrieNode() : isWord(false), children(26, nullptr) {}
};

class Trie {
public:
	TrieNode *root;

	Trie() { root = new TrieNode(); }

	void insert(const string &word) {
		TrieNode *cur = root;
		for (const auto &c : word) {
			char i = c - 'a';
			if (!cur->children[i]) {
				cur->children[i] = new TrieNode();
			}
			cur = cur->children[i];
		}
		cur->isWord = true;
	}

	bool search(const string &word, int idx, TrieNode *cur, int limit) {
		if (limit < 0) return false;
		if (idx == word.size()) return cur->isWord && limit == 0;
		int i = word[idx] - 'a';
		for (int j = 0; j < 26; ++j) {
			if (!cur->children[j]) continue;
			if (search(word, idx + 1, cur->children[j],
				i == j ? limit : limit - 1)) {
				return true;
			}
		}
		return false;
	}
};

class MagicDictionary {
private:
	Trie t;

public:
	MagicDictionary() {}

	void buildDict(vector<string> dictionary) {
		for (const auto &d : dictionary) t.insert(d);
	}

	bool search(string searchWord) {
		return t.search(searchWord, 0, t.root, 1);
	}
};

/**
* Your MagicDictionary object will be instantiated and called as such:
* MagicDictionary* obj = new MagicDictionary();
* obj->buildDict(dictionary);
* bool param_2 = obj->search(searchWord);
*/
