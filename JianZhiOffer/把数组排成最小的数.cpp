#include "header.h"

/*

输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。
例如输入数组{3，32，321}，则打印出这三个数字能排成的最小数字为321323。

*/

class Solution {
public:
	string PrintMinNumber(vector<int> numbers)
	{
		if (numbers.empty())
			return{};
		int len = numbers.size();
		string res;
		sort(numbers.begin(), numbers.end(),
			[](const int &str1, const int &str2) -> bool
		{
			string A = to_string(str1) + to_string(str2);
			string B = to_string(str2) + to_string(str1);
			return A < B;
		}
		);
		for (auto i : numbers)
			res += to_string(i);
		return res;
	}
};