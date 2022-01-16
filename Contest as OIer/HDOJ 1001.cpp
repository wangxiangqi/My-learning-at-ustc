/* product of wangxiangqi*/
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<time.h>
#include<cmath>
using namespace std;
float u=1;
int rec[10^6];
float pro(int w[100],int l, int r, int n,int pos,int count)
{
	while(w[count]!=0)
	{
		pos+=w[pos];
		rec[count]=pos;
		count++;
		pos=pos-2*w[pos];
		rec[count]=pos;
		u++;
		pro(w,l,r,n,pos,count);
	}
	float c=0;
	for(int i=pow(2,u)-1;i<pow(2,u+1);i++)
	{
		if(rec[i]%n>=l&&rec[i]%n<=r)
		{
			c++;
		}
	}
	return c/pow(2,u);
}
int main()
{
	int n;
	unsigned long long m;
	int l,r;
	while(1)
	{
	    cin>>n>>m>>l>>r;
		if(n==0&&m==0&&l==0&&r==0)
		{
			exit(0);
		}
		int w[100];
		for(int i=0;i<100;i++)
		{
			w[i]=0;
		}
		int count=0;
		while(m--)
		{	
			cin>>w[count];
			count++;
		}
		cout<<pro(w,l,r,n,1,0);
	}
}
