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
��һ����������׼������������(n-1)�Է򸾲μ�(n �� 30 n \leq 30n��30)��
������m������ͨ���ϵ(???)��
������������ͱ��ˣ�ͬ�Ի����Զ����ܷ���ͨ���ϵ(��Ȧ���ҡ�)��
������һ�ų����������ߣ�һ����������һ���������ɣ�
���ﲻϣ����������һ�Է򸾻�����ͨ���ϵ��������һ����һ������λ�����������������ߵ���
*/
//Tarjan �����㷨
/*1.��һ���㿪ʼdfs��������ջ
2.�����һ����û�е�����������һ��
3.�����һ���㵽����������ջ�У���һ���㵽����㣬��һ�ι���һ����·��Ҳ���ǿ�������*/
stack<int> st;
void dfs(int x)
{
    st.push(x);      //����ջ
    dis[x]=1;        //x����ջ��
    dfn[x]=low[x]=++te;    //dfn������ʾĳ������ʹ������Ҽ�¼��ʼ��lowֵ
    for(int i=f[x]; i; i=nex[i])
    {
        int v=to[i];
        if(dfn[v]==0)
        {
            dfs(v);
            low[x]=min(low[x],low[v]);   //��һ����·��low�ĳ�һ����
        }
        else if(dis[v]==1)low[x]=min(low[x],low[v]);    //��һ������ջ�У���ô�ҵ�һ����·�����ǿ�����Ƕ�׻�·������ȡ��Сlow
    }
    if(dfn[x]==low[x])   //��ʾx��ĳ�ʼֵû�б��ı䣬����һ��ǿ��ͨ����
    {
        while(st.size())
        {
            int g=st.top();
            st.pop();
            dis[g]=0;
            id[g]=x;    //��x����ǿ��ͨ����
            if(g==x)break;  //����g��ǿ��ͨ���������һ����
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
