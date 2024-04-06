#include "header.h"

/*

LCR 113. 课程表 II

现在你总共有 numCourses 门课需要选，记为 0 到 numCourses - 1
给你一个数组 prerequisites，其中 prerequisites[i] = [ai, bi]，表示在选修课程 ai 前必须先选修 bi

例如，想要学习课程 0，你需要先完成课程 1，我们用一个匹配来表示：[0,1]
返回你为了学完所有课程所安排的学习顺序。可能会有多个正确的顺序，你只要返回 任意一种 就可以了。如果不可能完成所有课程，返回一个空数组

示例 1：
输入：numCourses = 2, prerequisites = [[1,0]]
输出：[0,1]
解释：总共有 2 门课程。要学习课程 1，你需要先完成课程 0。因此，正确的课程顺序为 [0,1]

示例 2：
输入：numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
输出：[0,2,1,3]
解释：总共有 4 门课程。要学习课程 3，你应该先完成课程 1 和课程 2。并且课程 1 和课程 2 都应该排在课程 0 之后。
因此，一个正确的课程顺序是 [0,1,2,3] 。另一个正确的排序是 [0,2,1,3]

示例 3：
输入：numCourses = 1, prerequisites = []
输出：[0]

提示：
1 <= numCourses <= 2000
0 <= prerequisites.length <= numCourses * (numCourses - 1)
prerequisites[i].length == 2
0 <= ai, bi < numCourses
ai != bi
所有[ai, bi] 互不相同


注意：本题与主站 210 题相同：https://leetcode-cn.com/problems/course-schedule-ii/

*/

// 参考 LeetCode 210. 课程表 II
class Solution {
private:
	vector<char> flags;
	vector<int> res;
	vector<vector<int>> adj;

public:
	vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
		adj.resize(numCourses);
		flags.resize(numCourses);
		for (const auto &p : prerequisites) adj[p[0]].push_back(p[1]);
		for (int i = 0; i < numCourses; ++i) {
			if (!dfs(i)) return {};
		}
		return res;
	}

private:
	bool dfs(int i) {
		if (flags[i] == 1) return false; // 存在环
		if (flags[i] == -1) return true; // 节点已完成搜索
		// 0 表示未搜索，1 表示搜索中，-1 表示搜索完成
		flags[i] = 1;
		for (const auto &next : adj[i]) {
			if (!dfs(next)) return false;
		}
		flags[i] = -1;
		res.push_back(i);
		return true;
	}
};
