#include "header.h"

/*

LCR 119. 最长连续序列

给定一个未排序的整数数组 nums，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度
请你设计并实现时间复杂度为 O(n) 的算法解决此问题。

示例 1：
输入：nums = [100,4,200,1,3,2]
输出：4
解释：最长数字连续序列是 [1, 2, 3, 4]。它的长度为 4。

示例 2：
输入：nums = [0,3,7,2,5,8,4,6,0,1]
输出：9

提示：
0 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9

注意：本题与主站 128 题相同： https://leetcode-cn.com/problems/longest-consecutive-sequence/

*/


// 并查集
class UF {
private:
	vector<int> id;
	vector<int> size;

public:
	UF(int total) {
		for (int i = 0; i < total; ++i) {
			id.push_back(i);
			size.push_back(1);
		}
	}
	int find(int x) {
		if (x != id[x]) id[x] = find(id[x]);
		return id[x];
	}
	void unionpq(int p, int q) {
		int pRoot = find(p);
		int qRoot = find(q);
		if (pRoot == qRoot) return;
		id[pRoot] = qRoot;
		size[qRoot] += size[pRoot];
	}
	int getMaxSeqLen() {
		int maxLen = 0;
		for (int i = 0; i < id.size(); ++i) {
			if (i == id[i]) maxLen = max(maxLen, size[i]);
		}
		return maxLen;
	}
};

class Solution1 {
public:
	int longestConsecutive(vector<int> &nums) {
		unordered_map<int, int> m;
		int len = nums.size();
		UF uf(len);
		for (int i = 0; i < len; ++i) {
			if (m.count(nums[i])) continue;
			if (m.count(nums[i] + 1)) uf.unionpq(i, m[nums[i] + 1]);
			if (m.count(nums[i] - 1)) uf.unionpq(i, m[nums[i] - 1]);
			m[nums[i]] = i;
		}
		return uf.getMaxSeqLen();
	}
};



// 哈希表
class Solution2 {
public:
	int longestConsecutive(vector<int> &nums) {
		unordered_set<int> s;
		for (const int &n : nums) s.insert(n);
		int longestSeq = 0;
		for (const int &n : s) {
			if (!s.count(n - 1)) {
				int cur = n;
				int curLen = 1;
				while (s.count(++cur)) ++curLen;
				longestSeq = max(longestSeq, curLen);
			}
		}
		return longestSeq;
	}
};

