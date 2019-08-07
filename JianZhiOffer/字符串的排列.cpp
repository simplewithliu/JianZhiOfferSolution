#include "header.h"

/*

输入一个字符串,按字典序打印出该字符串中字符的所有排列。
例如输入字符串abc,则打印出由字符a,b,c所能排列出来的所有字符串abc,acb,bac,bca,cab和cba。

*/

class Solution {
public:
	vector<string> Permutation(string str)
	{
		if (str.empty()) return{};
		vector<string> res;
		dfs(str, 0, res);
		sort(res.begin(), res.end());
		return res;
	}
	void dfs(string str, int i, vector<string> &res)
	{
		int len = str.size();
		if (i == len)
		{
			res.push_back(str);
			return;
		}
		for (int j = i; j < len; ++j)
		{
			if (i != j&&str[i] == str[j])
				continue;
			swap(str[i], str[j]);
			dfs(str, i + 1, res);
			swap(str[i], str[j]);
		}
	}
};