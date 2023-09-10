#include "header.h"

/*

LCR 114.火星词典

现有一种使用英语字母的外星文语言，这门语言的字母顺序与英语顺序不同

给定一个字符串列表 words，作为这门语言的词典，words 中的字符串已经按这门新语言的字母顺序进行了排序

请你根据该词典还原出此语言中已知的字母顺序，并按字母递增顺序排列，若不存在合法字母顺序，返回 ""

若存在多种可能的合法字母顺序，返回其中 任意一种 顺序即可

字符串 s 字典顺序小于 字符串 t 有两种情况：
在第一个不同字母处，如果 s 中的字母在这门外星语言的字母顺序中位于 t 中字母之前，那么 s 的字典顺序小于 t
如果前面 min(s.length, t.length) 字母都相同，那么 s.length < t.length 时，s 的字典顺序也小于 t

示例 1：
输入：words = ["wrt","wrf","er","ett","rftt"]
输出："wertf"

示例 2：
输入：words = ["z","x"]
输出："zx"

示例 3：
输入：words = ["z","x","z"]
输出：""
解释：不存在合法字母顺序，因此返回 ""

提示：
1 <= words.length <= 100
1 <= words[i].length <= 100
words[i] 仅由小写英文字母组成

注意：本题与主站 269 题相同：https://leetcode-cn.com/problems/alien-dictionary/

*/

// DFS + 拓扑排序
class Solution1 {
private:
	const char VISITING = 1, VISITED = 2;
	unordered_map<char, vector<char>> edges;
	unordered_map<char, char> states;
	bool valid = true;
	string order;
	int index = 0;

private:
	void addEdge(const string &str1, const string &str2) {
		int len1 = str1.size(), len2 = str2.size();
		int len = min(len1, len2);
		int idx = 0;
		while (idx < len) {
			char c1 = str1[idx], c2 = str2[idx];
			if (c1 != c2) {
				edges[c1].emplace_back(c2);
				return;
			}
			++idx;
		}
		if (idx == len && len1 > len2) valid = false;
	}
	void dfs(char c) {
		states[c] = VISITING;
		for (const auto &v : edges[c]) {
			if (!states.count(v)) {
				dfs(v);
				if (!valid) return;
			} else if (states[v] == VISITING) {
				valid = false;
				return;
			}
		}
		states[c] = VISITED;
		order[index] = c;
		--index;
	}

public:
	string alienOrder(vector<string> &words) {
		int len = words.size();
		for (const auto &word : words) {
			int wordLen = word.size();
			for (int i = 0; i < wordLen; ++i) {
				char c = word[i];
				if (!edges.count(c)) edges[c] = vector<char>();
			}
		}
		for (int i = 1; i < len && valid; ++i) addEdge(words[i - 1], words[i]);
		if (!valid) return "";
		order = string(edges.size(), ' ');
		index = edges.size() - 1;
		for (const auto &p : edges) {
			if (!states.count(p.first)) dfs(p.first);
			if (!valid) return "";
		}
		return order;
	}
};


// BFS + 拓扑排序
class Solution2 {
private:
	unordered_map<char, vector<char>> edges;
	unordered_map<char, int> inDegrees;
	bool valid = true;

private:
	void addEdge(const string &str1, const string &str2) {
		int len1 = str1.size(), len2 = str2.size();
		int len = min(len1, len2);
		int idx = 0;
		while (idx < len) {
			char c1 = str1[idx], c2 = str2[idx];
			if (c1 != c2) {
				edges[c1].emplace_back(c2);
				++inDegrees[c2];
				return;
			}
			++idx;
		}
		if (idx == len && len1 > len2)
			valid = false;
	}

public:
	string alienOrder(vector<string> &words) {
		int len = words.size();
		for (const auto &word : words) {
			int wordLen = word.size();
			for (int i = 0; i < wordLen; ++i) {
				char c = word[i];
				if (!edges.count(c)) edges[c] = vector<char>();
			}
		}
		for (int i = 1; i < len && valid; ++i) addEdge(words[i - 1], words[i]);
		if (!valid) return "";
		queue<char> q;
		for (const auto &p : edges) {
			if (!inDegrees.count(p.first)) q.emplace(p.first);
		}
		string order;
		while (!q.empty()) {
			char u = q.front();
			q.pop();
			order.push_back(u);
			for (const auto &v : edges[u]) {
				--inDegrees[v];
				if (!inDegrees[v]) q.emplace(v);
			}
		}
		return order.size() == edges.size() ? order : "";
	}
};

