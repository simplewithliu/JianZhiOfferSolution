#include "header.h"

/*

给你一个字符串数组 words ，找出并返回 length(words[i]) * length(words[j]) 的最大值，并且这两个单词不含有公共字母。
如果不存在这样的两个单词，返回 0 。

示例 1：
输入：words = ["abcw","baz","foo","bar","xtfn","abcdef"]
输出：16
解释：这两个单词为 "abcw", "xtfn"。

示例 2：
输入：words = ["a","ab","abc","d","cd","bcd","abcd"]
输出：4
解释：这两个单词为 "ab", "cd"。

示例 3：
输入：words = ["a","aa","aaa","aaaa"]
输出：0
解释：不存在这样的两个单词。

提示：
2 <= words.length <= 1000
1 <= words[i].length <= 1000
words[i] 仅包含小写字母

注意：本题与主站 318 题相同：https://leetcode-cn.com/problems/maximum-product-of-word-lengths/

*/

class Solution1 {
public:
	int maxProduct(vector<string>& words) {
		int len = words.size();
		vector<int> masks(len);
		for (int i = 0; i < len; ++i) {
			string word = words[i];
			for (const char &c : word) masks[i] |= 1 << (c - 'a');
		}
		int maxProd = 0;
		for (int i = 0; i < len; ++i) {
			for (int j = i + 1; j < len; ++j) {
				if ((masks[i] & masks[j]) == 0) maxProd = max(maxProd, (int)(words[i].size()*words[j].size()));
			}
		}
		return maxProd;
	}
};

class Solution2 {
public:
	int maxProduct(vector<string>& words) {
		int len = words.size();
		unordered_map<int, int> m;
		for (int i = 0; i < len; ++i) {
			int mask = 0;
			string word = words[i];
			for (const char &c : word) mask |= 1 << (c - 'a');
			if (m.count(mask)) {
				if (word.size() > m[mask]) m[mask] = word.size();
			} else {
				m[mask] = word.size();
			}
		}
		int maxProd = 0;
		for (const auto &p1 : m) {
			int wordLen1 = p1.second;
			for (const auto &p2 : m) {
				if ((p1.first & p2.first) == 0) {
					int wordLen2 = p2.second;
					maxProd = max(maxProd, wordLen1*wordLen2);
				}
			}
		}
		return maxProd;
	}
};