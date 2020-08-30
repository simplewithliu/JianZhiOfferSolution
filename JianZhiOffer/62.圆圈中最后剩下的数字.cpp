#include "header.h"

/*

0,1,...,n-1这n个数字排成一个圆圈，从数字0开始，每次从这个圆圈里删除第m个数字。求出这个圆圈里剩下的最后一个数字。
例如，0、1、2、3、4这5个数字组成一个圆圈，从数字0开始每次删除第3个数字，则删除的前4个数字依次是2、0、4、1，因此最后剩下的数字是3。

示例 1：
输入: n = 5, m = 3
输出: 3
 
示例 2：
输入: n = 10, m = 17
输出: 2
  
限制：
1 <= n <= 10^5
1 <= m <= 10^6

*/

//模拟环，超时
class Solution1 {
public:
	int lastRemaining(int n, int m) 
	{
		vector<int> circle;
		for (int i = 0; i < n; ++i) circle.push_back(i);
		int idx = 0;
		while (n>1)
		{
			idx = (idx + m - 1) % n;
			circle.erase(circle.begin() + idx);
			--n;
		}
		return circle[0];
	}
};

//数学方法
class Solution2 {
public:
	int lastRemaining(int n, int m)
	{
		int res = 0;
		for (int i = 2; i <= n; ++i)
		{
			res = (res + m) % i;
		}
		return res;
	}
};
//https://leetcode-cn.com/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof/solution/javajie-jue-yue-se-fu-huan-wen-ti-gao-su-ni-wei-sh/