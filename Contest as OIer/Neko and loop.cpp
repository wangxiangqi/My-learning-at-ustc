/* product of wangxiangqi*/
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<string>
#include<math.h>
#include<iostream>
using namespace std;
#define mod 1000000007
int Gcd(int x, int y)
{
	if(y==0)
		return x;
	return Gcd(y, x%y);
}
int a[1000], p[1000], sum[1000];
int tre[1000];
void Add(int l, int r, int x)
{
	int m;
	if(l==r)
	{
		tre[x] = sum[r];
		return;
	}
	m = (l+r)/2;
	Add(l, m, x*2);
	Add(m+1, r, x*2+1);
	tre[x] = min(tre[x*2], tre[x*2+1]);
}
LL Query(int l, int r, int x, int a, int b)
{
	int m;
	LL ans = 1e18;
	if(l>=a && r<=b)
		return tre[x];
	m = (l+r)/2;
	if(a<=m)
		ans = min(ans, Query(l, m, x*2, a, b));
	if(b>=m+1)
		ans = min(ans, Query(m+1, r, x*2+1, a, b));
	return ans;
}
int main(void)
{
	LL s, all, ans, temp, M;
	int T, n, m, k, i, j, len, cnt, now, cas = 1;
	scanf("%d", &T);
	while(T--)
	{
		ans = 0;
		scanf("%d%d%d%d", &n, &s, &m, &k);
		for(i=1;i<=n;i++)
			scanf("%d", &a[i]);
		cnt = Gcd(n, k), len = n/cnt;
		for(i=1;i<=cnt;i++)
		{
			now = i, M = m;
			for(j=1;j<=len;j++)
			{
				p[j] = p[j+len] = a[now];
				now = now+k;
				if(now>=n+1)
					now -= n;
			}
			for(j=1;j<=len*2;j++)
				sum[j] = sum[j-1]+p[j];
			Add(1, len*2, 1);
			all = temp = 0;
			if(sum[len]>0)
				all = sum[len]*(M/len);
			M %= len;
			for(j=len+1;j<=len*2;j++)
				temp = max(temp, sum[j]-Query(1, len*2, 1, j-M, j));
			ans = max(ans, all+temp);
			if(m>=len)
			{
				M = m-len;
				if(sum[len]>0)
					all = sum[len]*(M/len);
				M = len;
				for(j=len+1;j<=len*2;j++)
					temp = max(temp, sum[j]-Query(1, len*2, 1, j-M, j));
				ans = max(ans, all+temp);
			}
		}
		printf("Case #%d: %lld\n", cas++, max(0ll, s-ans));
	}
	return 0;
}

