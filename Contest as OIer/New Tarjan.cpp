/* product of wangxiangqi*/
//Tarjan �������Ƕ����㷨��ʱ�临�Ӷ��Ͻ����Ż��ķ�ʽ
//��ͼ���ǿ��ͨ�����ľۺϵķ���
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std; 
const int N=10^5+5,M=10^5+5;
int top,Index,tot,cur,n,m;
int sta[N],In[N],DFN[N],LOW[N],color[N],sum[N],head[N],a[M],b[M];
//��������
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
//add �����м����µ�Ԫ��
 
