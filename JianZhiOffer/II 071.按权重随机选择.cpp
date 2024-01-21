#include "header.h"

/*

LCR 071. 按权重随机选择

给你一个 下标从 0 开始 的正整数数组 w, 其中 w[i] 代表第 i 个下标的权重
请你实现一个函数 pickIndex, 它可以 随机地 从范围 [0, w.length - 1] 内（含 0 和 w.length - 1）选出并返回一个下标, 选取下标 i 的 概率 为 w[i] / sum(w)

例如，对于 w = [1, 3], 挑选下标 0 的概率为 1 / (1 + 3) = 0.25, 而选取下标 1 的概率为 3 / (1 + 3) = 0.75

示例 1：
输入：
["Solution","pickIndex"]
[[[1]],[]]
输出：
[null,0]
解释：
Solution solution = new Solution([1]);
solution.pickIndex(); // 返回 0，因为数组中只有一个元素，所以唯一的选择是返回下标 0。

示例 2：
输入：
["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"]
[[[1,3]],[],[],[],[],[]]
输出：
[null,1,1,1,1,0]
解释：
Solution solution = new Solution([1, 3]);
solution.pickIndex(); // 返回 1，返回下标 1，返回该下标概率为 3/4 。
solution.pickIndex(); // 返回 1
solution.pickIndex(); // 返回 1
solution.pickIndex(); // 返回 1
solution.pickIndex(); // 返回 0，返回下标 0，返回该下标概率为 1/4 。

由于这是一个随机问题，允许多个答案，因此下列输出都可以被认为是正确的:
[null,1,1,1,1,0]
[null,1,1,1,1,1]
[null,1,1,1,0,0]
[null,1,1,1,0,1]
[null,1,0,1,0,0]
......
诸若此类

提示：
1 <= w.length <= 10^4
1 <= w[i] <= 10^5
pickIndex 将被调用不超过 10^4 次

注意：本题与主站 528 题相同： https://leetcode-cn.com/problems/random-pick-with-weight/


*/


class Solution1 {
private:
	vector<int> sum;

public:
	Solution1(vector<int> &w) {
		int len = w.size();
		sum.resize(len + 1);
		for (int i = 0; i < len; ++i) sum[i + 1] = sum[i] + w[i];
	}

	int pickIndex() {
		int len = sum.size();
		int lo = 1, hi = len - 1;
		int target = rand() % sum[len - 1] + 1;
		while (lo < hi) {
			int mi = lo + (hi - lo) / 2;
			sum[mi] < target ? lo = mi + 1 : hi = mi;
		}
		return lo - 1;
	}
};

/**
* Your Solution object will be instantiated and called as such:
* Solution* obj = new Solution(w);
* int param_1 = obj->pickIndex();
*/

/*

该方法可以用一个大数组构造出所有的下标元素序列，
然后对输入数组总长度作rand，看结果落在哪个下标元素上

比如 [3, 1, 2, 4]，则可以构造一个大数组[0, 0, 0, 1, 2, 2, 3, 3, 3, 3]
但是这个题目给出的输入用例范围非常大，构造大数组会造成内存超限
最后选择使用前缀和的方法，通过二分查找解决

*/

// https://leetcode.cn/problems/random-pick-with-weight/solutions/966628/gong-shui-san-xie-yi-ti-shuang-jie-qian-8bx50/
// @author https://leetcode.cn/u/ac_oier/



class Solution2 {
private:
	int bid = 0;
	int cid = 0;
	vector<pair<int, int>> buckets;

public:
	Solution2(vector<int> &w) {
		int len = w.size();
		double sum = 0, minNum = INT_MAX;
		for (int n : w) {
			sum += n;
			minNum = min(minNum, (double)n);
		}
		double minFrac = minNum / sum;
		int k = 1;
		while (minFrac * k < 1) k *= 10;
		for (int i = 0; i < len; ++i) {
			int cnt = w[i] / sum * k;
			buckets.push_back({ i, cnt });
		}
	}

	int pickIndex() {
		pair<int, int> p = buckets[bid];
		int id = p.first, cnt = p.second;
		while (cid >= cnt) {
			++bid;
			if (bid == buckets.size()) bid = 0;
			cid = 0;
			p = buckets[bid];
			id = p.first;
			cnt = p.second;
		}
		++cid;
		return id;
	}
};

/**
* Your Solution object will be instantiated and called as such:
* Solution* obj = new Solution(w);
* int param_1 = obj->pickIndex();
*/


// https://leetcode.cn/problems/random-pick-with-weight/solutions/966628/gong-shui-san-xie-yi-ti-shuang-jie-qian-8bx50/
// @author https://leetcode.cn/u/ac_oier/
