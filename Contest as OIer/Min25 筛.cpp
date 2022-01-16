/* product of wangxiangqi*/
//�����������壺
//����sigma(n)Ϊn������������������f(n,k)=sum_{i=1}^n (sigma(i^k))
#include<stdio.h>
#include<math.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N=200005;
int T,S,pr[N],pc;
ll n,num[N],m,K;
ull g[N];
bool fl[N];
// ����һ������X�����Ϊ�ڼ������Եõ���Ч��g������
inline int ID(ll x){return x<=S?x:m-n/x+1;}

ull f(ll n,int i)
{
    if(n<1||pr[i]>n)
	return 0;
    ull ret=g[ID(n)]-(i-1)*(K+1);
    while((ll)pr[i]*pr[i]<=n)
	{
        int p=pr[i];
        ull e=K+1,t=n/p;
        while(t>=p)
		ret+=f(t,i+1)*e+e+K,
		t/=p,
		e+=K;
        // ret= sum{sigma(p^es)([n>1]+f(n/p^es,p)+g[n]-g[num[i-1]]}
        // ��Ϊ���ں���g(n,m)��n<=m^2,g(n,m)Ϊ0
        // �Ҹ���sigma���������ʣ���������p����sigma(p^es)=es*k+1
        // ���� ret+=(es*k+1)*f(n/p^es,p)+((es+1)k+1)(1<=es&& n/p^es>p)����ǰ���sigma(p^e)*f(n/p^e,p)������һ���sigma(p^e)
        // ����������������e<1Ҳ�Ͳ��ؽ�������
        i++;
    }
    return ret;
}
//g[i]��С��i������������sigma�������
//����ǰ����Ƶ���ֻ�е�i����ͨ��[n/m]�õ�ʱ���������
ull solve(ll n){
    int i,p,x;ull y;
    S=sqrt(n);
    while((ll)S*S<=n)S++;
    while((ll)S*S>n)S--;
    while(m)num[m--]=0;
    for(i=1;i<=S;i++)num[++m]=i;
    for(i=S;i>=1;i--)if(n/i>S)num[++m]=n/i;
    for(i=1;i<=m;i++)g[i]=num[i]-1;
    //�˴�g[i]ΪС�ڵ��ڵ�i���������ͨ��[n/m]�õ������������ӵ�����
    //���ȼ�ȥ��1����Ϊ1һ����Ϊ���������޷�����������ɸȥ
    x=1;y=0;
    for(p=2;p<=S;p++)if(g[p]!=g[p-1]){
        while(num[x]<(ll)p*p)x++;
        //��g'(i,j)Ϊ����ɸ��ɸ��ǰj��������1��j֮��ʣ����������
        //����g'(i,j)=g'(0,j)-sum_{k=0,k<i}(g'(k,[j/p[k+1]])-g'(k,p[k]))
        //����p[0]=1,p[i](i>0)Ϊ��i������
        //��g(j)��Ϊg'(i,j)ʹ����p[i]<j&&p[i+1]>j
        //����g'(k,p[k])��Ϊk+1
        //�������ϵĵ���ʽ�������õ�num[x]>=p^2Ϊֹ���ʽ��������µ�x
        //����ÿ�ζ�Ҫ��ȥ��δȥ����ǰ������g�Գ䵱g'��˴Ӵ���С����
        for(i=m;i>=x;i--)g[i]-=g[ID(num[i]/p)]-y;
        y++;
    }
    for(i=1;i<=m;i++)g[i]*=K+1;
    return f(n,1)+1;
}

int main(){
    int i,j;
    //����ɸ
    for(i=2;i<N;i++)if(!fl[i]){
        pr[++pc]=i;
        for(j=i+i;j<N;j+=i)fl[j]=1;
    }
    for(scanf("%d",&T);T--;){
        scanf("%lld%lld",&n,&K);
        printf("%llu\n",solve(n));
    }
    return 0;
}

