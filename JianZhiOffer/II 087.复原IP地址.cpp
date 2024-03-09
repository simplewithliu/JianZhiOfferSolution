#include "header.h"

/*

有效IP地址正好由四个整数（每个整数位于 0 到 255 之间组成，且不能含有前导 0），整数之间用 '.' 分隔
例如："0.1.2.201" 和 "192.168.1.1" 是有效IP地址，但是 "0.011.255.245"、"192.168.1.312" 和 "192.168@1.1" 是无效IP地址
给定一个只包含数字的字符串 s ，用以表示一个 IP地址，返回所有可能的有效IP地址，这些地址可以通过在 s 中插入 '.' 来形成
你 不能 重新排序或删除 s 中的任何数字
你可以按 任何 顺序返回答案

示例 1：
输入：s = "25525511135"
输出：["255.255.11.135","255.255.111.35"]

示例 2：
输入：s = "0000"
输出：["0.0.0.0"]

示例 3：
输入：s = "101023"
输出：["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]

提示：
1 <= s.length <= 20
s 仅由数字组成

注意：本题与主站 93 题相同：https://leetcode-cn.com/problems/restore-ip-addresses/


*/

class Solution {
private:
	vector<string> res;
	vector<string> path;

public:
	vector<string> restoreIpAddresses(string s) {
		backtrack(s, 0);
		return res;
	}

private:
	void backtrack(const string &s, int start) {
		int len = s.size();
		if (start == len && path.size() == 4) {
			string str = path[0];
			for (int i = 1; i < path.size(); ++i) str += "." + path[i];
			res.push_back(str);
			return;
		}
		if (start < len && path.size() == 4) return;
		for (int subLen = 1; subLen <= 3; ++subLen) {
			if (start + subLen - 1 >= len) return;
			if (subLen != 1 && s[start] == '0') return;
			const string str = s.substr(start, subLen);
			if (subLen == 3 && stoi(str) > 255) return;
			path.push_back(str);
			backtrack(s, start + subLen);
			path.pop_back();
		}
	}
};
