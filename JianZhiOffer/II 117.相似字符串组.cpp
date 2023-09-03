#include "header.h"


/*

LCR 117. 相似字符串组

如果交换字符串 X 中的两个不同位置的字母，使得它和字符串 Y 相等，那么称 X 和 Y 两个字符串相似。如果这两个字符串本身是相等的，那它们也是相似的

例如，"tars" 和 "rats" 是相似的 (交换 0 与 2 的位置)； "rats" 和 "arts" 也是相似的，但是 "star" 不与 "tars"，"rats"，或 "arts" 相似

总之，它们通过相似性形成了两个关联组：{"tars", "rats", "arts"} 和 {"star"}，注意，"tars" 和 "arts" 是在同一组中，即使它们并不相似

形式上，对每个组而言，要确定一个单词在组中，只需要这个词和该组中至少一个单词相似

给你一个字符串列表 strs，列表中的每个字符串都是 strs 中其它所有字符串的一个字母异位词，请问 strs 中有多少个相似字符串组？

示例 1：
输入：strs = ["tars","rats","arts","star"]
输出：2

示例 2：
输入：strs = ["omv","ovm"]
输出：1

提示：
1 <= strs.length <= 300
1 <= strs[i].length <= 300
strs[i] 只包含小写字母
strs 中的所有单词都具有相同的长度，且是彼此的字母异位词

注意：本题与主站 839 题相同：https://leetcode-cn.com/problems/similar-string-groups/

*/

// DFS
class Solution {
private:
	bool isSimila(const string &str1, const string &str2) {
		// 输入数组中都是异位词
		int diff = 0;
		for (int i = 0; i < str1.size(); ++i) {
			if (str1[i] != str2[i]) ++diff;
		}
		return diff == 0 || diff == 2;
	}
	void dfs(int idx, vector<vector<int>> &adj, vector<char> &visited) {
		visited[idx] = true;
		for (const auto &n : adj[idx]) {
			if (!visited[n]) dfs(n, adj, visited);
		}
	}

public:
	int numSimilarGroups(vector<string> &strs) {
		int len = strs.size();
		vector<vector<int>> adj(len);
		for (int i = 0; i < len; ++i) {
			for (int j = i + 1; j < len; ++j) {
				if (isSimila(strs[i], strs[j])) {
					adj[i].push_back(j);
					adj[j].push_back(i);
				}
			}
		}
		vector<char> visited(len);
		int count = 0;
		for (int i = 0; i < len; ++i) {
			if (!visited[i]) {
				dfs(i, adj, visited);
				++count;
			}
		}
		return count;
	}
};
// https://leetcode.com/problems/similar-string-groups/editorial/

