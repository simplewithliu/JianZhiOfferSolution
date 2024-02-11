#include "header.h"

/*

LCR 072. x 的平方根

给你一个非负整数 x，计算并返回 x 的 算术平方根
由于返回类型是整数，结果只保留整数部分，小数部分将被舍去

注意：不允许使用任何内置指数函数和算符，例如 pow(x, 0.5) 或者 x ** 0.5

示例 1：
输入：x = 4
输出：2

示例 2：
输入：x = 8
输出：2
解释：8 的算术平方根是 2.82842...，由于返回类型是整数，小数部分将被舍去

提示：
0 <= x <= 2^31 - 1

注意：本题与主站 69 题相同： https://leetcode-cn.com/problems/sqrtx/

*/

class Solution {
public:
	int mySqrt(int x) {
		if (x <= 1) return x;
		int lo = 1, hi = x / 2;
		while (lo < hi) {
			int mi = lo + (hi - lo + 1) / 2;
			mi > x / mi ? hi = mi - 1 : lo = mi;
		}
		return lo;
	}
};

