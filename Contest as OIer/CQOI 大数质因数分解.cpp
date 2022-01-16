/* product of wangxiangqi*/
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#define LL long long
#define rep(i, x, y) for (int i = x; i <= y; i++)

const int prime_list[12] = { 2, 3, 5, 7, 11, 13, (LL) 1e9 + 7 };
const int small_prime[6] = { 2, 3, 5, 7, 11 };
const int luck_prime = 19260817;

template <typename T>
inline void read(T &x) {
    x = 0;
    LL f = 1;
    char c = getchar();
    for (; !isdigit(c); c = getchar()) {
        if (c == '-')
            f = -f;
    }
    for (; isdigit(c); c = getchar()) {
        x = x * 10 + c - 48;
    }
    x *= f;
}

LL ksc(LL a, LL b, LL m) {
    LL d = ((long double)a / m * b + 1e-8);
    LL r = a * b - d * m;
    return r < 0 ? r + m : r;
}

LL ksm(LL a, LL b, LL p) {
    LL sum = 1;
    for (; b >= 1; b >>= 1, a = ksc(a, a, p)) {
        if (b & 1)
            sum = ksc(sum, a, p);
    }
    return sum;
}

LL gcd(LL a, LL b) {
    if (!a) return b;
    if (!b) return a;
#define ctz __builtin_ctzll
    int t = ctz(a | b);
    a >>= ctz(a);
    do {
        b >>= ctz(b);
        if (a > b) {
            LL t = b;
            b = a;
            a = t;
        }
        b -= a;
    } while (b != 0);
    return a << t;
}

bool miller_rabin(LL x) {
    if (x < 2)
        return false;
    if (x == 2 || x == 3 || x == 5 || x == 7)
        return true;
    if (x % 2 == 0 || x % 3 == 0 || x % 5 == 0 || x % 7 == 0)
        return false;
    LL cnt = 0, rem = x - 1;
    while (!(rem & 1)) {
        cnt++;
        rem >>= 1;
    }

    rep(i, 0, 6) {
        if(x == prime_list[i]) return true;
        if(x % prime_list[i] == 0) return false;
        LL rt = ksm(prime_list[i], rem, x);
        LL y = rt;
        rep(i, 1, cnt) {
            rt = ksc(rt, rt, x);
            if (rt == 1 && y != 1 && y != x - 1) {
                return false;
            }
            y = rt;
        }
        if (rt != 1)
            return false;
    }
    return true;
}

int M = (1 << 7) - 1;
LL fin(LL x, LL p, LL c) {
    LL ans = ksc(x, x, p) + c;
    return ans < p ? ans : ans - p;
}
LL abs(LL x) {
    return x < 0? -x : x;
}
LL pollards_rho(LL x) {
    if (x % 2 == 0)
        return 2;
    if (x % 3 == 0)
        return 3;
    if (x % 5 == 0)
        return 5;
    if (x % 7 == 0)
        return 7;
    LL base = 1ll * rand() % (x - 1) + 1;
    LL sp = 0, tp = 0;
    int i = 1, j = 0;
    LL val = 1;
    LL d;
    for(i = 1; ; i <<= 1, sp = tp, val = 1) {
        for(j = 1; j <= i; ++j) {
            tp = f(tp, x, base);
            val = ksc(val, abs(tp - sp) , x);
            if(!(j & M)) {
                d = gcd(val, x);
                if(d > 1) return d;
            }
        }
        d = gcd(val, x);
        if(d > 1) return d;
    }
}

LL factor[5], m = 0;
void work(LL x) {
    if(x <= 1) return;
    if(miller_rabin(x)) {
        factor[++m] = x;
        return;
    }
    LL num = x;
    while(num >= x) {
        num = pollards_rho(x);
    }
    while(x % num == 0) {x /= num;}
    if(x >= 2) work(x); 
    if(num >= 2) work(num);
}

LL exgcd(LL a, LL b, LL &x, LL &y) {
    if(b == 0) {x = 1; y = 0; return a;}
    LL d = exgcd(b, a%b, x, y);
    LL z = x;
    x = y;
    y = z - y * (a / b);
    return d;
}

LL inv(LL a, LL p) {
    LL x, y;
    LL d = exgcd(a, p, x, y);
    return d == 1? (x + p) % p : -1;
}

int main() {
    srand((unsigned)time(0));
    LL e, N, c;
    read(e); read(N); read(c);
    
    work(N);
    std::sort(factor + 1, factor + m + 1);
    
    LL r = (factor[1] - 1) * (factor[2] - 1);
    LL d = inv(e, r);
    
    printf("%lld %lld\n", d, ksm(c, d, N));
    return 0;
}

