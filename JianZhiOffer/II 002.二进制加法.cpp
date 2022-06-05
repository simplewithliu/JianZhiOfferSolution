#include "header.h"

/*

给定两个 01 字符串 a 和 b ，请计算它们的和，并以二进制字符串的形式输出。
输入为非空字符串且只包含数字 1 和 0。

示例 1:
输入: a = "11", b = "10"
输出: "101"

示例 2:
输入: a = "1010", b = "1011"
输出: "10101"


提示：
每个字符串仅由字符 '0' 或 '1' 组成。
1 <= a.length, b.length <= 10^4
字符串如果不是 "0" ，就都不含前导零。

注意：本题与主站 67 题相同：https://leetcode-cn.com/problems/add-binary/

*/

class Solution {
public:
	string addBinary(string a, string b) {
		string res;
		int i = a.size() - 1, j = b.size() - 1, flag = 0;
		while (i >= 0 || j >= 0) {
			int sum = flag;
			if (i >= 0) sum += a[i--] - '0';
			if (j >= 0) sum += b[j--] - '0';
			res.append(to_string(sum % 2));
			flag = sum >> 1;
		}
		if (flag) res.append(to_string(flag));
		reverse(res.begin(), res.end());
		return res;
	}
};
/*
 * 题目可以使用位运算，通过 异或 和 位与 操作得到结果，但整数无法避免溢出，只能在类似python中整数无长度要求的情境下使用
 * https://leetcode.cn/problems/JFETK5/solution/er-jin-zhi-jia-fa-by-leetcode-solution-fa6t/ 
 * @author 力扣官方题解
 */