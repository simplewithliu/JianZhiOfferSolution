#include "header.h"

/*

LCR 019. 验证回文串 II

给你一个字符串s，最多可以从中删除一个字符。

请你判断 s 是否能成为回文字符串：如果能，返回 true；否则，返回 false

示例 1：
输入：s = "aba"
输出：true

示例 2：
输入：s = "abca"
输出：true
解释：你可以删除字符 'c'

示例 3：
输入：s = "abc"
输出：false

提示：
1 <= s.length <= 10^5
s 由小写英文字母组成

注意：本题与主站 680 题相同：https://leetcode-cn.com/problems/valid-palindrome-ii/

*/

class Solution {
public:
	bool validPalindrome(string s) {
		int len = s.size();
		int left = 0, right = len - 1;
		while (left < right && s[left] == s[right]) {
			++left;
			--right;
		}
		return checkPal(s, left + 1, right) || checkPal(s, left, right - 1);
	}

private:
	bool checkPal(const string &s, int left, int right) {
		while (left < right) {
			if (s[left] != s[right]) return false;
			++left;
			--right;
		}
		return true;
	}
};
