#include "header.h"

/*

LCR 017. 最小覆盖子串

给你一个字符串 s， 一个字符串 t
返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 ""

注意：
对于 t 中重复字符，我们寻找的子字符串中该字符数量必须不少于 t 中该字符数量
如果 s 中存在这样的子串，我们保证它是唯一的答案

示例 1：
输入：s = "ADOBECODEBANC", t = "ABC"
输出："BANC"
解释：最小覆盖子串 "BANC" 包含来自字符串 t 的 'A'、'B' 和 'C'

示例 2：
输入：s = "a", t = "a"
输出："a"
解释：整个字符串 s 是最小覆盖子串

示例 3:
输入: s = "a", t = "aa"
输出: ""
解释: t 中两个字符 'a' 均应包含在 s 的子串中，因此没有符合条件的子字符串，返回空字符串

提示：
m == s.length
n == t.length
1 <= m, n <= 10^5
s 和 t 由英文字母组成

进阶：你能设计一个在 o(m+n) 时间内解决此问题的算法吗？

注意：本题与主站 76 题相似：https://leetcode-cn.com/problems/minimum-window-substring/

*/


class Solution {
public:
	string minWindow(string s, string t) {
		vector<int> mp(60);
		for (const auto &c : t) ++mp[c - 'A'];
		int start = 0, end = 0, counter = t.size();
		int sLen = s.size(), minStart = 0, minLen = INT_MAX;
		while (end < sLen) {
			if (mp[s[end] - 'A'] > 0) --counter;
			--mp[s[end] - 'A'];
			++end;
			while (counter == 0) {
				if (end - start < minLen) {
					minStart = start;
					minLen = end - start;
				}
				if (mp[s[start] - 'A'] == 0) ++counter;
				++mp[s[start] - 'A'];
				++start;
			}
		}
		return minLen == INT_MAX ? "" : s.substr(minStart, minLen);
	}
};
// https://leetcode.com/problems/minimum-window-substring/solutions/26808/here-is-a-10-line-template-that-can-solve-most-substring-problems/
// @author https://leetcode.com/zjh08177/

