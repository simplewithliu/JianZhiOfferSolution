#include "header.h"

/*

给你一个整数数组 nums 和两个整数 k 和 t 。
请你判断是否存在两个不同下标 i 和 j，使得 abs(nums[i] - nums[j]) <= t ，同时又满足 abs(i - j) <= k 。
如果存在则返回 true，不存在返回 false。

示例 1：
输入：nums = [1,2,3,1], k = 3, t = 0
输出：true

示例 2：
输入：nums = [1,0,1,1], k = 1, t = 2
输出：true

示例 3：
输入：nums = [1,5,9,1,5,9], k = 2, t = 3
输出：false

提示：
0 <= nums.length <= 2 * 10^4
-2^31 <= nums[i] <= 2^31 - 1
0 <= k <= 10^4
0 <= t <= 2^31 - 1

注意：本题与主站 220 题相同： https://leetcode-cn.com/problems/contains-duplicate-iii/

*/

// 滑动窗口 + 有序集合
class Solution1 {
public:
	bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t) {
		int len = nums.size();
		set<int> s;
		for (int i = 0; i < nums.size(); ++i) {
			auto it = s.lower_bound(max(nums[i], INT_MIN + t) - t);
			if (it != s.end() && *it <= (min(nums[i], INT_MAX - t) + t)) return true;
			s.insert(nums[i]);
			if (s.size() == k + 1) s.erase(nums[i - k]);
		}
		return false;
	}
};
/**
 * 根据题意，实际上可以理解为：两个不同元素的下标距离不大于k， 元素值的差不大于t；
 * 虽然题目中使用了绝对值来表示，但根本上还是两个不同元素，它们互为i、j；
 * 从j的视角去看后面的i，符合条件时 Vj 也属于 Vi (+/-) t，互换i和j变成从j的视角看前面的i，结果一样；
 * 所以只考虑其中的一个方向即可。
 *
 * https://leetcode.cn/problems/contains-duplicate-iii/solutions/726619/cun-zai-zhong-fu-yuan-su-iii-by-leetcode-bbkt/
 * @author https://leetcode.cn/u/leetcode-solution/
 */


// 桶排序
class Solution2 {
private:
	int getID(long long n, long long m) {
		return n < 0 ? (n + 1) / m - 1 : n / m;
	}

public:
	bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t) {
		unordered_map<int, int> mp;
		int len = nums.size();
		for (int i = 0; i < len; ++i) {
			long long n = nums[i];
			int id = getID(n, t + 1LL);
			if (mp.count(id)) return true;
			if (mp.count(id - 1) && abs(n - mp[id - 1]) <= t) return true;
			if (mp.count(id + 1) && abs(n - mp[id + 1]) <= t) return true;
			mp[id] = n;
			if (mp.size() == k + 1) mp.erase(getID(nums[i - k], t + 1LL));
		}
		return false;
	}
};
/**
 * getID 方法的逻辑可参考
 * https://leetcode.cn/problems/contains-duplicate-iii/solutions/726905/gong-shui-san-xie-yi-ti-shuang-jie-hua-d-dlnv/
 * @author https://leetcode.cn/u/ac_oier/
 */