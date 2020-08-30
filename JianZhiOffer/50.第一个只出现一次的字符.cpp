#include "header.h"

/*

在字符串 s 中找出第一个只出现一次的字符。如果没有，返回一个单空格。 
s只包含小写字母。

示例:
s = "abaccdeff"
返回 "b"

s = ""
返回 " "
 
限制：0 <= s 的长度 <= 50000

*/

class Solution {
public:
	char firstUniqChar(string s)
	{
		if (s.empty()) return ' ';
		vector<int> m(26, 0);
		for (auto c : s) ++m[c - 'a'];
		for (auto c : s) if (m[c - 'a'] == 1) return c;
		return ' ';
	}
};


/*

请实现一个函数用来找出字符流中第一个只出现一次的字符。
例如，当从字符流中只读出前两个字符"go"时，第一个只出现一次的字符是"g"。
当从该字符流中读出前六个字符“google"时，第一个只出现一次的字符是"l"。

*/

class Solution2 {
public:
	vector<int> bucket = vector<int>(128, -1);
	int index = 0;
	//Insert one char from stringstream
	void Insert(char ch)
	{
		if (bucket[ch - 0] == -1)
			bucket[ch - 0] = index;
		else
			bucket[ch - 0] = -2;
		++index;
	}
	//return the first appearence once char in current stringstream
	char FirstAppearingOnce()
	{
		char ch = '#';
		int minindex = INT_MAX;;
		for (int i = 0; i < 128; ++i)
		{
			if (bucket[i] >= 0 && bucket[i]<minindex)
			{
				minindex = min(minindex, bucket[i]);
				ch = static_cast<char>(i);
			}
		}
		return ch;
	}
};
