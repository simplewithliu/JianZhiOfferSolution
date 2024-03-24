#include "header.h"

/*

LCR 111. 除法求值

给你一个变量对数组 equations 和一个实数值数组 values 作为已知条件，其中 equations[i] = [Ai, Bi] 和 values[i] 共同表示等式 Ai / Bi = values[i] 。每个 Ai 或 Bi 是一个表示单个变量的字符串。

另有一些以数组 queries 表示的问题，其中 queries[j] = [Cj, Dj] 表示第 j 个问题，请你根据已知条件找出 Cj / Dj = ? 的结果作为答案。

返回 所有问题的答案 。如果存在某个无法确定的答案，则用 -1.0 替代这个答案。如果问题中出现了给定的已知条件中没有出现的字符串，也需要用 -1.0 替代这个答案。

注意：输入总是有效的，你可以假设除法运算中不会出现除数为 0 的情况，且不存在任何矛盾的结果。
注意：未在等式列表中出现的变量是未定义的，因此无法确定它们的答案。

示例 1：
输入：equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
输出：[6.00000,0.50000,-1.00000,1.00000,-1.00000]
解释：
条件：a / b = 2.0, b / c = 3.0
问题：a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
结果：[6.0, 0.5, -1.0, 1.0, -1.0 ]
注意：x 是未定义的 => -1.0

示例 2：
输入：equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0], queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
输出：[3.75000,0.40000,5.00000,0.20000]

示例 3：
输入：equations = [["a","b"]], values = [0.5], queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
输出：[0.50000,2.00000,-1.00000,-1.00000]

提示：
1 <= equations.length <= 20
equations[i].length == 2
1 <= Ai.length, Bi.length <= 5
values.length == equations.length
0.0 < values[i] <= 20.0
1 <= queries.length <= 20
queries[i].length == 2
1 <= Cj.length, Dj.length <= 5
Ai, Bi, Cj, Dj 由小写英文字母与数字组成

注意：本题与主站 399 题相同： https://leetcode-cn.com/problems/evaluate-division/


*/

// DFS
class Solution1 {
private:
	unordered_map<string, unordered_map<string, double>> adjacent;
	unordered_set<string> visited;

public:
	vector<double> calcEquation(vector<vector<string>> &equations,
		vector<double> &values,
		vector<vector<string>> &queries) {
		vector<double> res;
		build(equations, values);
		for (auto q : queries) {
			double v = dfs(q[0], q[1]);
			if (v != -1) {
				res.push_back(v);
				adjacent[q[0]][q[1]] = v;
				adjacent[q[1]][q[0]] = 1 / v;
			} else {
				res.push_back(-1);
			}
		}
		return res;
	}

private:
	void build(vector<vector<string>> &equations, vector<double> &values) {
		for (int i = 0; i < equations.size(); ++i) {
			string a = equations[i][0];
			string b = equations[i][1];
			double v = values[i];
			adjacent[a][b] = v;
			adjacent[b][a] = 1 / v;
		}
	}
	double dfs(string begin, string end) {
		if (!adjacent.count(begin) || !adjacent.count(end)) return -1;
		if (visited.count(begin)) return -1;
		if (adjacent[begin].count(end)) return adjacent[begin][end];
		// 注意visited是全局变量，返回时不要忘记删除当前遍历元素
		// 为了避免忘记，使用一个外围作用域的res
		double res = -1.0;
		visited.insert(begin);
		for (auto p : adjacent[begin]) {
			double v = dfs(p.first, end);
			if (v != -1) {
				res = v * p.second;
				break;
			}
		}
		visited.erase(begin);
		return res;
	}
};


// BFS
class Solution2 {
private:
	unordered_map<string, int> equ;
	vector<vector<pair<int, double>>> adjacent;
	unordered_set<int> visited;

public:
	vector<double> calcEquation(vector<vector<string>> &equations,
		vector<double> &values,
		vector<vector<string>> &queries) {
		int len = equations.size();
		int id = 0;
		for (int i = 0; i < len; ++i) {
			if (!equ.count(equations[i][0])) equ[equations[i][0]] = id++;
			if (!equ.count(equations[i][1])) equ[equations[i][1]] = id++;
		}
		adjacent.resize(id);
		build(equations, values);
		vector<double> res;
		for (const auto &q : queries) {
			// 注意visited是全局的，这里每次开始新的搜索直接clear
			visited.clear();
			double v = bfs(q[0], q[1]);
			if (v != -1) {
				res.push_back(v);
				adjacent[equ[q[0]]].push_back({ equ[q[1]], v });
				adjacent[equ[q[1]]].push_back({ equ[q[0]], 1.0 / v });
			} else {
				res.push_back(-1.0);
			}
		}
		return res;
	}

private:
	// 建图时优化：使用哈希表将字符串映射为整数
	void build(vector<vector<string>> &equations, vector<double> &values) {
		for (int i = 0; i < equations.size(); ++i) {
			int va = equ[equations[i][0]], vb = equ[equations[i][1]];
			adjacent[va].push_back({ vb, values[i] });
			adjacent[vb].push_back({ va, 1.0 / values[i] });
		}
	}
	double bfs(string begin, string end) {
		if (!equ.count(begin) || !equ.count(end)) return -1.0;
		// 这里的辅助队列相当于存储了节点跨边与权重
		queue<pair<int, double>> q;
		q.push({ equ[begin], 1.0 });
		while (!q.empty()) {
			const auto tmp = q.front();
			q.pop();
			if (visited.count(tmp.first)) continue;
			if (tmp.first == equ[end]) return tmp.second;
			visited.insert(tmp.first);
			for (const auto &p : adjacent[tmp.first]) {
				q.push({ p.first, tmp.second * p.second });
			}
		}
		return -1.0;
	}
};


// 并查集
class UF {
private:
	vector<int> id;
	vector<double> weight;

public:
	UF(int total) {
		for (int i = 0; i < total; ++i) {
			id.push_back(i);
			weight.push_back(1.0);
		}
	}
	int find(int x) {
		if (id[x] != x) {
			int parent = id[x];
			id[x] = find(parent);
			weight[x] *= weight[parent];
		}
		return id[x];
	}
	void unionpq(int p, int q, double value) {
		int pRoot = find(p);
		int qRoot = find(q);
		if (pRoot == qRoot) return;
		id[pRoot] = qRoot;
		weight[pRoot] = weight[q] * value / weight[p];
	}
	double isConnected(int p, int q) {
		int pRoot = find(p);
		int qRoot = find(q);
		if (pRoot == qRoot) return weight[p] / weight[q];
		return -1.0;
	}
};

class Solution3 {
public:
	vector<double> calcEquation(vector<vector<string>> &equations,
		vector<double> &values,
		vector<vector<string>> &queries) {
		int len = equations.size();
		UF uf(2 * len);
		unordered_map<string, int> m;
		int id = 0;
		for (int i = 0; i < len; ++i) {
			string a = equations[i][0];
			string b = equations[i][1];
			if (!m.count(a)) m[a] = id++;
			if (!m.count(b)) m[b] = id++;
			uf.unionpq(m[a], m[b], values[i]);
		}
		int queriesLen = queries.size();
		vector<double> res;
		for (auto q : queries) {
			int id0 = m.count(q[0]) ? m[q[0]] : -1;
			int id1 = m.count(q[1]) ? m[q[1]] : -1;
			if (id0 == -1 || id1 == -1) res.push_back(-1.0);
			else res.push_back(uf.isConnected(id0, id1));
		}
		return res;
	}
};

// Floyd 算法，预先计算出任意两点之间的距离
class Solution4 {
private:
	unordered_map<string, int> equ;
	vector<vector<double>> graph;

public:
	vector<double> calcEquation(vector<vector<string>> &equations,
		vector<double> &values,
		vector<vector<string>> &queries) {
		int len = equations.size();
		int id = 0;
		for (int i = 0; i < len; ++i) {
			if (!equ.count(equations[i][0])) equ[equations[i][0]] = id++;
			if (!equ.count(equations[i][1])) equ[equations[i][1]] = id++;
		}
		graph.resize(id, vector<double>(id, -1.0));
		build(equations, values);
		for (int k = 0; k < id; ++k) {
			for (int i = 0; i < id; ++i) {
				for (int j = 0; j < id; ++j) {
					// 注意这里的路径如果太长可能丢失精度，越早拿到结果越好
					if (graph[i][j] == -1.0 && graph[i][k] > 0 && graph[k][j] > 0) {
						graph[i][j] = graph[i][k] * graph[k][j];
					}
				}
			}
		}
		vector<double> res;
		for (const auto &q : queries) {
			double result = -1.0;
			if (equ.count(q[0]) && equ.count(q[1])) {
				int va = equ[q[0]], vb = equ[q[1]];
				result = graph[va][vb] == -1.0 ? result : graph[va][vb];
			}
			res.push_back(result);
		}
		return res;
	}

private:
	void build(vector<vector<string>> &equations, vector<double> &values) {
		for (int i = 0; i < equations.size(); ++i) {
			int va = equ[equations[i][0]], vb = equ[equations[i][1]];
			graph[va][vb] = values[i];
			graph[vb][va] = 1.0 / values[i];
		}
	}
};

