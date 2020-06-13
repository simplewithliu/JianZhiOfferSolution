#include "header.h"

/*

输入数字 n，按顺序打印出从 1 到最大的 n 位十进制数。比如输入 3，则打印出 1、2、3 一直到最大的 3 位数 999。

示例 1:
输入: n = 1
输出: [1,2,3,4,5,6,7,8,9]

说明：
用返回一个整数列表来代替打印
n 为正整数

*/

//题目中返回的是int型数组，所以不存在大数问题
//如果直接打印的话，则需要考虑大数问题，利用字符串操作
class Solution {
private:
	vector<int> res;
	int start = 0, nineAnt = 0;
public:
	vector<int> printNumbers(int n)
	{
		vector<char> loop{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
		string num(n, '0');
		start = n - 1;
		helper(0, n, num, loop);
		return res;
	}
	void helper(int x, int n, string &num, vector<char> &loop)
	{
		if (x == n)
		{
			string s = num.substr(start);
			if (s != "0") res.push_back(stoi(s));
			if (n - start == nineAnt) --start;
			return;
		}
		for (char i : loop)
		{
			if (i == '9') ++nineAnt;
			num[x] = i;
			helper(x + 1, n, num, loop);
		}
		--nineAnt;
	}
};
//https://leetcode-cn.com/problems/da-yin-cong-1dao-zui-da-de-nwei-shu-lcof/solution/mian-shi-ti-17-da-yin-cong-1-dao-zui-da-de-n-wei-2/