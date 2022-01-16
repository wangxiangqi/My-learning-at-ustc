#include<iostream>
#include<vector>
#include<string.h>
#include<algorithm>
#include<stdio.h>
using namespace std;
const int N=302;
const int inf=1e6;
int g[N][N], used[N],rela[N];
int n;
int topx[N],topy[N],usex[N],usey[N],slack[N];
bool find(int x){
    usex[x]=1;                //��ǲ��� 
    for(int i=1;i<=n;i++){    
        if(usey[i]==1) continue;    //��һ��ֱ����        
        int tmp=topx[x]+topy[i]-g[x][i];    //��� 
        if(tmp!=0){
            slack[i]=min(tmp,slack[i]);        //ÿһ�����δ���ӵ����Ҷ����ӵ���С��� 
        }
        else {                    //û��� 
            usey[i]=1;                        //��ǲ��� 
            if(rela[i]==-1||find(rela[i])){        // ռ ||�ñ��˻� 
                rela[i]=x;
                return true;
            }
        }
    }    
    return false;
}
long long km(){
    memset(rela,-1,sizeof(rela));
    memset(topx,0,sizeof(topx));
    memset(topy,0,sizeof(topy));
    for(int i=1;i<=n;i++){        //�Ҳ��ʼ�� 
        for(int j=1;j<=n;j++){
            topx[i]=max(topx[i],g[i][j]);
        }
    }
    for(int i=1;i<=n;i++){                
        memset(slack,inf,sizeof(slack));    //��� 
        while(1){
            memset(usex,0,sizeof(usex));
            memset(usey,0,sizeof(usey));
            if(find(i)) break;  //�ҹ��� 
            int tmp=inf;
            for(int j=1;j<=n;j++){
                if(usey[j]==1) continue;
                tmp=min(tmp,slack[j]);    //��С��� 
            }
            if(tmp==inf)    return -1;            
            for(int j=1;j<=n;j++){                    
                if(usex[j]==1) topx[j]-=tmp;    //����ͨ�ҽ� 
            }
            for(int j=1;j<=n;j++){
                if(usey[j]==1) topy[j]+=tmp;     //����ͨ����
                else slack[j]-=tmp;                //δ��ͨ��ཱུ�� 
            }
        }
    }    
    long long ans=0;
    for(int i=1;i<=n;i++){
        if(rela[i]!=-1) ans+=g[rela[i]][i];
    }
    return ans;
}
int main(){
    while(scanf("%d",&n) ==    1){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf("%d",&g[i][j]);
            }
        }
        printf("%d\n",km());
    }
}

