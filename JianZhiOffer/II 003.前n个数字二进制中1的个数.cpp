#include "header.h"

/*

给定一个非负整数 n ，请计算 0 到 n 之间的每个数字的二进制表示中 1 的个数，并输出一个数组。

示例 1:
输入: n = 2
输出: [0,1,1]
解释:
0 --> 0
1 --> 1
2 --> 10

示例 2:
输入: n = 5
输出: [0,1,1,2,1,2]
解释:
0 --> 0
1 --> 1
2 --> 10
3 --> 11
4 --> 100
5 --> 101
  
说明 : 0 <= n <= 10^5
   
进阶:
给出时间复杂度为 O(n*sizeof(integer)) 的解答非常容易。但你可以在线性时间 O(n) 内用一趟扫描做到吗？你能进一步完善解法吗？
要求在C++或任何其他语言中不使用任何内置函数（如 C++ 中的 __builtin_popcount ）来执行此操作；要求算法的空间复杂度为 O(n) 。
    
注意：本题与主站 338 题相同：https://leetcode-cn.com/problems/counting-bits/

*/

// 判断最高有效位
class Solution1 {
public:
	vector<int> countBits(int n) {
		vector<int> bits(n + 1);
		int highBit = 0;
		for (int i = 1; i <= n; ++i) {
			if ((i&i - 1) == 0) highBit = i;
			bits[i] = bits[i - highBit] + 1;
		}
		return bits;
	}
};

// 判断最低有效位
class Solution2 {
public:
	vector<int> countBits(int n) {
		vector<int> bits(n + 1);
		for (int i = 1; i <= n; ++i) {
			bits[i] = bits[i >> 1] + (i & 1);
		}
		return bits;
	}
};

//判断最低设置位
class Solution3 {
public:
	vector<int> countBits(int n) {
		vector<int> bits(n + 1);
		for (int i = 1; i <= n; ++i) {
			bits[i] = bits[i&i - 1] + 1;
		}
		return bits;
	}
};

/*
 * https://leetcode.cn/problems/counting-bits/solution/bi-te-wei-ji-shu-by-leetcode-solution-0t1i/
 * @author 力扣官方题解
 */