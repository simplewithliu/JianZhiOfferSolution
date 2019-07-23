#include "header.h"

/*

请实现一个函数，将一个字符串中的每个空格替换成“%20”。
例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。

*/

class Solution {
public:
	//题目需保证替换后数组不会越界，给出length变量标出数组最大长度。
	void replaceSpace(char *str, int length)
	{
		if (!str || length <= 0)
			return;
		int originalLength = 0;
		int numberofBlank = 0;
		int i = 0;
		while (str[i] != '\0')
		{
			++originalLength;
			if (str[i] == ' ')
				++numberofBlank;
			++i;
		}
		int newlength = originalLength + numberofBlank * 2;
		if (newlength>length)
			return;
		int indexofOriginal = originalLength;
		int indexofNew = newlength;
		while (indexofOriginal >= 0 && indexofNew>indexofOriginal)
		{
			if (str[indexofOriginal] == ' ')
			{
				str[indexofNew--] = '0';
				str[indexofNew--] = '2';
				str[indexofNew--] = '%';
			}
			else
			{
				str[indexofNew--] = str[indexofOriginal];
			}
			--indexofOriginal;
		}
	}
};