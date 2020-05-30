#include "header.h"

/*

给定一个double类型的浮点数base和int类型的整数exponent。
求base的exponent次方。

*/

class Solution {
public:
	double Power(double base, int exponent)
	{
		double value = 1.0;
		if (exponent > 0)
		{
			while (exponent)
			{
				value *= base;
				--exponent;
			}
		}
		else if (exponent < 0)
		{
			while (exponent)
			{
				value *= base;
				++exponent;
			}
			value = 1 / value;
		}
		return value;
	}
};