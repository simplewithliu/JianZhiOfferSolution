#include "header.h"

/*

在一个数组 nums 中除一个数字只出现一次之外，其他数字都出现了三次。请找出那个只出现一次的数字。

示例 1：
输入：nums = [3,4,3,3]
输出：4

示例 2：
输入：nums = [9,1,7,9,7,9,7]
输出：1
  
限制：
1 <= nums.length <= 10000
1 <= nums[i] < 2^31

*/

class Solution1 {
public:
	int singleNumber(vector<int> &nums) 
	{
		int res = 0;
		for (int i = 0; i < 32; ++i)
		{
			int sum = 0;
			for (int n : nums)
			{
				if ((n >> i) & 1) sum += 1;
			}
			res |= (sum % 3) << i;
		}
		return res;
	}
};

//状态机解法（技巧性）
class Solution2 {
public:
	int singleNumber(vector<int> &nums)
	{
		int a = 0, b = 0;
		for (int n : nums)
		{
			b = b ^ n & ~a;
			a = a ^ n & ~b;
		}
		return b;
	}
};
//https://leetcode-cn.com/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-ii-lcof/solution/mian-shi-ti-56-ii-shu-zu-zhong-shu-zi-chu-xian-d-4/
