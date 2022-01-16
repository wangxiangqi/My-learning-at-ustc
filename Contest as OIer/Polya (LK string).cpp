/* product of wangxiangqi*/
/*
LK's string
一盒有红、蓝、绿三种颜色的珠子，每种颜色珠子的个数都大于24，
现在LK想用这一盒珠子穿出一条项链，项链上的珠子个数为n（0<=n<=24）,
请你帮她计算一下一共可以用这一盒珠子可以穿出多少条不同的项链。
通过旋转、翻转达到同一种状态的被认为是相同的项链。
*/ 
/*
 * poj. 2409
 * date. 2015.8.20
 * 16ms 132kB
 */
#include <iostream>
#include <cstdio>
using namespace std;

long long qpow(int a, int n) {      //由于库函数pow()返回值为double, 所以这里用快幂重写
    long long result = 1, base = a;
    while (n) {
        if (n&1) result *= base;
        base *= base;
        n >>= 1;
    }
    return result;
}
int gcd(int a, int b) {             //计算最大公约数
    return b ? gcd(b, a%b) : a;
}
long long polya(int n, int m) {
    if (n == 0) return 0;
    long long sum = 1;
    for (int i = 0; i < n; ++i)     //旋转
        sum += qpow(m, gcd(i, n));
    if (n&1)                        //翻转
        sum += n * qpow(m, (n+1)/2);                    //奇数情况
    else
        sum += n/2 * (qpow(m, n/2) + qpow(m, n/2 + 1)); //偶数情况
    return sum/(n*2);
}

int main(){
    int n, m;
    while (~scanf("%d %d", &m, &n) && n && m)
        printf("%d\n", polya(n, m));

    return 0;
}
