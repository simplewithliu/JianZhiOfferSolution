#include "header.h"

/*

剑指 Offer II 108. 单词演变

字典 wordList 中从单词 beginWord 和 endWord 的 转换序列 是一个按下述规格形成的序列 beginWord -> s1 -> s2 -> ... -> sk：

每一对相邻的单词只差一个字母
对于 1 <= i <= k 时，每个 si 都在 wordList 中。注意， beginWord 不需要在 wordList 中
sk == endWord

给你两个单词 beginWord 和 endWord 和一个字典 wordList ，返回 从 beginWord 到 endWord 的 最短转换序列 中的 单词数目。如果不存在这样的转换序列，返回 0

示例 1：
输入：beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
输出：5
解释：一个最短转换序列是 "hit" -> "hot" -> "dot" -> "dog" -> "cog", 返回它的长度 5

示例 2：
输入：beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
输出：0
解释：endWord "cog" 不在字典中，所以无法进行转换

提示：
1 <= beginWord.length <= 10
endWord.length == beginWord.length
1 <= wordList.length <= 5000
wordList[i].length == beginWord.length
beginWord、endWord 和 wordList[i] 由小写英文字母组成
beginWord != endWord
wordList 中的所有字符串互不相同

注意：本题与主站 127 题相同： https://leetcode-cn.com/problems/word-ladder/

*/

class Solution1 {
public:
	int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
		queue<string> q;
		unordered_set<string> wordDict(wordList.begin(), wordList.end());
		if (!wordDict.count(endWord)) return 0;
		q.push(beginWord);
		wordDict.erase(beginWord);
		int ladder = 1;
		while (!q.empty()) {
			int len = q.size();
			for (int i = 0; i < len; ++i) {
				string tmp = q.front();
				q.pop();
				for (int j = 0; j < tmp.size(); ++j) {
					char c = tmp[j];
					for (int k = 0; k < 26; ++k) {
						tmp[j] = 'a' + k;
						if (wordDict.count(tmp)) {
							if (tmp == endWord) return ladder + 1;
							q.push(tmp);
							wordDict.erase(tmp);
						}
					}
					tmp[j] = c;
				}
			}
			++ladder;
		}
		return 0;
	}
};

// 双向BFS
class Solution2 {
public:
	int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
		unordered_set<string> dict(wordList.begin(), wordList.end());
		unordered_set<string> head, tail;
		if (!dict.count(endWord)) return 0;
		head.insert(beginWord);
		tail.insert(endWord);
		int ladder = 2;
		while (!head.empty() && !tail.empty()) {
			if (head.size() > tail.size()) swap(head, tail);
			unordered_set<string> tmpset;
			for (auto it = head.begin(); it != head.end(); ++it) {
				string word = *it;
				for (int i = 0; i < word.size(); ++i) {
					char c = word[i];
					for (int j = 0; j < 26; ++j) {
						word[i] = 'a' + j;
						if (tail.count(word)) return ladder;
						if (dict.count(word)) {
							tmpset.insert(word);
							dict.erase(word);
						}
					}
					word[i] = c;
				}
			}
			++ladder;
			swap(head, tmpset);
		}
		return 0;
	}
};