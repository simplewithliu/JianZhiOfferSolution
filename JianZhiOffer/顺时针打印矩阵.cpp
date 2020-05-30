#include "header.h"

/*

输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字，
例如，如果输入如下4 X 4矩阵： 
	1  2  3  4 
	5  6  7  8 
	9  10 11 12 
	13 14 15 16 
则依次打印出数字1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10.

*/

class Solution {
public:
	vector<int> printMatrix(vector<vector<int> > matrix)
	{
		if (matrix.empty() || matrix[0].empty()) return{};
		vector<int> res;
		int rows = matrix.size(), cols = matrix[0].size();
		int startRow = 0, endRow = rows - 1, startCol = 0, endCol = cols - 1;
		while (startRow <= endRow&&startCol <= endCol)
		{
			for (int i = startCol; i <= endCol; ++i)
			{
				res.push_back(matrix[startRow][i]);
			}
			++startRow;
			for (int i = startRow; i <= endRow; ++i)
			{
				res.push_back(matrix[i][endCol]);
			}
			--endCol;

			if (startRow > endRow || startCol>endCol) break;

			for (int i = endCol; i >= startCol; --i)
			{
				res.push_back(matrix[endRow][i]);
			}
			--endRow;
			for (int i = endRow; i >= startRow; --i)
			{
				res.push_back(matrix[i][startCol]);
			}
			++startCol;
		}
		return res;
	}
};