#include "header.h"

/*

LCR 085. 括号生成

数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合

示例 1：
输入：n = 3
输出：["((()))","(()())","(())()","()(())","()()()"]

示例 2：
输入：n = 1
输出：["()"]

提示：
1 <= n <= 8

注意：本题与主站 22 题相同： https://leetcode-cn.com/problems/generate-parentheses/

*/


class Solution {
private:
	vector<string> res;

public:
	vector<string> generateParenthesis(int n) {
		if (n <= 0) return res;
		backtrack("", n, 0, 0);
		return res;
	}

private:
	void backtrack(string path, int n, int left, int right) {
		if (left > n || right > left) return;
		if (path.size() == n * 2) {
			res.push_back(path);
			return;
		}
		backtrack(path + '(', n, left + 1, right);
		backtrack(path + ')', n, left, right + 1);
	}
};

