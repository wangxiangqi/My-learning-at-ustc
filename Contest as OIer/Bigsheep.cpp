/* product of wangxiangqi*/
//CCPC 2019 Bidsheep
/*BigSheep总是喜欢溜圈，但是他有几个原则：

只能向左转，且不能在同一个地方多次左转。
每次只走不同的圈。
每次走圈走遍整个区域，同一个点只去一次，起点不一定需要等于终点。
有一天，BigSheep半夜睡不着觉，跑去操场溜圈。我们可以认为操场是一个n×m的网格图，神奇的BigSheep可以把任意一个格子当作自己的起点开始绕圈，对于BigSheep那些奇怪的原则，我们可以抽象成以下几点：

BigSheep在起点时可以任意选择自己的朝向。
每次只能直走，或者左转后直走，且不能越过边界。
每次走圈的路径不能一样，即同一个路径不能走多次（对于两条路径，存在一个格子(x0,y0)在第一条路径中是第i个访问的，在第二条路径中是第j个访问的，且i != j，我们即可认为这两条路径是不同的）。每次溜圈都需要遍历每一个格子，且每一个格子只能被访问一次，溜圈的起点和终点不需要保证相邻。

BigSheep想知道自己最多可以溜多少圈。*/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
using namespace std;
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int m,n;
		cin>>m>>n;
		if(m>=n)
		swap(m,n);
		if (m == 1 && n == 1) cout << 1;
		else if (m == 1 && n > 1) cout << 2;
		else if (m > 1 && n > 1) cout << 2 * (m + n - 2);
		cout << endl;
	}
}
