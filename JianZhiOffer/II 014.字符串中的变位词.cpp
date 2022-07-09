#include "header.h"

/*

给定两个字符串 s1 和 s2，写一个函数来判断 s2 是否包含 s1 的某个变位词。

换句话说，第一个字符串的排列之一是第二个字符串的 子串 。

示例 1：
输入 : s1 = "ab" s2 = "eidbaooo"
输出 : True
解释 : s2 包含 s1 的排列之一("ba").

示例 2：
输入 : s1 = "ab" s2 = "eidboaoo"
输出 : False

提示：
1 <= s1.length, s2.length <= 10^4
s1 和 s2 仅包含小写字母

注意：本题与主站 567 题相同： https://leetcode-cn.com/problems/permutation-in-string/

*/

// 滑动窗口，与LeetCode 076题型相同
class Solution {
public:
	bool checkInclusion(string s1, string s2) {
		vector<int> m(26, 0);
		for (auto c : s1) ++m[c - 'a'];
		int len1 = s1.size(), len2 = s2.size();
		int start = 0, end = 0;
		while (end < len2) {
			char c = s2[end];
			++end;
			--m[c - 'a'];
			while (start < end && m[c - 'a'] < 0) {
				++m[s2[start] - 'a'];
				++start;
			}
			if (end - start == len1) return true;
		}
		return false;
	}
};

