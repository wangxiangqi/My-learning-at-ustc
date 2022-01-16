/* product of wangxiangqi*/
#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 1001
#define STACKINCREMENT 10
//定义stack的相关参数
unsigned int_stacksize;//预先分配的栈空间
int *int_stacktop_ptr;//栈顶指针
int *int_stackbase_ptr;//栈底指针 
//下面的过程仅仅使用GCC预编译， 
//在这里宏定义stack类似于定义模板
//可以参见另一个用C++ 写的template来定义stack 
#define initStack(stack) stack## _stackbase_ptr=(stack*)malloc(sizeof(stack)*STACK_INIT_SIZE);\
                         if(stack## _stackbase_ptr) {\
                         stack## _stacktop_ptr=stack## _stackbase_ptr;\
                         stack ## _stacksize=STACK_INIT_SIZE;\
                         }else exit(0)
                        //初始化栈 
#define stackEmpty(stack) stack ## _stackbase_ptr== stack ## _stacktop_ptr ?1:0
//检查是否空栈 
#define getTop(stack,e) stack ## _stackbase_ptr==stack ## _stacktop_ptr ? 0:(e=*(stack ## _stacktop_ptr-1),1)
//获得栈的最上端的元素
#define clearStack(stack) stack ## _stacktop_ptr=stack ## _stackbase_ptr==stack
//清空栈的元素
#define destroyStack(stack) free(stack ## _stackbase_ptr)
//摧毁栈
#define stackLength(stack) stack ## _stacktop_ptr - stack ## _stackbase_ptr
//度量栈的长度大小
#define pop(stack,e)  (stack ## _stackbase_ptr==stack ## _stacktop_ptr) ? 0:(e=*(--stack ## _stacktop_ptr-1),1)
//pop出第一个元素
#define push(stack,e)  if(stack ## _stacktop_ptr-stack ## _stackbase_ptr>=stack ## _stacksize)\
                       {\
                       	stack ## _stacktop_ptr=(stack *)realloc(stack ## _stackbase_ptr, \
						(stack ## _stacksize+STACKINCREMENT)*sizeof(stack));\
					   if(! stack ## _stackbase_ptr) exit(0);\
					   stack ## _stacktop_ptr = stack ## _stackbase_ptr+stack ## _stacksize;\
					   stack ## _stacksize +=STACKINCREMENT;}\
                       *(stack ## _stacktop_ptr++) = e;
//其实可以用template模板来代替define函数，这里的##其实已经类似于template的含义
//但那已经不是C语言，而是C++的内容 
//向栈中push一个元素
unsigned char_stacksize;//预先分配的栈空间 
char *char_stacktop_ptr;//栈顶指针
char *char_stackbase_ptr;//栈底指针 \
//char 类型的栈
typedef struct node{
	int data[10];
	float x,y;
}tnode;
//定义node类型结构体
unsigned tnode_stacksize;//预先分配的栈空间 
tnode *tnode_stacktop_ptr;//栈顶指针
tnode *tnode_stackbase_ptr;//栈底指针 
int main()
{
	//将Stack初始化 
	initStack(int);
	initStack(char);
	initStack(tnode); 
	//测试整数类型栈 
	int x;
	//scanf("%d",&x);
	push(int,3);
	push(int,4);
	push(int,5); 
	if(pop(int,x))
	{
		printf("栈不是空 %d\n",x);
	}
	else
	{
		printf("栈空，不能出栈\n");
	}
	printf("栈中有%d个元素\n",stackLength(int));
	if(stackEmpty(int))
	{
		printf("栈空，不能取栈顶\n");
	}
	else
	{
		if(getTop(int,x))
		{
			printf("栈顶元素为%d\n",x);
		}
	}
	push(int,3);
	printf("栈中有%d个元素\n",stackLength(int));
	push(int,4);
	push(int,5);
}
