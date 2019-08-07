#include "header.h"

/*

一个整型数组里除了两个数字之外，其他的数字都出现了两次。请写程序找出这两个只出现一次的数字。

*/

class Solution {
public:
	void FindNumsAppearOnce(vector<int> data, int *num1, int *num2)
	{
		int xorsum = 0;
		for (auto i : data)
			xorsum ^= i;
		int bitflag = 1;
		while (!(bitflag&xorsum))
			bitflag <<= 1;
		for (auto i : data)
		{
			if (i&bitflag)
				(*num1) ^= i;
			else
				(*num2) ^= i;
		}
	}
};