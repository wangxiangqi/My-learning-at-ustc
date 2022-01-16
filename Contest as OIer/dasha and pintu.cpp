//Dasha and pintu
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int dir=0;
int x=0;
int y=0;
int plotTree(int bian[][2],int n,int total)
{
int count=0,mount=0;
for(int i=0;i<total-1;i++)
	{
			if(bian[i][0]==n)
			{
				dir=!dir;
				//cout<<dir;
				if(dir==0)
			    {
				cout<<++x<<' '<<y-mount<<endl;
				count=1;
			    }
			     if(dir==1)
			     {
				cout<<x-count<<' '<<++y<<endl;
				mount=1;
			    }
			    for(int j=0;j<total-1;j++)
			    {
			    	if(bian[i][1]==bian[j][0])
			    	{
			    		n=bian[i][1];
			            //cout<<n<<endl;
			            plotTree(bian,n,total);
			    	}
			    }
			}	
		}
}
//这个做法是不行的，会有交叉线段的可能，换个思路
 
int main()
{
	int total;
	cin>>total;
	int bian[total-1][2];
	for(int i=0;i<total-1;i++)
	{
		cin>>bian[i][0];
		cin>>bian[i][1];
	}
	for(int i=0;i<total-1;i++)
	{
		int count=0;
		for(int j=0;j<total-1;j++)
		{
			if(bian[i][0]==bian[j][0])
			{
				count++;
			}
		}
		if(count>2)
		{
			cout<<"NO\n";
			exit(0);
		}
	}
	cout<<"YES\n";
	plotTree(bian,1,total);
}
