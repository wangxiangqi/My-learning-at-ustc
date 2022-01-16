/* product of wangxiangqi*/
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<cstdio>
#include<queue>
#include<algorithm>
#define maxn 10001
using namespace std;
int num[maxn];
int dp[maxn];
struct point{
	int x;
	int y;
	int z;
	//z as the money
}p[maxn];
//these two functions to locate the point
int cmp1(point a,point b)
{
	if(a.x<b.x)
	{
		return 1;
	}
	else if(a.x==b.x)
	{
		if(a.y<b.y)
		{
			return 1;
		}
		return 0;
	}
	return 0;
}
int cmp2(point a,point b){
    if (a.y<b.y)return 1;
    else if (a.y==b.y){
        if (a.x<b.x)return 1;
        return 0;
    }
    return 0;
}
struct tree{
	int l,r;
	int maxing;
	int mid=(l+r)/2;
}tre[maxn];
void pushup(int id)
{
	tre[id].maxing=max(tre[id*2].maxing,tre[id*2+1].maxing);
}
void build(int id,int l,int r)
{
	tre[id].l=l;
	tre[id].r=r;
	if (l==r){
        tre[id].maxing=0;
        return ;
    }
    int mid=tre[id].mid;
    build(id*2,l,mid);
    build(id*2+1,mid+1,r);
    pushup(id);
}
int update(int id, int pos, int val)
{
	if (tre[id].l==tre[id].r){
        tre[id].maxing=max(val,tre[id].maxing);
        return 1;
    }
    int mid=tre[id].mid;
    if (pos<=mid){
        update(id*2,pos,val);
    }
    else {
        update(id*2+1,pos,val);
    }
    pushup(id);
}
int query(int id,int r, int l)
{
	if (tre[id].l>=l&&tre[id].r<=r){
        return tre[id].maxing;
     }
     int mid=tre[id].mid;
     if (r<=mid){
        return query(id*2,l,r);
    }
    else if (l>mid){
        return query(id*2+1,l,r);
    }
    else {
        return max(query(id*2,l,mid),query(id*2+1,mid+1,r));
    }
}
int main()
{
	int T;
	int N;
	int i,j;
	cin>>T;
	while(T--)
	{
		cin>>N;
		queue<int>qq;
		for(i=1;i<N;i++)
		{
			cin>>p[i].x>>p[i].y>>p[i].z;
		}
		sort(p+1,p+N+1,cmp2);
		//why sort?
		num[p[1].y]=1;
		for (i=2;i<=N;i++){
            if (p[i].y!=p[i-1].y){
                num[p[i].y]=num[p[i-1].y]+1;
            }
        }
        build(1,1,num[p[N].y]);
        sort (p+1,p+N+1,cmp1);
        int maxing=0;
        int temp=0;
        p[0].x=0;
        p[0].y=0;
        p[0].z=0;
        for (i=1;i<=N;i++){
            if (p[i].x!=p[i-1].x)
            {
                while (!qq.empty()){
                    int fuck=qq.front();
                    qq.pop();
                    update(1,num[p[fuck].y],dp[fuck]);
                }
                if (num[p[i].y]!=1){
                    dp[i]=p[i].z+query(1,1,num[p[i].y]-1);
                }
                else {
                    dp[i]=p[i].z;
                }
                qq.push(i);
            }
            else {
                if (num[p[i].y]!=1){
                    dp[i]=p[i].z+query(1,1,num[p[i].y]-1);
                }
                else {
                    dp[i]=p[i].z;
                }
                qq.push(i);
            }
            if (dp[i]>maxing)
                maxing=dp[i];
        }
        printf("%lld\n",maxing);
    
	}
}

