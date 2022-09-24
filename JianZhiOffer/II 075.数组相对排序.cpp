#include "header.h"

/*

给你两个数组，arr1 和 arr2，arr2 中的元素各不相同，arr2 中的每个元素都出现在 arr1 中。
对 arr1 中的元素进行排序，使 arr1 中项的相对顺序和 arr2 中的相对顺序相同。
未在 arr2 中出现过的元素需要按照升序放在 arr1 的末尾。

示例 1：
输入：arr1 = [2,3,1,3,2,4,6,7,9,2,19], arr2 = [2,1,4,3,9,6]
输出：[2,2,2,1,4,3,3,9,6,7,19]

示例  2:
输入：arr1 = [28,6,22,8,44,17], arr2 = [22,28,8,6]
输出：[22,28,8,6,17,44]
  
提示：
1 <= arr1.length, arr2.length <= 1000
0 <= arr1[i], arr2[i] <= 1000
arr2 中的元素 arr2[i]  各不相同 
arr2 中的每个元素 arr2[i] 都出现在 arr1 中

注意：本题与主站 1122 题相同：https://leetcode-cn.com/problems/relative-sort-array/

*/

// 哈希表方法
class Solution1 {
public:
	vector<int> relativeSortArray(vector<int> &arr1, vector<int> &arr2) {
		unordered_map<int, int> rank;
		for (int i = 0; i < arr2.size(); ++i) rank[arr2[i]] = i;
		sort(arr1.begin(), arr1.end(), [&](int first, int second) -> bool {
			if (rank.count(first)) return rank.count(second) ? rank[first] < rank[second] : true;
			else return rank.count(second) ? false : first < second;
		});
		return arr1;
	}
};

// 计数排序法
class Solution2 {
public:
	vector<int> relativeSortArray(vector<int> &arr1, vector<int> &arr2) {
		int upper = *max_element(arr1.begin(), arr1.end());
		vector<int> freq(upper + 1);
		for (int n : arr1) ++freq[n];
		vector<int> res;
		for (int n : arr2) {
			while (freq[n]--) res.push_back(n);
		}
		for (int n = 0; n <= upper; ++n) {
			if (freq[n] > 0) {
				while (freq[n]--) res.push_back(n);
			}
		}
		return res;
	}
};