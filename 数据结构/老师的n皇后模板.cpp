//n-�ʺ��������������㷨���ҵ��⼴��
//��һά���������ÿһ�лʺ���кţ�����solution[3]=4��ʾ�����е����з�����һ���ʺ�
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<time.h>
#include<algorithm>
using namespace std;
//���öѷ���洢�ķ�ʽʵ��
int neighbors[100000]; //����ھӵ����飬����Ϊ0,1,2,...,size-1
int solution[100000]; //ÿ��һ���ʺ�solution[i]=row,��ʾ��j�еĻʺ���row��
long long int len;            //�ʺ�����
//��������
void initSolution(){
	for(int i=0;i<len;++i)    //�������ʼ���ֻ����ĳ����ʼ����
		solution[i]=i;
	for(int i=0;i<len;++i)  //�ھ������ʼ��
		neighbors[i] = i;
}
int evaluate(int solu[]){
	int value=0;
	for(int i=0;i<len;i++)
	{
		for(int j=0;j<len;j++)
		{    if(j!=i)
		{if((solu[i]-solu[j])==i-j||(solu[i]-solu[j])==j-i)
			{
				value++;
			}
		}	
		}
	}
	return value;
}
int SwapQueen(int calccol){
    int pos1 = rand() % len;
    int pos2 = rand() % len;
    while (pos1 == pos2)
        {pos2 = rand() % len;}
    neighbors[pos1]=solution[pos2];
	neighbors[pos2]=solution[pos1];
	for(int i=0;i<len;i++)
	{    
		if(i!=pos1&&i!=pos2)
		{neighbors[i]=solution[i];
		}
	}
	int current=evaluate(neighbors);
	if(current<calccol)
	{swap(solution[pos1],solution[pos2]);
	calccol=current;
	}
	return calccol;
}
void restart(){
	int times = 20;  //���������Ĵ������Ŷ���С,����times>1����
	for(int i=0;i<times;++i){
		int k = rand()%len;
		int j = rand()%len;
		long long int row = solution[k];
		solution[k] = solution[j];
		solution[j] = row;
	}
	puts("restart()�����ã�");
}
int main(){
	int c1,c2; //����ѡ�����׼����������
	long seed = 820;  //��������ӣ������������ı䣬��ôÿ���㷨���еĽ������һ���ģ���ʹ��rand()����
	srand((unsigned) time(NULL));
	//��һ��ע�͵�������ÿ�ε���������Ӷ���һ��
	printf("������ʺ������");
	scanf("%d",&len);     //���̶������̵Ĵ�С
	while(1)
	{
		cout<<1<<endl;
		initSolution();
		restart();
		int iter=0;//���Ƶ�������
		int calccol=evaluate(solution);
		if(calccol==0){
		printf("�õ��Ľ�Ϊ��");
	    for(int i=0;i<len;++i)
		printf("%lld,",solution[i]);
		return 1;
		}
		while(iter<len*len)
		{
			cout<<iter<<endl;
			calccol=SwapQueen(calccol);
			if(calccol==0)
			{
			printf("�õ��Ľ�Ϊ��");
	        for(int i=0;i<len;++i)
		    printf("%lld,",solution[i]);
		return 1;
			}
			iter++;
		}
	}
	getchar();
}
