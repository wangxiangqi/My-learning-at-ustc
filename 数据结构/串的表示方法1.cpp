#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
typedef struct{
	char *ch;
	int length;
}SString;
int TraverseString(SString &S);
int InitString(SString &str)
{
	str.length=0;
	str.ch=NULL;
	return 1;
}
int compare(SString &str, SString com)
{
	for(int i=0;i<str.length;i++)
	{
		if(str.ch[i]!=com.ch[i])
		{return 1;
		}
	}
	if(com.length>str.length)
	{return 1;
	}
	return 0;
}
int Delete(SString &S,int init, int end)
{
	for(int i=init;i<S.length-end+init;i++)
	{
		S.ch[i]=S.ch[i+end-init];
	}
	S.length=S.length-end+init;
	return 1;
}
int StringConact(SString &first, SString &second)
{
	int k=first.length;
	first.length+=second.length;
	char temp[500];
	first.ch=(char *)realloc(first.ch,sizeof(char)*first.length);
	for(int i=0;i<second.length;i++)
	{
		first.ch[k++]=second.ch[i];
	}
	return 1;
}
SString SubString(SString &S,int init, int end)
{
	SString res;
	res.length=end-init;
	res.ch=(char *)malloc(sizeof(char)*res.length);
	for(int i=init;i<end;i++)
	{
		res.ch[i-init]=S.ch[i-1];
	}
	return res;
}
int StringInsert(SString &str, int i, SString &V)
{
	SString last=SubString(str,i+1,str.length+1);
	Delete(str,i,str.length);
	StringConact(str,V);
	StringConact(str,last);
	return 1;
}
int DestroyString(SString &str)
{
	str.length=0;
	return 1;
}
int ClearString(SString &str)
{
	for(int i=0;i<str.length;i++)
	{
	str.ch[i]=0;}
	return 1; 
}
int Stringlength(SString &S)
{
	return S.length;
}
int TraverseString(SString &S)
{
	for(int i=0;i<S.length;i++)
	{printf("%c",S.ch[i]);
	}
	puts("");return 1;
}
int next[1000];
int KMP(SString &S, SString &temp)
{
	int i=0,j=0;
	next[0]=-1; 
	next[1]=0;
	int k=2,w=2;
	while(w<temp.length)
	{
		k=next[w-1];
		while(k>0&&temp.ch[k]!=temp.ch[w-1])
		{
			k=next[k];
		}
		if(k<=0)
		{
			if(temp.ch[0]==temp.ch[w-1])
			{next[w]=1;
			}
			else{next[w]=0;
			}
		}
		else{
			next[w]=k+1;
		}
		w++;
	}
	while(i<S.length&&j<temp.length)
	{
		if((j==-1)||S.ch[i]==temp.ch[j])
		{
			i++;
			j++;
		}
		else{
			j=next[j];
		}
	}
	if(j>=temp.length){
		return i-temp.length;
	}
	else{return -1;
	}
}
int StrAssign(SString &S, char *str)
{
	int i;
	for(i=0;str[i]!='\0';i++){;}
	S.length=i;
	S.ch=(char *)malloc(sizeof(char)*i);
	for(int j=0;j<S.length;j++)
	{S.ch[j]=str[j];
	}
	return 1;
}
int Replace(SString &S, SString T, SString V)
{
	for(int i=0;i<S.length-T.length;i++)
	{
		SString temp=SubString(S,i,T.length+i);
		if(compare(temp,T)==0)
		{
			Delete(S,i-1,T.length+i-1);
			StringInsert(S,i-1,V);
			i+=V.length;
		}
	}
	return 1;
}
int main()
{
	SString me;SString T; SString V;
	InitString(me);
	InitString(T);
	InitString(V);
	printf("enter your string\n");
	char str[500];
	gets(str);
	printf("%d\n",StrAssign(me,str));
	TraverseString(me);
	printf("here to show function substr(from 1 to 5)\n");
	SString oo=SubString(me,1,5);
	TraverseString(oo);
	printf("enter another string\n");
	char str1[500];
	gets(str1);
	StrAssign(T,str1);
	printf("here to show function insert(at 3'd insert cool)\n");
	char mod[500];
	mod[0]='c',mod[1]='o',mod[2]='o',mod[3]='l';
	SString lo;InitString(lo);
	StrAssign(lo,mod);
	StringInsert(T,3,lo);
	TraverseString(T);
	printf("enter another string\n");
	char str2[500];
	gets(str2);
	StrAssign(V,str2);
	printf("here to show function replace\n");
	SString T1;
	StrAssign(T1,str1);
	Replace(me,T1,V);
	TraverseString(me);
	printf("here to show the KMP search(find V out of me)\n");
	printf("%d\n",KMP(me,V));
}
