#include "header.h"

/*

给定两个整数 a 和 b，求它们的除法的商 a/b，要求不得使用乘号 '*'、除号 '/' 以及求余符号 '%'

注意：
整数除法的结果应当截去（truncate）其小数部分，例如：truncate(8.345) = 8 以及 truncate(-2.7335) = -2
假设我们的环境只能存储 32 位有符号整数，其数值范围是 [−2^31, 2^31−1]。本题中，如果除法结果溢出，则返回 2^31 − 1

示例 1：
输入：a = 15, b = 2
输出：7
解释：15/2 = truncate(7.5) = 7

示例 2：
输入：a = 7, b = -3
输出：-2
解释：7/-3 = truncate(-2.33333..) = -2

示例 3：
输入：a = 0, b = 1
输出：0

示例 4：
输入：a = 1, b = 1
输出：1

提示:
-2^31 <= a, b <= 2^31 - 1
b != 0

注意：本题与主站 29 题相同：https://leetcode-cn.com/problems/divide-two-integers/

*/

class Solution {
public:
	int divide(int a, int b) {
		if (a == INT_MIN) {
			if (b == -1) return INT_MAX;
			else if (b == 1) return INT_MIN;
			else return (b & 1) == 1 ? divide(a + 1, b) : divide(a / 2, b / 2);
		} else if (b == INT_MIN) {
			return 0;
		}

		int pa = abs(a), pb = abs(b), res = 0;
		int sign = (a > 0) ^ (b > 0) ? -1 : 1;
		while (pa >= pb) {
			int temp = pb, m = 1;
			while ((temp << 1) <= pa && (temp << 1) > 0) {
				temp <<= 1;
				m <<= 1;
			}
			pa -= temp;
			res += m;
		}
		return sign*res;
	}
};