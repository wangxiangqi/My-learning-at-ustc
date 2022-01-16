/* product of wangxiangqi*/
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		string str;
		cin>>str;
		char a=str[0];
		int ans=0;
		for(int i=0;i<str.size();i++)
		{
			if(str[i]==a)
			{
				continue;//The result stays the same
			}
			else
			{
				if(str[i]=='1')
				{
					ans++;
					a='1';
				}
				else
				{
					a='0';
				}
			}
		}
		if(a=='0')
		{
			ans++;
		}
		if(ans>2)
		{
			cout<<2;
		}
		else
		cout<<ans<<endl;
	}
}
