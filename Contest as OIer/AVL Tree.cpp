/* product of wangxiangqi*/
#include<stdio.h>
#include<stdlib.h>
//AVL tree
typedef struct BiTNode{
	int data;
	int bf;
	struct BiTNode *lchild, rchild;
}BiTNode,*BiTree;
int InsertAVL(BiTree *T, int e, int *taller)
{
	if(!*T)
	{
		*T=(BiTree)malloc(sizeof(BiTNode));
		(*T)->data=e;
		(*T)->lchild=(*T)->rchild=NULL;
		(*T)->bf=0;
		*taller=1;
	}
	else
	{
		
	}
}
