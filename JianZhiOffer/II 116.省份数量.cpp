#include "header.h"

/*

LCR 116. 省份数量

有 n 个城市，其中一些彼此相连，另一些没有相连。如果城市 a 与城市 b 直接相连，且城市 b 与城市 c 直接相连，那么城市 a 与城市 c 间接相连。

省份 是一组直接或间接相连的城市，组内不含其他没有相连的城市。

给你一个 n x n 的矩阵 isConnected ，其中 isConnected[i][j] = 1 表示第 i 个城市和第 j 个城市直接相连，而 isConnected[i][j] = 0 表示二者不直接相连。
返回矩阵中 省份 的数量。

示例 1：
输入：isConnected = [[1,1,0],[1,1,0],[0,0,1]]
输出：2

示例 2：
输入：isConnected = [[1,0,0],[0,1,0],[0,0,1]]
输出：3

提示：
1 <= n <= 200
n == isConnected.length
n == isConnected[i].length
isConnected[i][j] 为 1 或 0
isConnected[i][i] == 1
isConnected[i][j] == isConnected[j][i]

注意：本题与主站 547 题相同： https://leetcode-cn.com/problems/number-of-provinces/

*/

// DFS
class Solution1 {
private:
	vector<char> visited;

public:
	int findCircleNum(vector<vector<int>> &isConnected) {
		int cities = isConnected.size();
		visited.resize(cities, false);
		int provinces = 0;
		for (int i = 0; i < cities; ++i) {
			if (!visited[i]) {
				dfs(isConnected, i);
				++provinces;
			}
		}
		return provinces;
	}

private:
	void dfs(vector<vector<int>> &isConnected, int i) {
		int len = isConnected.size();
		for (int j = 0; j < len; ++j) {
			if (isConnected[i][j] == 1 && !visited[j]) {
				visited[j] = true;
				dfs(isConnected, j);
			}
		}
	}
};


// BFS
class Solution2 {
public:
	int findCircleNum(vector<vector<int>> &isConnected) {
		int cities = isConnected.size();
		vector<char> visited(cities, false);
		int provinces = 0;
		queue<int> q;
		for (int i = 0; i < cities; ++i) {
			if (!visited[i]) {
				++provinces;
				q.push(i);
				visited[i] = true;
				while (!q.empty()) {
					int tmp = q.front();
					q.pop();
					for (int j = 0; j < cities; ++j) {
						if (isConnected[tmp][j] == 1 && !visited[j]) {
							visited[j] = true;
							q.push(j);
						}
					}
				}
			}
		}
		return provinces;
	}
};


// 并查集
class UF {
private:
	vector<int> id;

public:
	int count;
	UF(int total) {
		count = 0;
		for (int i = 0; i < total; ++i) {
			id.push_back(i);
			++count;
		}
	}
	int find(int x) {
		if (x != id[x]) id[x] = find(id[x]);
		return id[x];
	}
	void unionpq(int p, int q) {
		int pRoot = find(p);
		int qRoot = find(q);
		if (pRoot == qRoot) return;
		id[pRoot] = qRoot;
		--count;
	}

	// bool isConnected(int p, int q) { return find(p) == find(q); }
};

class Solution3 {
public:
	int findCircleNum(vector<vector<int>> &isConnected) {
		int len = isConnected.size();
		UF uf(len);
		for (int i = 0; i < len; ++i) {
			for (int j = 0; j < i; ++j) {
				if (isConnected[i][j]) uf.unionpq(i, j);
			}
		}
		return uf.count;
	}
};

