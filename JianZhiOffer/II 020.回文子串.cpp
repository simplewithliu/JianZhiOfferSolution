#include "header.h"

/*

给你一个字符串 s，请你统计并返回这个字符串中回文子串的数目
回文字符串 是正着读和倒过来读一样的字符串
子字符串 是字符串中的由连续字符组成的一个序列
具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被视作不同的子串

示例 1：
输入：s = "abc"
输出：3
解释：三个回文子串: "a", "b", "c"

示例 2：
输入：s = "aaa"
输出：6
解释：6个回文子串: "a", "a", "a", "aa", "aa", "aaa"

提示：
1 <= s.length <= 1000
s 由小写英文字母组成

注意：本题与主站 647 题相同: https://leetcode-cn.com/problems/palindromic-substrings/


*/

// 中心拓展
class Solution1 {
public:
	int countSubstrings(string s) {
		int res = 0;
		int len = s.size();
		for (int i = 0; i < len; ++i) {
			res += extend(s, i, i) + extend(s, i, i + 1);
		}
		return res;
	}

private:
	int extend(const string &s, int i, int j) {
		int cnt = 0;
		for (; i >= 0 && j < s.size(); --i, ++j) {
			if (s[i] != s[j]) break;
			++cnt;
		}
		return cnt;
	}
};

// Manacher
class Solution2 {
public:
	int countSubstrings(string s) {
		string str = preProcess(s);
		int len = str.size();
		vector<int> pal(len);
		int center = 0, maxRight = 0;
		int cnt = 0;
		for (int i = 0; i < len; ++i) {
			if (i < maxRight) {
				int mirror = 2 * center - i;
				pal[i] = min(maxRight - i, pal[mirror]);
			}
			int left = i - (pal[i] + 1);
			int right = i + (pal[i] + 1);
			while (left >= 0 && right < len && str[left] == str[right]) {
				--left;
				++right;
				++pal[i];
			}
			if ((i + pal[i]) > maxRight) {
				maxRight = i + pal[i];
				center = i;
			}
			cnt += (pal[i] + 1) / 2;
		}
		return cnt;
	}

private:
	string preProcess(const string &s) {
		int len = s.size();
		string str;
		for (int i = 0; i < len; ++i) str.append({ '#', s[i] });
		str.append("#");
		return str;
	}
};

// 动态规划
class Solution3 {
public:
	int countSubstrings(string s) {
		if (s.empty()) return 0;
		int len = s.size();
		vector<vector<char>> isPal(len, vector<char>(len, false));
		int res = 0;
		for (int palLen = 1; palLen <= len; ++palLen) {
			for (int i = 0; i <= len - palLen; ++i) {
				int j = i + palLen - 1;
				isPal[i][j] = (s[i] == s[j]) &&
					(palLen < 3 || isPal[i + 1][j - 1]);
				if (isPal[i][j]) ++res;
			}
		}
		return res;
	}
};

