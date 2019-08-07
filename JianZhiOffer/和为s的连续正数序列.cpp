#include "header.h"

/*

小明很喜欢数学,有一天他在做数学作业时,要求计算出9~16的和,他马上就写出了正确答案是100。
但是他并不满足于此,他在想究竟有多少种连续的正数序列的和为100(至少包括两个数)。
没多久,他就得到另一组连续正数和为100的序列:18,19,20,21,22。
现在把问题交给你,你能不能也很快的找出所有和为S的连续正数序列?

*/

class Solution {
public:
	vector<vector<int>> FindContinuousSequence(int sum)
	{
		if (sum < 3) return{};
		vector<vector<int>> res;
		int minnum = 1, maxnum = 2, tempsum = 3;
		while (minnum < maxnum)
		{
			if (tempsum == sum)
			{
				vector<int> temp;
				int tempnum = minnum;
				while (tempnum <= maxnum)
					temp.push_back(tempnum++);
				res.push_back(temp);
				++maxnum;
				tempsum += maxnum;
			}
			else if (tempsum < sum)
			{
				++maxnum;
				tempsum += maxnum;
			}
			else
			{
				tempsum -= minnum;
				++minnum;
			}
		}
		return res;
	}
};