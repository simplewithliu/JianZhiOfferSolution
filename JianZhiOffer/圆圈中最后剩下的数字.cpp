#include "header.h"

/*

让小朋友们围成一个大圈。然后,随机指定一个数m,让编号为0的小朋友开始报数。
每次喊到m-1的那个小朋友要出列唱首歌,然后可以在礼品箱中任意的挑选礼物,
并且不再回到圈中,从他的下一个小朋友开始,继续0...m-1报数....这样下去....直到剩下最后一个小朋友,
可以不用表演,请你试着想下,哪个小朋友会是最后一个呢？(注：小朋友的编号是从0到n-1)

*/

class Solution {
public:
	int LastRemaining_Solution(int n, int m)
	{
		if (n == 0 || m == 0) return -1;
		queue<int> q;
		for (int i = 0; i < n; ++i)
			q.push(i);
		int len = q.size();
		while (len != 1)
		{
			int temp = m - 1;
			while (temp != 0)
			{
				int num = q.front();
				q.pop();
				q.push(num);
				--temp;
			}
			q.pop();
			len = q.size();
		}
		return q.front();
	}
};