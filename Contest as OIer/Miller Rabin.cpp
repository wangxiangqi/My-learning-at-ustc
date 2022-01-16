/* product of wangxiangqi*/
#include<iostream>
#include<cstdio>
#include<cmath>
#include<time.h>
#include<cstdlib>
using namespace std;
//Miller-Rabin arithmatic
//The little rule of Fermat
int main()
{
	int x[1000];
	int m,q;
	cout<<"input m and q (make sure m is odd)"<<endl;
	cin>>m>>q;
	int n=(int)pow(2,q)*m+1;
	srand((unsigned)time(NULL));
	int a=(int)abs(rand()%(n-2)+2);
	x[0]=(int)pow(a,m)%n;
	cout<<a<<' '<<n<<' '<<x[0]<<endl;
	for(int i=0;i<q;i++)
	{
		x[i]=(x[i-1]*x[i-1])%n;
	}
	
}
