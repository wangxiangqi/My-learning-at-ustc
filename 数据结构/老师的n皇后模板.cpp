//n-皇后问题的随机搜索算法，找到解即可
//用一维数组来存放每一列皇后的行号，比如solution[3]=4表示第四列第五行放置了一个皇后
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<time.h>
#include<algorithm>
using namespace std;
//采用堆分配存储的方式实现
int neighbors[100000]; //存放邻居的数组，内容为0,1,2,...,size-1
int solution[100000]; //每列一个皇后，solution[i]=row,表示第j列的皇后在row行
long long int len;            //皇后数量
//函数声明
void initSolution(){
	for(int i=0;i<len;++i)    //随机给初始布局或给定某个初始布局
		solution[i]=i;
	for(int i=0;i<len;++i)  //邻居数组初始化
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
	int times = 20;  //随机交换解的次数，扰动大小,设置times>1即可
	for(int i=0;i<times;++i){
		int k = rand()%len;
		int j = rand()%len;
		long long int row = solution[k];
		solution[k] = solution[j];
		solution[j] = row;
	}
	puts("restart()被调用！");
}
int main(){
	int c1,c2; //两个选择出来准备交换的列
	long seed = 820;  //随机数种子，如果这个数不改变，那么每次算法运行的结果都是一样的，即使用rand()函数
	srand((unsigned) time(NULL));
	//这一句注释掉，等于每次的随机数种子都不一样
	printf("请输入皇后个数：");
	scanf("%d",&len);     //键盘读入棋盘的大小
	while(1)
	{
		cout<<1<<endl;
		initSolution();
		restart();
		int iter=0;//控制迭代次数
		int calccol=evaluate(solution);
		if(calccol==0){
		printf("得到的解为：");
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
			printf("得到的解为：");
	        for(int i=0;i<len;++i)
		    printf("%lld,",solution[i]);
		return 1;
			}
			iter++;
		}
	}
	getchar();
}
