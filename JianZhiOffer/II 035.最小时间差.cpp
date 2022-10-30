#include "header.h"

/*

给定一个 24 小时制（小时:分钟 "HH:MM"）的时间列表，找出列表中任意两个时间的最小时间差并以分钟数表示。

示例 1：
输入：timePoints = ["23:59","00:00"]
输出：1

示例 2：
输入：timePoints = ["00:00","23:59","00:00"]
输出：0

提示：
2 <= timePoints.length <= 2 * 10^4
timePoints[i] 格式为 "HH:MM"

注意：本题与主站 539 题相同： https://leetcode-cn.com/problems/minimum-time-difference/

*/

class Solution1 {
private:
	int getMinutes(const string &t) {
		return ((t[0] - '0') * 10 + t[1] - '0') * 60 + (t[3] - '0') * 10 + t[4] - '0';
	}

public:
	int findMinDifference(vector<string> &timePoints) {
		sort(timePoints.begin(), timePoints.end());
		int res = INT_MAX;
		int t0 = getMinutes(timePoints[0]);
		int pre = t0;
		for (int i = 1; i < timePoints.size(); ++i) {
			int ti = getMinutes(timePoints[i]);
			res = min(ti - pre, res);
			pre = ti;
		}
		res = min(t0 + 1440 - pre, res);
		return res;
	}
};


class Solution2 {
private:
	int getMinutes(const string &t) {
		return ((t[0] - '0') * 10 + t[1] - '0') * 60 + (t[3] - '0') * 10 + t[4] - '0';
	}

public:
	int findMinDifference(vector<string> &timePoints) {
		int n = timePoints.size();
		if (n > 1440) return 0;
		vector<int> cnts(1440 * 2, 0);
		for (const auto &t : timePoints) {
			int ti = getMinutes(t);
			++cnts[ti], ++cnts[ti + 1440];
		}
		int res = 1440, pre = -1;
		for (int i = 0; i < 1440 * 2 && res != 0; ++i) {
			if (cnts[i] == 0) continue;
			else if (cnts[i] > 1) res = 0;
			else if (pre != -1) res = min(i - pre, res);
			pre = i;
		}
		return res;
	}
};
/*
 * https://leetcode.cn/problems/minimum-time-difference/solutions/1217545/gong-shui-san-xie-jian-dan-mo-ni-ti-by-a-eygg/
 * @author https://leetcode.cn/u/ac_oier/
 */