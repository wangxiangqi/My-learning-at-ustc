#include<bits/stdc++.h>
using namespace std;
string fir;
string sec;
int count=0;
int comb(string no,int n,int k)
{
	for(int i=0;i<n;i++)
	{
		sec.push_back(no[i]);
		no.erase(no[i]);
		comb(no,n--,k);
	}
}
int main()
{
	int n,k; 
    printf("������n��k��ֵ:\n");
    scanf("%d%d",&n,&k);
    if(k>n) 
        printf("����n��k��ֵ����!\n");
    printf("�����������\n");
    for(int i=0;i<n;i++)
    {
	int m;scanf("%d",&m);
	fir.push_back(m);
	}
	comb(fir,n,k);
	for(int i=0;i<sec.length();i++)
	{
		cout<<sec[i]-'0'<<'  ';
		if((i+1)%k==0)
		{puts("");
		}
	}
}
