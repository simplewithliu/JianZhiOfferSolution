#include "header.h"

/*

输入一个字符串，打印出该字符串中字符的所有排列。你可以以任意顺序返回这个字符串数组，但里面不能有重复元素。

示例:
输入：s = "abc"
输出：["abc","acb","bac","bca","cab","cba"]
   
限制：1 <= s 的长度 <= 8

*/

//参考LeetCode 47 全排列2
class Solution {
public:
	vector<string> permutation(string s) 
	{
		if (s.empty()) return {};
		vector<string> res;
		string str;
		vector<char> used(s.size(), false);
		sort(s.begin(), s.end());
		helper(s, str, res, used);
		return res;
	}
	void helper(string &s, string &str, vector<string> &res, vector<char> &used)
	{
		int len1 = s.size(), len2 = str.size();
		if (len1 == len2)
		{
			res.push_back(str);
			return;
		}
		for (int i = 0; i < len1; ++i)
		{
			if (used[i]) continue;
			if (i > 0 && s[i - 1] == s[i] && !used[i - 1]) continue;
			used[i] = true;
			str.push_back(s[i]);
			helper(s, str, res, used);
			used[i] = false;
			str.pop_back();
		}
	}
};