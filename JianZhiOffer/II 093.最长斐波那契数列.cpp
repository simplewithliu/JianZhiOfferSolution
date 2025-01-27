#include "header.h"

/*

剑指 Offer II 093. 最长斐波那契数列

如果序列 X_1, X_2, ..., X_n 满足下列条件，就说它是斐波那契式的：
1. n >= 3
2. 对于所有 i + 2 <= n，都有 X_i + X_{i+1} = X_{i+2}
给定一个严格递增的正整数数组形成序列 arr ，找到 arr 中最长的斐波那契式的子序列的长度。如果一个不存在，返回 0
（回想一下，子序列是从原序列 arr 中派生出来的，它从 arr 中删掉任意数量的元素（也可以不删），而不改变其余元素的顺序。例如， [3, 5, 8] 是 [3, 4, 5, 6, 7, 8] 的一个子序列）

示例 1：
输入: arr = [1,2,3,4,5,6,7,8]
输出: 5
解释: 最长的斐波那契式子序列为 [1,2,3,5,8] 。

示例 2：
输入: arr = [1,3,7,11,12,14,18]
输出: 3
解释: 最长的斐波那契式子序列有 [1,11,12]、[3,11,14] 以及 [7,11,18] 。

提示：
3 <= arr.length <= 1000
1 <= arr[i] < arr[i + 1] <= 10^9

注意：本题与主站 873 题相同： https://leetcode-cn.com/problems/length-of-longest-fibonacci-subsequence/

*/

// 备忘录
class Solution1 {
public:
	int lenLongestFibSubseq(vector<int> &arr) {
		int len = arr.size();
		vector<vector<int>> memo(len, vector<int>(len, -1));
		unordered_map<int, int> mp;
		for (int i = 0; i < arr.size(); ++i) mp[arr[i]] = i;
		int ans = 0;
		for (int i = 2; i < len; ++i) {
			for (int j = i - 1; j > 0; --j) {
				ans = max(ans, solve(arr, j, i, memo, mp));
			}
		}
		return ans;
	}

private:
	int solve(vector<int> &arr, int j, int i, vector<vector<int>> &memo,
		unordered_map<int, int> &mp) {
		int key = arr[i] - arr[j];
		if (!mp.count(key) || mp[key] >= j) return 0;
		if (memo[j][i] != -1) return memo[j][i];
		return memo[j][i] = max(1 + solve(arr, mp[key], j, memo, mp), 3);
	}
};

// 自底而上的动态规划
class Solution2 {
public:
	int lenLongestFibSubseq(vector<int> &arr) {
		unordered_map<int, int> indices;
		int len = arr.size();
		for (int i = 0; i < len; ++i)
			indices[arr[i]] = i;
		vector<vector<int>> dp(len, vector<int>(len, 0));
		int ans = 0;
		for (int i = 0; i < len; ++i) {
			for (int j = i - 1; j > 0; --j) {
				int key = arr[i] - arr[j];
				if (indices.count(key) && indices[key] < j) {
					dp[j][i] = max(dp[indices[key]][j] + 1, 3);
				}
				ans = max(ans, dp[j][i]);
			}
		}
		return ans;
	}
};

