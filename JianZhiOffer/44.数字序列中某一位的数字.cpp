#include "header.h"

/*

数字以0123456789101112131415…的格式序列化到一个字符序列中。在这个序列中，第5位（从下标0开始计数）是5，第13位是1，第19位是4，等等。
请写一个函数，求任意第n位对应的数字。

示例 1：
输入：n = 3
输出：3
 
示例 2：
输入：n = 11
输出：0
  
限制：0 <= n < 2^31
注意：本题与主站 400 题相同：https://leetcode-cn.com/problems/nth-digit/

*/

class Solution {
public:
	int findNthDigit(int n) 
	{
		int digit = 1;
		long long start = 1;
		long long count = 9;
		while (n > count)
		{
			n -= count;
			digit += 1;
			start *= 10;
			count = digit * start * 9;
		}
		long long  num = start + (n - 1) / digit;
		return to_string(num)[(n - 1) % digit] - '0';
	}
};
//https://leetcode-cn.com/problems/shu-zi-xu-lie-zhong-mou-yi-wei-de-shu-zi-lcof/solution/mian-shi-ti-44-shu-zi-xu-lie-zhong-mou-yi-wei-de-6/