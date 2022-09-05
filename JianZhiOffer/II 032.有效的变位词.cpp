#include "header.h"

/*

给定两个字符串 s 和 t ，编写一个函数来判断它们是不是一组变位词（字母异位词）。

注意：若 s 和 t 中每个字符出现的次数都相同且字符顺序不完全相同，则称 s 和 t 互为变位词（字母异位词）。

示例 1:
输入: s = "anagram", t = "nagaram"
输出: true

示例 2:
输入: s = "rat", t = "car"
输出: false

示例 3:
输入: s = "a", t = "a"
输出: false

提示:
1 <= s.length, t.length <= 5 * 10^4
s and t 仅包含小写字母

进阶: 如果输入字符串包含 unicode 字符怎么办？你能否调整你的解法来应对这种情况？

注意：本题与主站 242 题相似（字母异位词定义不同）：https://leetcode-cn.com/problems/valid-anagram/

*/

// 存在unicode字符可以直接使用哈希表
class Solution {
public:
	bool isAnagram(string s, string t) {
		if (s.length() != t.length() || s == t) return false;
		vector<int> table(26, 0);
		for (const auto &c : s) ++table[c - 'a'];
		for (const auto &c : t) {
			--table[c - 'a'];
			if (table[c - 'a'] < 0) return false;
		}
		return true;
	}
};