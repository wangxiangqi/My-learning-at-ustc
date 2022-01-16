/* product of wangxiangqi*/
#include<bits/stdc++.h>
using namespace std;
int n;
int ans[10000][10],arr[10];
int ansnum=0;
void dfs(int stp, int now)
{
	if(stp>10)
	{
	if(now==n)
	{
		++ansnum;
		for(int i=0;i<10;i++)
		{
			ans[ansnum][i]=arr[i];
		}
	}
	return ;
}
	for(int i=1;i<=3;i++)
	{
		if((now+i)>n)
		{
			break;
		}
		arr[stp]=i;
		dfs(stp+1,now+1);
		arr[stp]=0;
	}
}
int main()
{
	cin>>n;
	if(n>30||n<10)
	{
		cout<<ansnum<<endl;
		return 0;
	}
	else
	{
		dfs(1,0);
	}
	for(int i=1;i<=ansnum;i++)
	{
		for(int j=0;j<10;j++)
		{
			cout<<ans[i][j]<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
