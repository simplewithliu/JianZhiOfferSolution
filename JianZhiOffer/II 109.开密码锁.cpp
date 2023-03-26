#include "header.h"

/*

剑指 Offer II 109. 开密码锁

你有一个带有四个圆形拨轮的转盘锁。每个拨轮都有10个数字： '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
每个拨轮可以自由旋转：例如把 '9' 变为 '0'，'0' 变为 '9'
每次旋转都只能旋转一个拨轮的一位数字

锁的初始数字为 '0000' ，一个代表四个拨轮的数字的字符串

列表 deadends 包含了一组死亡数字，一旦拨轮的数字和列表里的任何一个元素相同，这个锁将会被永久锁定，无法再被旋转

字符串 target 代表可以解锁的数字，你需要给出解锁需要的最小旋转次数，如果无论如何不能解锁，返回 -1

示例 1:
输入：deadends = ["0201","0101","0102","1212","2002"], target = "0202"
输出：6
解释：
可能的移动序列为 "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202"。
注意 "0000" -> "0001" -> "0002" -> "0102" -> "0202" 这样的序列是不能解锁的，
因为当拨动到 "0102" 时这个锁就会被锁定。

示例 2:
输入: deadends = ["8888"], target = "0009"
输出：1
解释：把最后一位反向旋转一次即可 "0000" -> "0009"。

示例 3:
输入: deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"], target = "8888"
输出：-1
解释：无法旋转到目标数字且不被锁定。

提示：
1 <= deadends.length <= 500
deadends[i].length == 4
target.length == 4
target 不在 deadends 之中
target 和 deadends[i] 仅由若干位数字组成

注意：本题与主站 752 题相同： https://leetcode-cn.com/problems/open-the-lock/

*/

// 双向BFS，参考 II 108. 单词演变
class Solution {
public:
	int openLock(vector<string> &deadends, string target) {
		unordered_set<string> dict(deadends.begin(), deadends.end());
		unordered_set<string> head, tail;
		if (dict.count("0000")) return -1;
		if (target == "0000") return 0;
		head.insert("0000");
		tail.insert(target);
		int ladder = 1;
		while (!head.empty() && !tail.empty()) {
			if (head.size() > tail.size()) swap(head, tail);
			unordered_set<string> tmpset;
			for (string word : head) {
				for (int i = 0; i < word.size(); ++i) {
					char c = word[i];
					word[i] = c == '9' ? '0' : c + 1;
					if (tail.count(word)) return ladder;
					if (!dict.count(word)) {
						tmpset.insert(word);
						dict.insert(word);
					}
					word[i] = c == '0' ? '9' : c - 1;
					if (tail.count(word)) return ladder;
					if (!dict.count(word)) {
						tmpset.insert(word);
						dict.insert(word);
					}
					word[i] = c;
				}
			}
			++ladder;
			swap(head, tmpset);
		}
		return -1;
	}
};

// https://leetcode.com/problems/open-the-lock/solutions/110237/regular-java-bfs-solution-and-2-end-bfs-solution-with-improvement/
// @author https://leetcode.com/yaoyimingg/
