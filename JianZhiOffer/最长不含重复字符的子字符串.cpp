#include "header.h"

/*

给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。

输入: "abcabcbb"
输出: 3
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。

输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。

*/

class Solution1 {
public:
	int lengthOfLongestSubstring(string s)
	{
		if (s.empty()) return 0;
		int len = s.size();
		vector<int> dict(128, -1);
		int startIndex = -1;
		int maxLen = 0;
		for (int i = 0; i < len; ++i)
		{
			if (dict[s[i]]>startIndex)
				startIndex = dict[s[i]];
			dict[s[i]] = i;
			maxLen = max(maxLen, i - startIndex);
		}
		return maxLen;
	}
};

//一种典型的滑动窗口方法
class Solution2 {
public:
	int lengthOfLongestSubstring(string s) 
	{
		vector<int> dict(128, 0);
		int start = 0, end = 0, maxLen = 0, counter = 0;
		while (end < s.size())
		{
			if (dict[s[end]]>0) ++counter;
			++dict[s[end]];
			++end;
			while (counter > 0)
			{
				if (dict[s[start]] > 1) --counter;
				--dict[s[start]];
				++start;
			}
			maxLen = max(maxLen, end - start);
		}
		return maxLen;
	}
};