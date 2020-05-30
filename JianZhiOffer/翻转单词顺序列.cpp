#include "header.h"

/*

正确的句子应该是“I am a student.”
句子单词的顺序翻转后为“student. a am I”

*/

class Solution {
public:
	string ReverseSentence(string str)
	{
		reverse(str.begin(), str.end());
		for (auto it1 = str.begin(), it2 = str.begin(); it1 != str.end();)
		{
			if (*it1 == ' ')
			{
				++it1;
				++it2;
			}
			else if (it2 == str.end() || *it2 == ' ')
			{
				reverse(it1, it2);
				it1 = it2;
			}
			else
			{
				++it2;
			}
		}
		return str;
	}
};
