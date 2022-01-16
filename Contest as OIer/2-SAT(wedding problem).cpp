/* product of wangxiangqi*/
//2-SAT 
//wedding problem
//poj 3468
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<stack>
#define ll long long int
using namespace std;
/*
有一对新郎新娘准备婚礼，邀请了(n-1)对夫妇参加(n ≤ 30 n \leq 30n≤30)，
其中有m个人有通奸关系(???)，
而且新郎新娘和别人，同性或异性都可能发生通奸关系(贵圈真乱…)。
现在有一张长桌，有两边，一边坐着新娘一边坐着新郎，
新娘不希望她对面有一对夫妇或者有通奸关系的人坐在一起，求一种排座位方案，输出坐新娘这边的人
*/
//Tarjan 缩点算法
/*1.从一个点开始dfs，并加入栈
2.如果下一个点没有到过，跳到第一步
3.如果下一个点到过，并且在栈中，下一个点到这个点，这一段构成一个回路，也就是可以缩点*/
stack<int> st;
void dfs(int x)
{
    st.push(x);      //加入栈
    dis[x]=1;        //x点在栈中
    dfn[x]=low[x]=++te;    //dfn用来表示某个点访问过，并且记录初始的low值
    for(int i=f[x]; i; i=nex[i])
    {
        int v=to[i];
        if(dfn[v]==0)
        {
            dfs(v);
            low[x]=min(low[x],low[v]);   //将一个回路的low改成一样的
        }
        else if(dis[v]==1)low[x]=min(low[x],low[v]);    //下一个点在栈中，那么找到一个回路，但是可能是嵌套回路，所以取最小low
    }
    if(dfn[x]==low[x])   //表示x点的初始值没有被改变，构成一个强连通分量
    {
        while(st.size())
        {
            int g=st.top();
            st.pop();
            dis[g]=0;
            id[g]=x;    //用x命名强连通分量
            if(g==x)break;  //代表g是强连通分量的最后一个数
        }
    }
} 
int main()
{
	int n, m;
	while(~scanf("%d%d",&n,&m)&&(n+m))
	{
		
	}
}
