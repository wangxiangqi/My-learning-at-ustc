/* product of wangxiangqi*/
//George's sticks
//George has a bunch of sticks, and he cuts them into numerous parts.
//Now you are given the length of the cut sticks, 
//you need to find the smallest length of original sticks.
//The original sticks are of the same length
//Plus the cut length con't be longer than 50
#include<bits/stdc++.h>
using namespace std;
const int N = 70;
int n;
int res;
int maxn, minn = N;
int box[N];	// step2
void dfs(int pre, int sum, int x, int y) {
	if (pre == 0) {	// step4 
		cout << x << '\n';
		exit(0);
	}
	if (sum == x) {	// step3 
		dfs(pre - 1, 0, x, maxn);
		return ;
	}
	for (int i = y; i >= minn; --i) {	// step2 & step3
		if (box[i] > 0 && i + sum <= x) {
			--box[i];
			dfs(pre, sum + i, x, i);
			++box[i];	//	回溯
			if (sum == 0 || sum + i == x) {	// step4
				break;
			}
		}
	}
}

int main() {
    cin >> n;
    while (n--) {
    	int t;
    	cin >> t;
    	if (t > 50) {	// 过滤 
    		continue;
		}
		++box[t];
		res += t;
		maxn = max(maxn, t);	// step1
		minn = min(minn, t);
    }
    int en = res >> 1;	// 由于res一直在改变，所以需要在循环前定义一个变量存储 
    for (int i = maxn; i <= en; ++i) {
    	if (res % i == 0) {
    		dfs(res / i, 0, i, maxn);
		}
	} 
	cout << res << '\n'; 
    return 0;
}

