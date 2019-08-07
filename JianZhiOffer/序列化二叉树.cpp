#include "header.h"

/*

请实现两个函数，分别用来序列化和反序列化二叉树.

*/


struct TreeNode 
{
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
		val(x), left(NULL), right(NULL) {}
};


//用先序遍历实现。
class Solution {
public:
	char * Serialize(TreeNode *root)
	{
		string str;
		travPre(root, str);
		while (!str.empty() && (str.back() == ',' || str.back() == '#'))
			str.pop_back();
		int len = str.size();
		char *s = new char[len + 1];
		for (int i = 0; i < len; ++i)
			s[i] = str[i];
		s[len] = '\0';
		return s;
	}
	void travPre(TreeNode *root, string &str)
	{
		if (!root)
		{
			str = str + '#' + ',';
			return;
		}
		str = str + to_string(root->val) + ',';
		travPre(root->left, str);
		travPre(root->right, str);
	}
	TreeNode * Deserialize(char *&str)
	{
		if (!str || *str == '\0') return nullptr;
		if (*str == ',') ++str;
		if (*str == '#')
		{
			++str;
			return nullptr;
		}
		string strToint;
		while ((*str <= '9'&&*str >= '0') || *str == '-')
		{
			strToint += *str;
			++str;
		}
		TreeNode *node = new TreeNode(stoi(strToint));
		node->left = Deserialize(str);
		node->right = Deserialize(str);
		return node;
	}
};