/* product of wangxiangqi*/
/*
LK's string
һ���к졢������������ɫ�����ӣ�ÿ����ɫ���ӵĸ���������24��
����LK������һ�����Ӵ���һ�������������ϵ����Ӹ���Ϊn��0<=n<=24��,
�����������һ��һ����������һ�����ӿ��Դ�����������ͬ��������
ͨ����ת����ת�ﵽͬһ��״̬�ı���Ϊ����ͬ��������
*/ 
/*
 * poj. 2409
 * date. 2015.8.20
 * 16ms 132kB
 */
#include <iostream>
#include <cstdio>
using namespace std;

long long qpow(int a, int n) {      //���ڿ⺯��pow()����ֵΪdouble, ���������ÿ�����д
    long long result = 1, base = a;
    while (n) {
        if (n&1) result *= base;
        base *= base;
        n >>= 1;
    }
    return result;
}
int gcd(int a, int b) {             //�������Լ��
    return b ? gcd(b, a%b) : a;
}
long long polya(int n, int m) {
    if (n == 0) return 0;
    long long sum = 1;
    for (int i = 0; i < n; ++i)     //��ת
        sum += qpow(m, gcd(i, n));
    if (n&1)                        //��ת
        sum += n * qpow(m, (n+1)/2);                    //�������
    else
        sum += n/2 * (qpow(m, n/2) + qpow(m, n/2 + 1)); //ż�����
    return sum/(n*2);
}

int main(){
    int n, m;
    while (~scanf("%d %d", &m, &n) && n && m)
        printf("%d\n", polya(n, m));

    return 0;
}
