#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"
#include <queue>
#include <stack>
using namespace std;

const int N=3;//3*3棋盘
const int Max_Step=30;//最大搜索深度

enum Direction{None,Up,Down,Left,Right};//方向
struct Chess//棋盘
{
    int cell[N][N];//数码数组
    int Value;//评估值
    Direction BelockDirec;//所屏蔽方向
    struct Chess * Parent;//父节点
};

//打印棋盘
void PrintChess(struct Chess *TheChess)
{
    printf("------------------------------------------------------------------------/n");
    for(int i=0;i<N;i++)
    {
        printf("/t");
        for(int j=0;j<N;j++)
        {
            printf("%d/t",TheChess->cell[i][j]);
        }
        printf("/n");
    }
    printf("/t/t/t/t差距:%d/n",TheChess->Value);
}
//移动棋盘
struct Chess * MoveChess(struct Chess * TheChess,Direction Direct,bool CreateNewChess)
{
    struct Chess * NewChess;

    //获取空闲格位置
    int i,j;
    for(i=0;i<N;i++)
    {
        bool HasGetBlankCell=false;
        for(j=0;j<N;j++)
        {
            if(TheChess->cell[i][j]==0)
            {
                HasGetBlankCell=true;
                break;
            }
        }
        if(HasGetBlankCell)
            break;
    }

    //移动数字
    int t_i=i,t_j=j;
    bool AbleMove=true;
    switch(Direct)
    {
    case Up:
        t_i++;
        if(t_i>=N)
            AbleMove=false;
        break;
    case Down:
        t_i--;
        if(t_i<0)
            AbleMove=false;
        break;
    case Left:
        t_j++;
        if(t_j>=N)
            AbleMove=false;
        break;
    case Right:
        t_j--;
        if(t_j<0)
            AbleMove=false;
        break;
    };
    if(!AbleMove)//不可以移动则返回原节点
    {
        return TheChess;
    }

    if(CreateNewChess)
    {
        NewChess=new Chess();
        for(int x=0;x<N;x++)
        {
            for(int y=0;y<N;y++)
                NewChess->cell[x][y]=TheChess->cell[x][y];
        }
    }
    else
        NewChess=TheChess;
    NewChess->cell[i][j]=NewChess->cell[t_i][t_j];
    NewChess->cell[t_i][t_j]=0;

    return NewChess;
}

//初始化一个初始棋盘
struct Chess * RandomChess(const struct Chess * TheChess)
{
    int M=30;//随机移动棋盘步数
    struct Chess * NewChess;
    NewChess=new Chess();
    memcpy(NewChess,TheChess,sizeof(Chess));
    srand((unsigned)time(NULL));
    for(int i=0;i<M;i++)
    {   
        int Direct=rand()%4;
        //printf("%d/n",Direct);
        NewChess=MoveChess(NewChess,(Direction) Direct,false);
    }
    return NewChess;
}

//估价函数
int Appraisal(struct Chess * TheChess,struct Chess * Target)
{
    int Value=0;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(TheChess->cell[i][j]!=Target->cell[i][j])
                Value++;
        }
    }
    TheChess->Value=Value;
    return Value;
}

//搜索函数
struct Chess * Search(struct Chess* Begin,struct Chess * Target)
{
    Chess * p1,*p2,*p;
    int Step=0;//深度
    p=NULL;
    queue<struct Chess *> Queue1;
    Queue1.push(Begin);
    //搜索
    do{
        p1=(struct Chess *)Queue1.front();
        Queue1.pop();
        for(int i=1;i<=4;i++)//分别从四个方向推导出新子节点
        {
            Direction Direct=(Direction)i;
            if(Direct==p1->BelockDirec)//跳过屏蔽方向
                continue;
       
            p2=MoveChess(p1,Direct,true);//移动数码
            if(p2!=p1)//数码是否可以移动
            {
                Appraisal(p2,Target);//对新节点估价
                if(p2->Value<=p1->Value)//是否为优越节点
                {
                    p2->Parent=p1;
                    switch(Direct)//设置屏蔽方向,防止往回推
                    {
                    case Up:p2->BelockDirec=Down;break;
                    case Down:p2->BelockDirec=Up;break;
                    case Left:p2->BelockDirec=Right;break;
                    case Right:p2->BelockDirec=Left;break;
                    }
                    Queue1.push(p2);//存储节点到待处理队列
                    if(p2->Value==0)//为0则,搜索完成
                    {
                        p=p2;
                        i=5;
                    }
                }
                else
                {
                    delete p2;//为劣质节点则抛弃
                    p2=NULL;
                }
            }
        }
        Step++;
        if(Step>Max_Step)
            return NULL;
    }while(p==NULL || Queue1.size()<=0);

    return p;
}

main()
{
    Chess * Begin,Target,* T;
    //设定目标棋盘 [0 1 2],[3 4 5],[6 7 8]
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            Target.cell[i][j]=i*N+j;
        }
    }
    //获取初始棋盘
    Begin=RandomChess(&Target);
    Appraisal(Begin,&Target);
    Begin->Parent=NULL;
    Begin->BelockDirec=None;
    Target.Value=0;
    printf("目标棋盘:/n");
    PrintChess(&Target);
    printf("初始棋盘:/n");
    PrintChess(Begin);
    //图搜索
    T=Search(Begin,&Target);
    //打印
    if(T)
    {
        /*把路径倒序*/
        Chess *p=T;
        stack<Chess *>Stack1;
        while(p->Parent!=NULL)
        {
            Stack1.push(p);
            p=p->Parent;
        }
        printf("搜索结果:/n");
        while(!Stack1.empty())
        {
            PrintChess(Stack1.top());
            Stack1.pop();
        }
        printf("/n完成!");
    }else
        printf("搜索不到结果.深度为%d/n",Max_Step);

    scanf("%d",T);
}

