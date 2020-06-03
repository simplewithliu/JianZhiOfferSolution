#include "header.h"

/*

请实现一个函数，把字符串 s 中的每个空格替换成"%20"。

示例 1：

输入：s = "We are happy."
输出："We%20are%20happy."
  
限制：
0 <= s 的长度 <= 10000

*/

class Solution {
public:
	string replaceSpace(string s)
	{
		if (s.empty()) return "";
		int originLen = s.size(), numBlank = 0;
		for (int i = 0; i < originLen; ++i) if (s[i] == ' ') ++numBlank;
		int newLen = originLen + numBlank * 2;
		s.resize(newLen);
		int idxOrigin = originLen - 1, idxNew = newLen - 1;
		while (idxOrigin >= 0 && idxNew > idxOrigin)
		{
			if (s[idxOrigin] == ' ')
			{
				s[idxNew--] = '0';
				s[idxNew--] = '2';
				s[idxNew--] = '%';
			}
			else
			{
				s[idxNew--] = s[idxOrigin];
			}
			--idxOrigin;
		}
		return s;
	}
};