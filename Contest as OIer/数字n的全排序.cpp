/* product of wangxiangqi*/
#include<bits/stdc++.h>
using namespace std;
bool vis[11];
int n,a[11];
void dfs(int stp)
{
	if(stp==n+1)
	{
		for(int i=1;i<=n;i++)
		{
			cout<<a[i]<<' ';
		}
		cout<<'\n';
		return ;
	}
	for(int i=1;i<=n;i++)
	{
		if(!vis[i])
		{
			vis[i]=1;
			a[stp]=i;
			dfs(stp+1);
			vis[i]=0;
		}
	}
}
int main()
{
	cin>>n;
	dfs(1);
	return 0;
}
