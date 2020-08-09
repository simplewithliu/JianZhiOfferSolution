#include "header.h"

/*

请实现两个函数，分别用来序列化和反序列化二叉树。

示例: 
你可以将以下二叉树：

    1
   / \
  2   3
     / \
    4   5
序列化为 "[1,2,3,null,null,4,5]"(一种可行方式)
注意：本题与主站 297 题相同：https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree/

*/

//用先序遍历实现
class Codec {
public:

	// Encodes a tree to a single string.
	string serialize(TreeNode *root) 
	{
		ostringstream out;
		serial(root, out);
		return out.str();
	}

	void serial(TreeNode *node, ostringstream &out)
	{
		if (!node)
		{
			out << "#,";
			return;
		}
		out << node->val << ",";
		serial(node->left, out);
		serial(node->right, out);
	}

	// Decodes your encoded data to tree.
	TreeNode * deserialize(string data) 
	{
		istringstream in(data);
		return deserial(in);
	}

	TreeNode * deserial(istringstream &in)
	{
		string val;
		getline(in, val, ',');
		if (val == "#") return nullptr;
		TreeNode *node = new TreeNode(stoi(val));
		node->left = deserial(in);
		node->right = deserial(in);
		return node;
	}
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));