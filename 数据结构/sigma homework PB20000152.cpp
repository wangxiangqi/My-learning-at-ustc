//sigma homework PB20000152
#include<iostream>
#include<cstdio>
#include<algorithm>
#define maxn 10^5
int maxing=-99999;
using namespace std;
int a[maxn];
int sum(int *a,int k,int j)
{
	int res=0;
	for(int i=k;i<j;i++)
	{
		res+=*(a+i);
	}
	return res;
}
int main()
{
    int n;
    cout<<"input total number"<<endl;
    cin>>n;
    int count=0;
    while(n--)
    {
    	cout<<"input "<<"a["<<count<<"]"<<endl;
    	cin>>a[count];
    	count++;  	
    }
    //method 1 
    //Brutal force
    /*for(int k=0;k<count;k++)
    {
    	for(int j=k+1;j<count;j++)
    	{
    		int m=sum(a,k,j);
    		maxing=max(maxing,m);
    	}
    }
    cout<<"the max sum of child sequence is "<<maxing<<endl;*/
    //method 2
    //polish the arithmatic
    //using the DP method
    int flag=a[0];
    int rec1=0,rec2=0;
    int rec3;
    for(int k=1;k<count;k++)
    {  
        int m=flag;
    	flag+=a[k];
    	if(min(m,flag)>maxing)
    	{
    		maxing=flag;
    		rec3=rec1;
    		rec2=k;
    	}
		if(m>flag)
    	{
    		flag=a[k];
    		rec1=k;
    	}
    }
    cout<<"the max sum of child sequence is "<<maxing<<endl;
    cout<<"the sequential numbers are"<<rec3<<' '<<rec2<<endl;
}
