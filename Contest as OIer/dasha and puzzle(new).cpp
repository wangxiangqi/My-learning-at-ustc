#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<cstdio>
using namespace std;
int degree[400];
vector <int>map[400];
int ans[400][3];
int fx[4]={1,0,-1,0};
int fy[4]={0,1,0,-1};
int dui[10]={2,3,0,1};
int n;
//利用DFS算法求解 
void DFS(int u,int from,int x,int y, int len,int flag)
{
	int dir=0;
	ans[u][0]=x;
	ans[u][1]=y;
	for(int i=0;i<map[u].size();i++)
	{
		int xx=x;
        int yy=y;
        int v=map[u][i];
        if(v==from)continue;
        if(flag!=-1&&dir==dui[flag])dir++;
        xx+=fx[dir]*len;
        yy+=fy[dir]*len;
        DFS(v,u,xx,yy,len/2,dir);
        dir++;
	}
}
int main()
{
	 while(~scanf("%d",&n))
    {
        for(int i=0;i<n-1;i++)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            map[x].push_back(y);
            map[y].push_back(x);
            degree[x]++;
            degree[y]++;
        }
        int flag=0;
        for(int i=1;i<=n;i++)if(degree[i]>4)flag=1;
        if(flag==1)printf("NO\n");
        else
        {
            DFS(1,-1,0,0,1<<30,-1);
            printf("YES\n");
            for(int i=1;i<=n;i++)
            {
                printf("%d %d\n",ans[i][0],ans[i][1]);
            }
        }
    }
}
