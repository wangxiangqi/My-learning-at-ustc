#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <iterator>
#include <vector>
#include <ctime>
#define MAXN 30000
using namespace std;
int N;
int Pos[MAXN];
int CollTable[MAXN*2][2];//冲突表，分别记录正负对角线上的冲突数
void OutputSolution()
{
    cout << "{";
    for (int i = 0; i<N - 1; i++)
        cout << Pos[i] << ", ";
    cout << Pos[N-1] << "}" << endl;
}
void InitialPos()
{
    for (int i = 0; i<N; i++)
        Pos[i] = i;
    for (int i = 0; i<N; i++)
    {
        int pos = rand() % N;
        swap(Pos[pos], Pos[N - pos - 1]);
    }
    memset(CollTable,0,sizeof(CollTable));
}
int CalcCollision()
{
    int CollCnt=0;
    for(int i=0;i<N;i++)
    {
        CollTable[Pos[i]+i][0]++;
        CollTable[Pos[i]-i+N-1][1]++;
    }
    for(int i=0;i<2*N-1;i++)
    {
        for(int j=0;j<2;j++)
        {
            if(CollTable[i][j]>1)
                CollCnt+=CollTable[i][j]-1;
        }
    }
    return CollCnt;
}
int NewCollision(int pos1,int pos2,int oc)
{
    int currcollcnt=oc;
    //删去原有冲突
    if(--CollTable[Pos[pos1]+pos1][0]>0)
        currcollcnt--;
    if(--CollTable[Pos[pos1]-pos1+N-1][1]>0)
        currcollcnt--;
    if(--CollTable[Pos[pos2]+pos2][0]>0)
        currcollcnt--;
    if(--CollTable[Pos[pos2]-pos2+N-1][1]>0)
        currcollcnt--;
    //计算现有冲突
    if(++CollTable[Pos[pos1]+pos2][0]>1)
        currcollcnt++;
    if(++CollTable[Pos[pos1]-pos2+N-1][1]>1)
        currcollcnt++;
    if(++CollTable[Pos[pos2]+pos1][0]>1)
        currcollcnt++;
    if(++CollTable[Pos[pos2]-pos1+N-1][1]>1)
        currcollcnt++;
    return currcollcnt;
}
void RecoverCollision(int pos1,int pos2)
{
    //恢复原有冲突
    ++CollTable[Pos[pos1]+pos1][0];
    ++CollTable[Pos[pos1]-pos1+N-1][1];
    ++CollTable[Pos[pos2]+pos2][0];
    ++CollTable[Pos[pos2]-pos2+N-1][1];
    //删去现有冲突
    --CollTable[Pos[pos1]+pos2][0];
    --CollTable[Pos[pos1]-pos2+N-1][1];
    --CollTable[Pos[pos2]+pos1][0];
    --CollTable[Pos[pos2]-pos1+N-1][1];
}
int SwapQueen(int OrigCollCnt)
{
    int pos1 = rand() % N;
    int pos2 = rand() % N;
    while (pos1 == pos2)
        pos2 = rand() % N;
    int CurrCollCnt = NewCollision(pos1,pos2,OrigCollCnt);
    if (CurrCollCnt < OrigCollCnt)
        swap(Pos[pos1], Pos[pos2]);
    else
    {
        CurrCollCnt=OrigCollCnt;
        RecoverCollision(pos1,pos2);
    }
    return CurrCollCnt;
}
int Queen()
{
    int Markov = N*N;
    clock_t start=clock();
    while (1)
    {
        int IterCnt = 0;
        InitialPos();
        int collcnt = CalcCollision();
        if (collcnt == 0)
        {
            OutputSolution();
            return 1;
        }
        while (IterCnt<Markov)
        {
            collcnt = SwapQueen(collcnt);
            if (collcnt == 0)
            {
                clock_t finish=clock();
                OutputSolution();
                double totaltime=(double)(finish - start)/CLOCKS_PER_SEC;
                cout<<"Speed:"<<totaltime<<"s"<<endl;
                return 1;
            }
            IterCnt++;
        }
    }
    return 0;
}
int main()
{
    srand(time(NULL));
    while (cin >> N)
    {
        memset(Pos, -1, sizeof(Pos));
        if (N <= 0)
            cout << "N is not legal!" << endl;
        else if(N >= 30000)
            cout << "For my PC's random range, I limit the N less than 99999" << endl;
        else if (N == 2 || N == 3)
                cout << "Cannot get a solution" << endl;
        else
            Queen();
    }
    return 0;
}
