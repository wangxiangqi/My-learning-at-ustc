#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <math.h>
#include <algorithm>
 
using namespace std;
const long long N = 500005;
const double PI = acos(-1.0);
 
struct Virt{
    double r,i;
    Virt(double r=0.0,double i=0.0){
        this->r=r;
        this->i=i;
    }
    Virt operator+(const Virt &x){
        return Virt(r+x.r,i+x.i);
    }
    Virt operator-(const Virt &x){
        return Virt(r-x.r,i-x.i);
    }
    Virt operator*(const Virt &x){
        return Virt(r*x.r-i*x.i,i*x.r+r*x.i);
    }
};
//�׵��㷨--��λ��
void Rader(Virt F[],long long len){
    long long j=len>>1;
    for(long long i=1;i<len-1;i++){
        if(i<j)swap(F[i],F[j]);
        long long k = len >> 1;
        while(j>=k){
            j-=k;
            k>>=1;
        }
        if(j<k)j+=k;
    }
}
//FFTʵ��
void FFT(Virt F[],long long len,long long on){
    Rader(F, len);
    for(long long h=2;h<=len;h<<=1) //���κ���㳤��Ϊh��DFT
    {
        Virt wn(cos(-on*2*PI/h),sin(-on*2*PI/h));  //��λ����e^(2*PI/m)��ŷ����ʽչ��
        for(long long j=0; j<len; j+=h)
        {
            Virt w(1,0);            //��ת����
            for(long long k=j;k<j+h/2;k++)
            {
                Virt u=F[k];
                Virt t=w*F[k+h/2];
                F[k]=u+t;     //�����ϲ�����
                F[k+h/2]=u-t;
                w=w*wn;      //������ת����
            }
        }
    }
    if(on==-1)
    for(long long i=0;i<len;i++)
    F[i].r/=len;
}
//����
void Conv(Virt a[],long long len){
    FFT(a,len,1);
//    FFT(b,len,1);
    for(long long i=0;i<len;i++)
        a[i]=a[i]*a[i];
    FFT(a,len,-1);
}
long long a[N],num[N],sum[N],ans[N];
Virt va[N];
int main(){
    long long t;
    scanf("%I64d",&t);
    while(t--){
        memset(num,0,sizeof(num));
        long long n;
        scanf("%I64d",&n);
        for(long long i=0;i<n;i++){
            scanf("%I64d",&a[i]);
            num[a[i]]++;
        }
        sort(a,a+n);
        long long len1=a[n-1]+1;
        long long len=1;
        while(len<len1*2)len<<=1;
        for(long long i=0;i<len;i++){
            va[i].r=num[i];
            va[i].i=0;
        }
        Conv(va,len);
        for(long long i=0;i<len;i++){
            sum[i]=(long long)(va[i].r+0.5);
//            cout<<sum[i]<<endl;
        }
        len=a[n-1]*2;
        for(long long i=0;i<n;i++)
        sum[a[i]+a[i]]--;
        for(long long i=0;i<=len;i++)
        sum[i]>>=1;
        ans[0]=0;
        for(long long i=1;i<=len;i++){
            ans[i]=ans[i-1]+sum[i];
        }
        long long cnt=0;
        for(long long i=0;i<n;i++){
            cnt+=ans[len]-ans[a[i]];
            cnt-=(long long)(n-i-1)*i;//��ȥһ��һС
            cnt-=n-1;//��ȥѡ���������
            cnt-=(long long)(n-i-1)*(n-i-2)/2;//��ȥ�������
        }
        long long tmp=(long long)n*(n-1)*(n-2)/6;
        printf("%.7f\n",(double)cnt/(double)tmp);
    }
    return 0;
}
/*����fftʱʵ��������Ҫ�������룻*/