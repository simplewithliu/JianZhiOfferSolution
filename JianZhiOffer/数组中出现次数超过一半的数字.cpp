#include "header.h"

/*

数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。
例如输入一个长度为9的数组{1,2,3,2,2,2,5,4,2}。
由于数字2在数组中出现了5次，超过数组长度的一半，因此输出2。如果不存在则输出0。

*/

//基于快速划分的方法，时间复杂度平均可以达到O(n)
class Solution1 {
public:
	int MoreThanHalfNum_Solution(vector<int> numbers)
	{
		if (numbers.empty()) return 0;
		int len = numbers.size();
		int middle = len >> 1;
		int start = 0, end = len - 1;
		int index = partition(numbers, start, end);
		while (index != middle)
		{
			if (index > middle)
			{
				end = index - 1;
				index = partition(numbers, start, end);
			}
			else
			{
				start = index + 1;
				index = partition(numbers, start, end);
			}
		}
		int res = numbers[index];
		if (check(numbers, res))
			return res;
		else
			return 0;
	}
	int partition(vector<int> &numbers, int lo, int hi)
	{
		swap(numbers[lo], numbers[lo + rand() % (hi - lo + 1)]);
		int pivot = numbers[lo];
		while (lo < hi)
		{
			while (lo < hi)
			{
				if (numbers[hi]>pivot)
					--hi;
				else
				{
					numbers[lo++] = numbers[hi];
					break;
				}
			}
			while (lo < hi)
			{
				if (numbers[lo] < pivot)
					++lo;
				else
				{
					numbers[hi--] = numbers[lo];
					break;
				}
			}
		}
		numbers[lo] = pivot;
		return lo;
	}
	bool check(vector<int> &numbers, int num)
	{
		int times = 0;
		for (int i = 0; i < numbers.size(); ++i)
			if (numbers[i] == num)
				++times;
		if (times * 2 <= numbers.size())
			return false;
		else
			return true;
	}
};

//基于数组特点的灵活方法
class Solution2 {
public:
	int MoreThanHalfNum_Solution(vector<int> numbers)
	{
		if (numbers.empty()) return 0;
		int cur = numbers[0];
		int times = 1;
		int len = numbers.size();
		for (int i = 1; i < len; ++i)
		{
			if (times == 0)
			{
				cur = numbers[i];
				times = 1;
			}
			if (numbers[i] == cur)
			{
				times += 1;
			}
			else
			{
				times -= 1;
			}
		}
		times = 0;
		for (int i = 0; i < len; ++i)
		{
			if (numbers[i] == cur)
				++times;
		}
		if (times>len / 2)
			return cur;
		return 0;
	}
};