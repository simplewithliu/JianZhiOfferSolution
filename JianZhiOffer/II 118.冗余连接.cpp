#include "header.h"

/*

LCR 118. 冗余连接

树可以看成是一个连通且无环的无向图

给定往一棵 n 个节点 (节点值 1～n) 的树中添加一条边后的图。
添加的边的两个顶点包含在 1 到 n 中间，且这条附加的边不属于树中已存在的边。
图的信息记录于长度为 n 的二维数组 edges ，edges[i] = [ai, bi] 表示图中在 ai 和 bi 之间存在一条边。

请找出一条可以删去的边，删除后可使得剩余部分是一个有着 n 个节点的树。
如果有多个答案，则返回数组 edges 中最后出现的那个。

示例 1：
输入: edges = [[1,2], [1,3], [2,3]]
输出: [2,3]

示例 2：
输入: edges = [[1,2], [2,3], [3,4], [1,4], [1,5]]
输出: [1,4]

提示:
n == edges.length
3 <= n <= 1000
edges[i].length == 2
1 <= ai < bi <= edges.length
ai != bi
edges 中无重复元素
给定的图是连通的

注意：本题与主站 684 题相同： https://leetcode-cn.com/problems/redundant-connection/

*/


class UF {
private:
	vector<int> id;

public:
	UF(int total) {
		for (int i = 0; i < total; ++i) id.push_back(i);
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
	}
	bool isConnected(int p, int q) { return find(p) == find(q); }
};

class Solution {
public:
	vector<int> findRedundantConnection(vector<vector<int>> &edges) {
		int len = edges.size();
		UF uf(len + 1);
		for (const auto &edge : edges) {
			int p = edge[0], q = edge[1];
			if (!uf.isConnected(p, q)) uf.unionpq(p, q);
			else return edge;
		}
		return {};
	}
};
// https://leetcode.cn/problems/redundant-connection/solutions/557616/rong-yu-lian-jie-by-leetcode-solution-pks2/
// @author https://leetcode.cn/u/leetcode-solution/
// 无向图连通性 考虑 并查集；有向图依赖性 考虑 深度广度优先、拓扑排序；
