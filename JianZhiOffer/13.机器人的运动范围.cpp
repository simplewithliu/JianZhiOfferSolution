#include "header.h"

/*

地上有一个m行n列的方格，从坐标 [0,0] 到坐标 [m-1,n-1] 。
一个机器人从坐标 [0, 0] 的格子开始移动，它每次可以向左、右、上、下移动一格（不能移动到方格外），也不能进入行坐标和列坐标的数位之和大于k的格子。
例如，当k为18时，机器人能够进入方格 [35, 37] ，因为3+5+3+7=18。但它不能进入方格 [35, 38]，因为3+5+3+8=19。请问该机器人能够到达多少个格子？

示例 1：
输入：m = 2, n = 3, k = 1
输出：3
 
示例 2：
输入：m = 3, n = 1, k = 0
输出：1

提示：
1 <= n,m <= 100
0 <= k <= 20

*/

//DFS
class Solution1 {
public:
	int movingCount(int m, int n, int k) 
	{
		if (m <= 0 || n <= 0) return 0;
		vector<vector<char>> visited(m, vector<char>(n, false));
		return helper(m, n, 0, 0, k, visited);
	}
	int helper(int m, int n, int i, int j, int k, vector<vector<char>> &visited)
	{
		if (i == m || j == n || visited[i][j] || (get(i) + get(j)) > k) return 0;
		visited[i][j] = true;
		return 1 + helper(m, n, i + 1, j, k, visited) + helper(m, n, i, j + 1, k, visited);
	}
	int get(int num) 
	{
		int res = 0;
		while (num)
		{
			res += num % 10;
			num /= 10;
		}
		return res;
	}
};

//BFS
class Solution2 {
public:
	int movingCount(int m, int n, int k)
	{
		if (m <= 0 || n <= 0) return 0;
		vector<vector<char>> visited(m, (vector<char>(n, false)));
		int res = 0;
		queue<pair<int,int>> q;
		q.push({ 0, 0 });
		while (!q.empty())
		{
			pair<int, int> temp = q.front();
			q.pop();
			int i = temp.first, j = temp.second;
			if (i == m || j == n || visited[i][j] == true || (get(i) + get(j) > k)) continue;
			visited[i][j] = true;
			++res;
			q.push({ i + 1, j });
			q.push({ i, j + 1 });
		}
		return res;
	}
	int get(int num)
	{
		int res = 0;
		while (num)
		{
			res += num % 10;
			num /= 10;
		}
		return res;
	}
};