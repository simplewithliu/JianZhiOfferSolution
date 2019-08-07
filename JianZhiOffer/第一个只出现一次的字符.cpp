#include "header.h"

/*

在一个字符串(0<=字符串长度<=10000，全部由字母组成)中找到第一个只出现一次的字符,并返回它的位置, 
如果没有则返回 -1（需要区分大小写）.

*/

class Solution1 {
public:
	int FirstNotRepeatingChar(string str)
	{
		if (str.empty()) return -1;
		vector<int> vec(60, 0);
		int len = str.size();
		for (int i = 0; i < len; ++i)
		{
			vec[str[i] - 'A'] += 1;
		}
		for (int i = 0; i < len; ++i)
		{
			if (vec[str[i] - 'A'] == 1)
				return i;
		}
		return -1;
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
