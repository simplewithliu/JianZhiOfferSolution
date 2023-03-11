#include "header.h"

/*

剑指 Offer II 106. 二分图

存在一个无向图，图中有 n 个节点。其中每个节点都有一个介于 0 到 n - 1 之间的唯一编号。给你一个二维数组 graph，其中 graph[u] 是一个节点数组，由节点 u 的邻接节点组成。
形式上，对于 graph[u] 中的每个 v，都存在一条位于节点 u 和节点 v 之间的无向边。该无向图同时具有以下属性：
不存在自环（graph[u] 不包含 u）
不存在平行边（graph[u] 不包含重复值）
如果 v 在 graph[u] 内，那么 u 也应该在 graph[v] 内（该图是无向图）
这个图可能不是连通图，也就是说两个节点 u 和 v 之间可能不存在一条连通彼此的路径

二分图定义：如果能将一个图的节点集合分割成两个独立的子集 A 和 B ，并使图中的每一条边的两个节点一个来自 A 集合，一个来自 B 集合，就将这个图称为二分图
如果图是二分图，返回 true；否则，返回 false

示例 1：
输入：graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
输出：false
解释：不能将节点分割成两个独立的子集，以使每条边都连通一个子集中的一个节点与另一个子集中的一个节点。

示例 2：
输入：graph = [[1,3],[0,2],[1,3],[0,2]]
输出：true
解释：可以将节点分成两组: {0, 2} 和 {1, 3} 。

提示：
graph.length == n
1 <= n <= 100
0 <= graph[u].length < n
0 <= graph[u][i] <= n - 1
graph[u] 不会包含 u
graph[u] 的所有值 互不相同
如果 graph[u] 包含 v，那么 graph[v] 也会包含 u

注意：本题与主站 785 题相同： https://leetcode-cn.com/problems/is-graph-bipartite/


*/

// DFS
class Solution1 {
public:
	bool isBipartite(vector<vector<int>> &graph) {
		vector<int> visited(graph.size());
		for (int i = 0; i < graph.size(); ++i) {
			if (!visited[i] && !dfs(graph, i, 1, visited)) return false;
		}
		return true;
	}

private:
	bool dfs(vector<vector<int>> &graph, int u, int color,
		vector<int> &visited) {
		if (visited[u]) return visited[u] == color;
		visited[u] = color;
		for (int v : graph[u]) {
			if (!dfs(graph, v, -color, visited)) return false;
		}
		return true;
	}
};

// BFS
class Solution2 {
public:
	bool isBipartite(vector<vector<int>> &graph) {
		vector<int> visted(graph.size());
		queue<int> q;
		for (int i = 0; i < graph.size(); ++i) {
			if (visted[i]) continue;
			q.push(i);
			visted[i] = 1;
			while (!q.empty()) {
				int u = q.front();
				q.pop();
				for (int v : graph[u]) {
					if (visted[v] == visted[u]) return false;
					if (!visted[v]) {
						visted[v] = -visted[u];
						q.push(v);
					}
				}
			}
		}
		return true;
	}
};

// 并查集
class UF {
private:
	vector<int> id;

public:
	UF(int total) {
		for (int i = 0; i < total; ++i) id.push_back(i);
	}
	int find(int x) {
		if (id[x] != x) id[x] = find(id[x]);
		return id[x];
	}
	void unionpq(int p, int q) {
		int pRoot = find(p);
		int qRoot = find(q);
		if (pRoot == qRoot) return;
		id[pRoot] = qRoot;
	}
	bool isConnected(int p, int q) { return find(p) == find(q); }
};

class Solution3 {
public:
	bool isBipartite(vector<vector<int>> &graph) {
		UF uf(graph.size());
		for (int i = 0; i < graph.size(); ++i) {
			for (int v : graph[i]) {
				if (uf.isConnected(v, i)) return false;
				uf.unionpq(graph[i][0], v);
			}
		}
		return true;
	}
};

// https://leetcode.cn/problems/is-graph-bipartite/solutions/333138/bfs-dfs-bing-cha-ji-san-chong-fang-fa-pan-duan-er-/
// @author https://leetcode.cn/u/sweetiee/

