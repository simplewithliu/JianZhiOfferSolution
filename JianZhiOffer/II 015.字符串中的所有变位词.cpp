﻿#include "header.h"

/*

给定两个字符串 s 和 p，找到 s 中所有 p 的 变位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。
变位词指字母相同，但排列不同的字符串。

示例 1：
输入: s = "cbaebabacd", p = "abc"
输出: [0,6]
解释:
起始索引等于 0 的子串是 "cba", 它是 "abc" 的变位词。
起始索引等于 6 的子串是 "bac", 它是 "abc" 的变位词。

示例 2：
输入: s = "abab", p = "ab"
输出: [0,1,2]
解释:
起始索引等于 0 的子串是 "ab", 它是 "ab" 的变位词。
起始索引等于 1 的子串是 "ba", 它是 "ab" 的变位词。
起始索引等于 2 的子串是 "ab", 它是 "ab" 的变位词。

提示:
1 <= s.length, p.length <= 3 * 10^4
s 和 p 仅包含小写字母
    
注意：本题与主站 438 题相同： https://leetcode-cn.com/problems/find-all-anagrams-in-a-string/

*/

// 滑动窗口，与LeetCode 076题型相同
class Solution {
public:
	vector<int> findAnagrams(string s, string p) {
		int sLen = s.size(), pLen = p.size();
		if (sLen < pLen) return{};
		vector<int> res;
		vector<int> m(26, 0);
		for (auto c : p) ++m[c - 'a'];
		int start = 0, end = 0, counter = pLen;
		while (end < sLen) {
			if (m[s[end] - 'a'] >= 1) --counter;
			--m[s[end] - 'a'];
			++end;
			while (counter == 0) {
				if (end - start == pLen) res.push_back(start);
				if (m[s[start] - 'a'] == 0) ++counter;
				++m[s[start] - 'a'];
				++start;
			}
		}
		return res;
	}
};