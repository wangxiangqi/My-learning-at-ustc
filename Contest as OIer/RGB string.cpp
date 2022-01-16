/* product of wangxiangqi*/
#include<iostream>
#include<cstdio>
#include<cmath>
//RGB problem
//greed theory
using namespace std;
int main()
{
	char str[10^6];
	char *begin,*end;
	begin=end=str;
	int n;
	cin>>n;
	//cout<<n;
	for(int i=0;i<n;i++)
	{
		cin>>str[i];
	}
	cout<<"the string you have entered is"<<str<<endl;
	while(*begin=='R'&&*begin!='\0')
	{
		begin++;
	}
	end=begin;
	while(*end!='\0')
	{
		if(*end=='R')
		{
			 char ch = *begin;
            *begin = *end;
            *end = ch;
            begin++;
		}
		end++;
	}
	cout<<str<<endl;
	while(begin < end)//这里讲GB分开，Ｂ放在右边
        {
                if(*begin == 'G')
                        begin++;
                if(*end == 'B')
                        end--;
                if(*begin == 'B' && *end =='G' && begin<end)
                {
                        char ch = *begin;
                        *begin = *end;
                        *end = ch;
                        begin++;
                        end--;
                }
        }
        //the code above used to partion the G and B 
        cout<<str<<endl;
        return 0;
}
