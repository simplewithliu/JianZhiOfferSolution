#include "header.h"

/*

请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。路径可以从矩阵中的任意一格开始，每一步可以在矩阵中向左、右、上、下移动一格。如果一条路径经过了矩阵的某一格，那么该路径不能再次进入该格子。
例如，在下面的3×4的矩阵中包含一条字符串“bfce”的路径。
[
 ["a","b","c","e"],
 ["s","f","c","s"],
 ["a","d","e","e"]
]
但矩阵中不包含字符串“abfb”的路径，因为字符串的第一个字符b占据了矩阵中的第一行第二个格子之后，路径不能再次进入这个格子。

示例 1：
输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
输出：true

示例 2：
输入：board = [["a","b"],["c","d"]], word = "abcd"
输出：false

提示：
1 <= board.length <= 200
1 <= board[i].length <= 200
注意：本题与主站 79 题相同：https://leetcode-cn.com/problems/word-search/


*/


class Solution {
public:
	bool exist(vector<vector<char>> &board, string word)
	{
		if (board.empty() || board[0].empty() || word.empty()) return false;
		int rows = board.size(), cols = board[0].size();
		vector<vector<char>> pathMap(rows, vector<char>(cols, false));
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				if (helper(board, i, j, rows, cols, word, 0, pathMap)) return true;
			}
		}
		return false;
	}
	bool helper(vector<vector<char>> &board, int row, int col, int rows, int cols, string &word, int idx, vector<vector<char>> &pathMap)
	{
		int len = word.size();
		if (idx == len) return true;
		if (row < 0 || row == rows || col < 0 || col == cols || pathMap[row][col] == true || board[row][col] != word[idx]) return false;
		pathMap[row][col] = true;
		bool res = helper(board, row + 1, col, rows, cols, word, idx + 1, pathMap) ||
			helper(board, row, col + 1, rows, cols, word, idx + 1, pathMap) ||
			helper(board, row - 1, col, rows, cols, word, idx + 1, pathMap) ||
			helper(board, row, col - 1, rows, cols, word, idx + 1, pathMap);
		pathMap[row][col] = false;
		return res;
	}
};