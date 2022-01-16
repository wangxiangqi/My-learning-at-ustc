#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<set>
#define N 500
typedef struct{
 char str[N];
 int length;
}SString;
//¿éÁ´µÄ±íÊ¾
int compare(SString *str, SString *com)
{
	for(int i=0;i<str->length;i++)
	{
		if(str->str[i]!=com->str[i])
		{return 1;
		}
	}
	if(com->length>str->length)
	{return 1;
	}
	return 0;
}
int TraverseString(SString &S)
{
	int i;
	for(i=0;i<S.length;i++)
	{
		printf("%c",S.str[i]);
	}
	puts("");
}
int StringAssign(SString *S, char string[])
{
	int i=0;
	S->length=strlen(string);
	for(i=0;i<S->length;i++)
	{
		S->str[i]=string[i];
	}
	return 1;
}
int clear(SString *S)
{
	memset(S->str,'\0',sizeof(S->str));
	S->length=0;
	return 1;
}
int Destroy(SString *S)
{
	clear(S);free(S);
	return 1;
}
int Delete(SString *S,int init, int end)
{
	for(int i=init;i<S->length-end+init;i++)
	{
		S->str[i]=S->str[i+end-init];
	}
	S->length=S->length-end+init;
	return 1;
}
int StringConact(SString *first, SString *second)
{
	int k=first->length;
	first->length+=second->length;
	char temp[500];
	for(int i=0;i<second->length;i++)
	{
		first->str[k++]=second->str[i];
	}
	return 1;
}
SString* SubString(SString *S,int init, int end)
{
	SString *res;
	res->length=end-init;
	for(int i=init;i<end;i++)
	{
		res->str[i-init]=S->str[i-1];
	}
	return res;
}
int Strlength(SString &S)
{
	return S.length;
}
int StringInsert(SString *str, int i, SString *V)
{
	printf("%d\n",str->length);
	SString *last=SubString(str,i+1,str->length+1);
	Delete(str,i,str->length);
	StringConact(str,V);
	StringConact(str,last);
	//TraverseString(*str);
	return 1;
}
int Replace(SString *S, SString *T, SString *V)
{
	
	TraverseString(*S);
	return 1;
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
		while(k>0&&temp.str[k]!=temp.str[w-1])
		{
			k=next[k];
		}
		if(k<=0)
		{
			if(temp.str[0]==temp.str[w-1])
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
		if((j==-1)||S.str[i]==temp.str[j])
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
int main()
{
	SString *me;SString *T; SString *V;
	me=(SString*)malloc(sizeof(SString));
	T=(SString*)malloc(sizeof(SString));
	V=(SString*)malloc(sizeof(SString));
	printf("enter your string\n");
	char str[500];
	gets(str);
	printf("%d\n",StringAssign(me,str));
	TraverseString(*me);
	printf("here to show function substr(from 1 to 5)\n");
	SString *oo=SubString(me,1,5);
	TraverseString(*oo);
	printf("enter another string\n");
	char str1[500];
	gets(str1);
	StringAssign(T,str1);
	printf("here to show function Conact\n");
	StringConact(me,T);
	TraverseString(*me);
	printf("here to show function Delete\n");
	Delete(me,me->length-T->length,me->length);
	TraverseString(*me);
	printf("here to show function insert(at 3'd insert cool)\n");
	char mod[500];
	mod[0]='c',mod[1]='o',mod[2]='o',mod[3]='l';
	SString *lo;
	lo=(SString*)malloc(sizeof(SString));
	StringAssign(lo,mod);
	TraverseString(*lo);
	StringInsert(T,3,lo);
	TraverseString(*T);
	Delete(T,3,7);
	TraverseString(*T);
	printf("enter another string\n");
	char str2[500];
	gets(str2);
	StringAssign(V,str2);
	printf("here to show function replace\n");
	TraverseString(*V);
	for(int i=0;i<me->length-V->length;i++)
	{
		printf("%d\n",V->length);
		SString *temp=SubString(me,i,T->length+i);
		TraverseString(*temp);
		if(compare(temp,T)==0)
		{
			Delete(me,i-1,V->length+i-1);
			StringInsert(me,i-1,V);
		}
	}
	TraverseString(*me);
	printf("here to show the KMP search(find V out of me)\n");
	printf("%d\n",KMP(*me,*V));
}
