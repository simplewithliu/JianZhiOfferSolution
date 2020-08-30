#include "header.h"

/*

假设把某股票的价格按照时间先后顺序存储在数组中，请问买卖该股票一次可能获得的最大利润是多少？

示例 1:
输入: [7,1,5,3,6,4]
输出: 5
解释: 在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格。
 
示例 2:
输入: [7,6,4,3,1]
输出: 0
解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。
  
限制：0 <= 数组长度 <= 10^5

注意：本题与主站 121 题相同：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/

*/

class Solution1 {
public:
	int maxProfit(vector<int> &prices) 
	{
		int minCost = INT_MAX;
		int profit = 0;
		for (int p : prices)
		{
			minCost = min(minCost, p);
			profit = max(profit, p - minCost);
		}
		return profit;
	}
};

//参考LeetCode 121
class Solution2 {
public:
	int maxProfit(vector<int> &prices)
	{
		int len = prices.size();
		if (len == 0) return 0;
		vector<vector<int>> dp(len, vector<int>(2, 0));
		for (int i = 0; i < len; ++i)
		{
			if (i - 1 == -1)
			{
				dp[i][0] = 0;
				dp[i][1] = -prices[i];
				continue;
			}
			dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
			dp[i][1] = max(dp[i - 1][1], -prices[i]);
		}
		return dp[len - 1][0];
	}
};