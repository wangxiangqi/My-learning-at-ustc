/* product of wangxiangqi*/
#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 1001
#define STACKINCREMENT 10
//����stack����ز���
unsigned int_stacksize;//Ԥ�ȷ����ջ�ռ�
int *int_stacktop_ptr;//ջ��ָ��
int *int_stackbase_ptr;//ջ��ָ�� 
//����Ĺ��̽���ʹ��GCCԤ���룬 
//������궨��stack�����ڶ���ģ��
//���Բμ���һ����C++ д��template������stack 
#define initStack(stack) stack## _stackbase_ptr=(stack*)malloc(sizeof(stack)*STACK_INIT_SIZE);\
                         if(stack## _stackbase_ptr) {\
                         stack## _stacktop_ptr=stack## _stackbase_ptr;\
                         stack ## _stacksize=STACK_INIT_SIZE;\
                         }else exit(0)
                        //��ʼ��ջ 
#define stackEmpty(stack) stack ## _stackbase_ptr== stack ## _stacktop_ptr ?1:0
//����Ƿ��ջ 
#define getTop(stack,e) stack ## _stackbase_ptr==stack ## _stacktop_ptr ? 0:(e=*(stack ## _stacktop_ptr-1),1)
//���ջ�����϶˵�Ԫ��
#define clearStack(stack) stack ## _stacktop_ptr=stack ## _stackbase_ptr==stack
//���ջ��Ԫ��
#define destroyStack(stack) free(stack ## _stackbase_ptr)
//�ݻ�ջ
#define stackLength(stack) stack ## _stacktop_ptr - stack ## _stackbase_ptr
//����ջ�ĳ��ȴ�С
#define pop(stack,e)  (stack ## _stackbase_ptr==stack ## _stacktop_ptr) ? 0:(e=*(--stack ## _stacktop_ptr-1),1)
//pop����һ��Ԫ��
#define push(stack,e)  if(stack ## _stacktop_ptr-stack ## _stackbase_ptr>=stack ## _stacksize)\
                       {\
                       	stack ## _stacktop_ptr=(stack *)realloc(stack ## _stackbase_ptr, \
						(stack ## _stacksize+STACKINCREMENT)*sizeof(stack));\
					   if(! stack ## _stackbase_ptr) exit(0);\
					   stack ## _stacktop_ptr = stack ## _stackbase_ptr+stack ## _stacksize;\
					   stack ## _stacksize +=STACKINCREMENT;}\
                       *(stack ## _stacktop_ptr++) = e;
//��ʵ������templateģ��������define�����������##��ʵ�Ѿ�������template�ĺ���
//�����Ѿ�����C���ԣ�����C++������ 
//��ջ��pushһ��Ԫ��
unsigned char_stacksize;//Ԥ�ȷ����ջ�ռ� 
char *char_stacktop_ptr;//ջ��ָ��
char *char_stackbase_ptr;//ջ��ָ�� \
//char ���͵�ջ
typedef struct node{
	int data[10];
	float x,y;
}tnode;
//����node���ͽṹ��
unsigned tnode_stacksize;//Ԥ�ȷ����ջ�ռ� 
tnode *tnode_stacktop_ptr;//ջ��ָ��
tnode *tnode_stackbase_ptr;//ջ��ָ�� 
int main()
{
	//��Stack��ʼ�� 
	initStack(int);
	initStack(char);
	initStack(tnode); 
	//������������ջ 
	int x;
	//scanf("%d",&x);
	push(int,3);
	push(int,4);
	push(int,5); 
	if(pop(int,x))
	{
		printf("ջ���ǿ� %d\n",x);
	}
	else
	{
		printf("ջ�գ����ܳ�ջ\n");
	}
	printf("ջ����%d��Ԫ��\n",stackLength(int));
	if(stackEmpty(int))
	{
		printf("ջ�գ�����ȡջ��\n");
	}
	else
	{
		if(getTop(int,x))
		{
			printf("ջ��Ԫ��Ϊ%d\n",x);
		}
	}
	push(int,3);
	printf("ջ����%d��Ԫ��\n",stackLength(int));
	push(int,4);
	push(int,5);
}
