#include "header.h"

/*

实现RandomizedSet类：
RandomizedSet() 初始化 RandomizedSet 对象
bool insert(int val) 当元素 val 不存在时，向集合中插入该项，并返回 true；否则，返回 false。
bool remove(int val) 当元素 val 存在时，从集合中移除该项，并返回 true；否则，返回 false。
int getRandom() 随机返回现有集合中的一项（测试用例保证调用此方法时集合中至少存在一个元素）。每个元素应该有相同的概率被返回。

你必须实现类的所有函数，并满足每个函数的平均时间复杂度为O(1) 。

示例：
输入
["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"]
[[], [1], [2], [2], [], [1], [2], []]

输出
[null, true, false, true, 2, true, false, 2]

解释
RandomizedSet randomizedSet = new RandomizedSet();
randomizedSet.insert(1); // 向集合中插入 1 。返回 true 表示 1 被成功地插入。
randomizedSet.remove(2); // 返回 false ，表示集合中不存在 2 。
randomizedSet.insert(2); // 向集合中插入 2 。返回 true 。集合现在包含 [1,2] 。
randomizedSet.getRandom(); // getRandom 应随机返回 1 或 2 。
randomizedSet.remove(1); // 从集合中移除 1 ，返回 true 。集合现在包含 [2] 。
randomizedSet.insert(2); // 2 已在集合中，所以返回 false 。
randomizedSet.getRandom(); // 由于 2 是集合中唯一的数字，getRandom 总是返回 2 。
  

提示：

-2^31 <= val <= 2^31 - 1
最多调用 insert、remove 和 getRandom 函数 2 * 10^5 次
在调用getRandom方法时，数据结构中至少存在一个元素。

*/

class RandomizedSet {
public:
	/** Initialize your data structure here. */
	RandomizedSet() {}

	/**
	* Inserts a value to the set. Returns true if the set did not already
	* contain the specified element.
	*/
	bool insert(int val) {
		if (m.count(val)) return false;
		int index = nums.size();
		nums.push_back(val);
		m[val] = index;
		return  true;
	}

	/**
	* Removes a value from the set. Returns true if the set contained the
	* specified element.
	*/
	bool remove(int val) {
		if (!m.count(val)) return false;
		int index = m[val];
		nums[index] = nums.back();
		m[nums.back()] = index;
		nums.pop_back();
		m.erase(val);
		return true;
	}

	/** Get a random element from the set. */
	int getRandom() {
		return nums[rand() % nums.size()];
	}

private:
	vector<int> nums;
	unordered_map<int, int> m;

};
/**
* Your RandomizedSet object will be instantiated and called as such:
* RandomizedSet* obj = new RandomizedSet();
* bool param_1 = obj->insert(val);
* bool param_2 = obj->remove(val);
* int param_3 = obj->getRandom();
*/