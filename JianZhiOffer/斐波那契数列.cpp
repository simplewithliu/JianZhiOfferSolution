#include "header.h"

/*

要求输入一个整数n，请你输出斐波那契数列的第n项（从0开始，第0项为0）

*/

class Solution {
public:
	int Fibonacci(int n)
	{
		if (n == 0) return 0;
		int a = 1, b = 0;
		while (--n > 0)
		{
			a = a + b;
			b = a - b;
		}
		return a;
	}
};