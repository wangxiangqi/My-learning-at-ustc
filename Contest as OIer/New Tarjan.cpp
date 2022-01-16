/* product of wangxiangqi*/
//Tarjan 本质上是对于算法的时间复杂度上进行优化的方式
//把图变成强连通分量的聚合的方法
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std; 
const int N=10^5+5,M=10^5+5;
int top,Index,tot,cur,n,m;
int sta[N],In[N],DFN[N],LOW[N],color[N],sum[N],head[N],a[M],b[M];
//基本参数
// 
struct EDGE{
int t,next;
}e[M]; 
void add(int a,int b)
{
cur++;
e[cur].t=b;
e[cur].next=head[a];
head[a]=cur;
} 
//add 向其中加入新的元素
 
