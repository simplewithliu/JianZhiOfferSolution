#include "header.h"

/*

完全二叉树 是每一层（除最后一层外）都是完全填充（即，节点数达到最大）的，并且所有的节点都尽可能地集中在左侧。

设计一种算法，将一个新节点插入到一个完整的二叉树中，并在插入后保持其完整。

实现 CBTInserter 类:

CBTInserter(TreeNode root) 使用头节点为 root 的给定树初始化该数据结构；
CBTInserter.insert(int v)  向树中插入一个值为 Node.val == val的新节点 TreeNode。使树保持完全二叉树的状态，并返回插入节点 TreeNode 的父节点的值；
CBTInserter.get_root() 将返回树的头节点。


示例 1：
输入
["CBTInserter", "insert", "insert", "get_root"]
[[[1, 2]], [3], [4], []]
输出
[null, 1, 2, [1, 2, 3, 4]]
解释：
CBTInserter cBTInserter = new CBTInserter([1, 2]);
cBTInserter.insert(3);  // 返回 1
cBTInserter.insert(4);  // 返回 2
cBTInserter.get_root(); // 返回 [1, 2, 3, 4]

提示：
树中节点数量范围为 [1, 1000]
0 <= Node.val <= 5000
root 是完全二叉树
0 <= val <= 5000
每个测试用例最多调用 insert 和 get_root 操作 10^4 次

注意：本题与主站 919 题相同： https://leetcode-cn.com/problems/complete-binary-tree-inserter/

*/

// 队列
class CBTInserter1 {
private:
	queue<TreeNode *> candidate;
	TreeNode *root;

public:
	CBTInserter1(TreeNode *root) {
		this->root = root;
		queue<TreeNode *> q;
		q.push(root);
		while (!q.empty()) {
			TreeNode *temp = q.front();
			q.pop();
			if (temp->left) q.push(temp->left);
			if (temp->right) q.push(temp->right);
			if (!(temp->left && temp->right)) candidate.push(temp);
		}
	}

	int insert(int val) {
		TreeNode *child = new TreeNode(val);
		TreeNode *parent = candidate.front();
		if (!parent->left) {
			parent->left = child;
		}
		else {
			parent->right = child;
			candidate.pop();
		}
		candidate.push(child);
		return parent->val;
	}

	TreeNode *get_root() { return this->root; }
};

// 位运算
class CBTInserter2 {
private:
	int cnt = 0;
	TreeNode *root;

public:
	CBTInserter2(TreeNode *root) {
		this->root = root;
		queue<TreeNode *> q;
		q.push(root);
		while (!q.empty()) {
			++cnt;
			TreeNode *temp = q.front();
			q.pop();
			if (temp->left) q.push(temp->left);
			if (temp->right) q.push(temp->right);
		}
	}

	int insert(int val) {
		++cnt;
		TreeNode *child = new TreeNode(val);
		TreeNode *node = this->root;

		// 获取最高位1的位置
		int msb_i = log2(cnt);
		// 将最高位1置为0
		int dir = cnt & ~(1 << msb_i);
		for (int i = msb_i - 1; i > 0; --i) {
			if (dir & (1 << i)) node = node->right;
			else node = node->left;
		}
		if (cnt & 1) node->right = child;
		else node->left = child;
		return node->val;
	}

	TreeNode *get_root() { return this->root; }
};
/*
* https://leetcode.cn/problems/complete-binary-tree-inserter/solutions/1689234/wan-quan-er-cha-shu-cha-ru-qi-by-leetcod-lf8t/
* @author 力扣官方题解
*/

/**
* Your CBTInserter object will be instantiated and called as such:
* CBTInserter* obj = new CBTInserter(root);
* int param_1 = obj->insert(val);
* TreeNode* param_2 = obj->get_root();
*/