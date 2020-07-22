#include "header.h"

/*

请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。
例如，字符串"+100"、"5e2"、"-123"、"3.1416"、"0123"都表示数值，
但"12e"、"1a3.14"、"1.2.3"、"+-5"、"-1E-16"及"12e+5.4"都不是。

注意：本题与主站 65 题相同：https://leetcode-cn.com/problems/valid-number/

*/

class Solution1 {
public:
	bool isNumber(string s) 
	{
		if (s.empty()) return false;
		int len = s.size();
		bool point = false, hasE = false, seeNum = false;
		int idx = 0;
		for (; s[idx] == ' '; ++idx);
		int first = idx;
		for (; idx < len; ++idx)
		{
			if (s[idx] >= '0'&&s[idx] <= '9')
			{
				seeNum = true;
			}
			else if (s[idx] == '.')
			{
				if (hasE || point) return false;
				point = true;
			}
			else if (s[idx] == 'e')
			{
				if (hasE || !seeNum) return false;
				hasE = true;
				seeNum = false;
			}
			else if (s[idx] == '+' || s[idx] == '-')
			{
				if (idx != first && s[idx - 1] != 'e') return false;
			}
			else if (s[idx] == ' ')
			{
				while (idx < len)
				{
					if (s[idx] != ' ') return false;
					++idx;
				}
			}
			else return false;
		}
		return seeNum;
	}
};

//自动机方法
class Solution2 {
public:
	bool isNumber(string s)
	{
		vector<unordered_map<char, char>> m(9);
		m[0].insert({ { ' ', 0 }, { 's', 1 }, { 'd', 2 }, { '.', 4 } });
		m[1].insert({ { 'd', 2 }, { '.', 4 } });
		m[2].insert({ { 'd', 2 }, { '.', 3 }, { 'e', 5 }, { ' ', 8 } });
		m[3].insert({ { 'd', 3 }, { 'e', 5 }, { ' ', 8 } });
		m[4].insert({ 'd', 3 });
		m[5].insert({ { 's', 6 }, { 'd', 7 } });
		m[6].insert({ 'd', 7 });
		m[7].insert({ { 'd', 7 }, { ' ', 8 } });
		m[8].insert({ ' ', 8 });
		char pos = 0;
		char key = 0;
		for (char c : s)
		{
			if (c >= '0'&&c <= '9') key = 'd';
			else if (c == '+' || c == '-') key = 's';
			else key = c;
			if (!m[pos].count(key)) return false;
			pos = m[pos][key];
		}
		return pos == 2 || pos == 3 || pos == 7 || pos == 8;
	}
};
//https://leetcode-cn.com/problems/biao-shi-shu-zhi-de-zi-fu-chuan-lcof/solution/mian-shi-ti-20-biao-shi-shu-zhi-de-zi-fu-chuan-y-2/