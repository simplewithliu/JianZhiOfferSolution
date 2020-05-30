#include "header.h"

/*

汇编语言中有一种移位指令叫做循环左移（ROL），现在有个简单的任务，就是用字符串模拟这个指令的运算结果。
对于一个给定的字符序列S，请你把其循环左移K位后的序列输出。
例如，字符序列S=”abcXYZdef”,要求输出循环左移3位后的结果，即“XYZdefabc”。

*/

class Solution {
public:
	string LeftRotateString(string str, int n)
	{
		if (str.empty() || n < 0) return{};
		int len = str.size();
		int num = n%len;
		string strROL = str.substr(num) + str.substr(0, num);
		return strROL;
	}
};

//这个题目也考察字符串翻转的灵活运用，所以另一种思路是：
//1、翻转字符串前面n个字符；
//2、翻转字符串的后面部分；
//3、翻转整个字符串。