#include "header.h"

/*

请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。
路径可以从矩阵中的任意一个格子开始，每一步可以在矩阵中向左，向右，向上，向下移动一个格子。
如果一条路径经过了矩阵中的某一个格子，则之后不能再次进入这个格子。 
例如 a b c e s f c s a d e e 这样的3 X 4 矩阵中包含一条字符串"bcced"的路径，
但是矩阵中不包含"abcb"路径，因为字符串的第一个字符b占据了矩阵中的第一行第二个格子之后，路径不能再次进入该格子。

*/

class Solution
{
public:
	bool hasPath(char *matrix, int rows, int cols, char *str)
	{
		if (!matrix || !str) return false;
		vector<vector<bool>> pathMap(rows, vector<bool>(cols, true));
		for (int i = 0; i < rows; ++i)
			for (int j = 0; j < cols; ++j)
			{
				if (findPath(matrix, i, j, rows, cols, str, pathMap))
					return true;
			}
		return false;
	}
	bool findPath(char *matrix, int row, int col, int rows, int cols, char *str, vector<vector<bool>> &pathMap)
	{
		if (*str == '\0') return true;
		if (row < 0 || row == rows || col < 0 || col == cols || pathMap[row][col] == false)
		{
			return false;
		}
		if (matrix[row*cols + col] == *str)
		{
			pathMap[row][col] = false;
			if (findPath(matrix, row + 1, col, rows, cols, str + 1, pathMap) ||
				findPath(matrix, row - 1, col, rows, cols, str + 1, pathMap) ||
				findPath(matrix, row, col + 1, rows, cols, str + 1, pathMap) ||
				findPath(matrix, row, col - 1, rows, cols, str + 1, pathMap))
			{
				return true;
			}
			else
			{
				pathMap[row][col] = true;
				return false;
			}
		}
		else
		{
			return false;
		}
	}
};