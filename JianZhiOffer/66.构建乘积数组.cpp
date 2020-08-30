#include "header.h"

/*

给定一个数组 A[0,1,…,n-1]，请构建一个数组 B[0,1,…,n-1]，其中 B 中的元素 B[i]=A[0]×A[1]×…×A[i-1]×A[i+1]×…×A[n-1]。不能使用除法。

示例:
输入: [1,2,3,4,5]
输出: [120,60,40,30,24]
  
提示：
所有元素乘积之和不会溢出 32 位整数
a.length <= 100000

*/

class Solution {
public:
	vector<int> constructArr(vector<int> &a) 
	{
		int len = a.size();
		if (len == 0) return {};
		vector<int> res(len, 1);
		for (int i = 1; i < len; ++i)
		{
			res[i] = res[i - 1] * a[i - 1];
		}
		int mem = 1;
		for (int i = len - 2; i >= 0; --i)
		{
			mem *= a[i + 1];
			res[i] *= mem;
		}
		return res;
	}
};