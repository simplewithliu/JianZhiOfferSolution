#include "header.h"

/*

输入一个正整数 target ，输出所有和为 target 的连续正整数序列（至少含有两个数）。
序列内的数字由小到大排列，不同序列按照首个数字从小到大排列。

示例 1：
输入：target = 9
输出：[[2,3,4],[4,5]]
 
示例 2：
输入：target = 15
输出：[[1,2,3,4,5],[4,5,6],[7,8]]
  
限制：1 <= target <= 10^5

*/

class Solution {
public:
	vector<vector<int>> findContinuousSequence(int target) 
	{
		if (target < 3) return {};
		vector<vector<int>> res;
		int minNum = 1, maxNum = 2, tempSum = 3;
		while (minNum < maxNum)
		{
			if (tempSum == target)
			{
				vector<int> temp;
				int tempNum = minNum;
				while (tempNum <= maxNum) temp.push_back(tempNum++);
				res.push_back(temp);
				++maxNum;
				tempSum += maxNum;
			}
			else if (tempSum < target)
			{
				++maxNum;
				tempSum += maxNum;
			}
			else
			{
				tempSum -= minNum;
				++minNum;
			}
		}
		return res;
	}
};

