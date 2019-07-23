#include "header.h"

/*

输入一个整数数组，实现一个函数来调整该数组中数字的顺序，
使得所有的奇数位于数组的前半部分，所有的偶数位于数组的后半部分，
并保证奇数和奇数，偶数和偶数之间的相对位置不变。

*/

class Solution {
public:
	void reOrderArray(vector<int> &array)
	{
		if (array.empty())
			return;
		int indexOfEven = 0, indexOfOdd = 0;
		while (indexOfEven < array.size())
		{
			while (indexOfEven < array.size() && (array[indexOfEven] & 1))
				++indexOfEven;
			indexOfOdd = indexOfEven + 1;
			while (indexOfOdd < array.size() && !(array[indexOfOdd] & 1))
			{
				++indexOfOdd;
			}
			if (indexOfOdd < array.size())
			{
				int temp = array[indexOfOdd];
				for (int i = indexOfOdd - 1; i >= indexOfEven; --i)
				{
					array[i + 1] = array[i];
				}
				array[indexOfEven++] = temp;
			}
			else
			{
				break;
			}
		}
	}
};