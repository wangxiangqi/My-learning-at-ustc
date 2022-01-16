#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	int n,k;
	cin>>n>>k;
	double p[10^5];
	for(int i=0;i<n;i++)
	{
		cin>>p[i];
	}
	double result=1;
	double sum=1;
	for(int i=1;i<=n;i++)
	{
		sum*=i*p[i-1];
	}
	double right=sum;
	sum*=k*(2*n+k-1)/2;
	double count=0;
	for(int i=0;i<n;i++)
	{
		count+=pow(p[i],k)*(right/p[i]);
	}
	result=sum+count;
	cout<<count<<endl;
	cout<<sum<<endl;
	cout<<result<<endl;
}
