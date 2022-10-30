#include "header.h"

/*

给你一个字符串数组，请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。
字母异位词是由重新排列源单词的字母得到的一个新单词，所有源单词中的字母通常恰好只用一次。

示例 1:
输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
输出: [["bat"],["nat","tan"],["ate","eat","tea"]]

示例 2:
输入: strs = [""]
输出: [[""]]

示例 3:
输入: strs = ["a"]
输出: [["a"]]

提示：
1 <= strs.length <= 10^4
0 <= strs[i].length <= 100
strs[i] 仅包含小写字母

注意：本题与主站 49 题相同： https://leetcode-cn.com/problems/group-anagrams/


*/

class Solution1 {
public:
	vector<vector<string>> groupAnagrams(vector<string> &strs) {
		unordered_map<string, vector<string>> m;
		for (const auto &str : strs) {
			string key = str;
			sort(key.begin(), key.end());
			m[key].push_back(str);
		}
		vector<vector<string>> res;
		for (auto it = m.begin(); it != m.end(); ++it) {
			res.push_back(it->second);
		}
		return res;
	}
};

class Solution2 {
public:
	vector<vector<string>> groupAnagrams(vector<string> &strs) {

		/*
		* A capture with an initializer acts as if it declares and explicitly captures a variable declared with type auto,
		* whose declarative region is the body of the lambda expression
		* https://en.cppreference.com/w/cpp/language/lambda#Lambda_capture
		*/
		auto arrayHash = [fn = hash<int>()](const array<int, 26> &arr)->size_t {
			return accumulate(arr.begin(), arr.end(), (size_t)0,
				[&](size_t acc, int num) { return (acc << 1) ^ fn(num); });
		};

		unordered_map<array<int, 26>, vector<string>, decltype(arrayHash)> m(0, arrayHash);
		for (const auto &str : strs) {
			array<int, 26> arr{};
			for (int i = 0; i < str.size(); ++i) ++arr[str[i] - 'a'];
			m[arr].push_back(str);
		}
		vector<vector<string>> res;
		for (auto it = m.begin(); it != m.end(); ++it) res.push_back(it->second);
		return res;
	}
};
/*
* https://leetcode.cn/problems/group-anagrams/solutions/520469/zi-mu-yi-wei-ci-fen-zu-by-leetcode-solut-gyoc/comments/1579184
* @author 力扣官方题解
*/


