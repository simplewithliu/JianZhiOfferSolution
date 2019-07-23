#include "header.h"

/*

地上有一个m行和n列的方格。一个机器人从坐标0,0的格子开始移动，
每一次只能向左，右，上，下四个方向移动一格，
但是不能进入行坐标和列坐标的数位之和大于k的格子。 
例如，当k为18时，机器人能够进入方格（35,37），因为3+5+3+7 = 18。
但是，它不能进入方格（35,38），因为3+5+3+8 = 19。
请问该机器人能够达到多少个格子？

*/


class Solution {
public:
	int movingCount(int threshold, int rows, int cols)
	{
		if (rows <= 0 || cols <= 0) return 0;
		int num = 0;
		vector<vector<bool>> pathMap(rows, vector<bool>(cols, false));
		dfs(threshold, 0, 0, rows, cols, pathMap, num);
		return num;
	}
	void dfs(int k, int row, int col, int rows, int cols, vector<vector<bool>> &pathMap, int &num)
	{
		if (row == rows || row < 0 || col == cols || col < 0 || pathMap[row][col])
			return;
		int count = 0, i = row, j = col;
		while (i || j)
		{
			count += i % 10 + j % 10;
			i /= 10;
			j /= 10;
		}
		if (count>k) return;
		num += 1;
		pathMap[row][col] = true;
		dfs(k, row + 1, col, rows, cols, pathMap, num);
		dfs(k, row - 1, col, rows, cols, pathMap, num);
		dfs(k, row, col + 1, rows, cols, pathMap, num);
		dfs(k, row, col - 1, rows, cols, pathMap, num);
	}
};
