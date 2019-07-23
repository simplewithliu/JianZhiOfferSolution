#include "header.h"

/*

请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。
例如，字符串"+100","5e2","-123","3.1416"和"-1E-16"都表示数值。 
但是"12e","1a3.14","1.2.3","+-5"和"12e+4.3"都不是。

*/

class Solution {
public:
	bool isNumeric(char* s)
	{
		bool point = false, hasE = false, seeNum = false;
		int i = 0;
		for (; s[i] == ' '; ++i);
		int first = i;
		for (; s[i] != '\0'; ++i)
		{
			if (s[i] >= '0'&&s[i] <= '9')
			{
				seeNum = true;
			}
			else if (s[i] == '.')
			{
				if (hasE || point) return false;
				point = true;
			}
			else if (s[i] == 'E' || s[i] == 'e')
			{
				if (hasE || !seeNum) return false;
				hasE = true;
				seeNum = false;
			}
			else if (s[i] == '-' || s[i] == '+')
			{
				if (i != first && s[i - 1] != 'E'&s[i - 1] != 'e') return false;
			}
			else if (s[i] == ' ')
			{
				while (s[i] != '\0')
				{
					if (s[i] != ' ')
						return false;
					++i;
				}
			}
			else
				return false;
		}
		return seeNum;
	}
};