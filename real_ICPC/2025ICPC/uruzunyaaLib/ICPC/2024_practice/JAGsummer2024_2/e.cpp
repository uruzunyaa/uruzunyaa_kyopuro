#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define ALL(v) v.begin(),v.end()
string S;
ll mod = 998244353;
int main() {
	cin >> S;
	int N = S.size();
	int maxD = N/2 + 1;
	vector now(4, vector(maxD, vector<ll>(N+1))),
		dp(4, vector(maxD, vector<ll>(N+1,-1)));
	vector cnt(maxD, vector<ll>(N+1));
	
	auto digit = [&](int s, int d, int i) {
		if (s == 0) {
			for (int k = 0; k < 10; ++k) {
				if (dp[s][d][i+1]== -1) dp[s][d][i+1] = 0;
				dp[s][d][i+1] += dp[s][d][i];
				dp[s][d][i+1] %= mod;
				now[s][d][i+1] += (now[s][d][i] * 10 % mod + k * cnt[d][i] % mod) % mod;
				now[s][d][i+1] %= mod;
				cnt[d][i+1] += cnt[d][i];
				cnt[d][i+1] %= mod;
			}
		}
		else if (s==1 || s==3) {
			for (int k = 1; k < 10; ++k) {
				if (dp[0][d][i+1]== -1) dp[0][d][i+1] = 0;
				dp[0][d][i+1] += dp[s][d][i];
				dp[0][d][i+1] %= mod;
				now[0][d][i+1] += (now[s][d][i] * 10 % mod + k) % mod;
				now[0][d][i+1] %= mod;
				cnt[d][i+1] = (cnt[d][i+1] + 1) % mod;
				cnt[d][i+1] %= mod;
			}
		}
		else if (s==-1) {
			for (int k = 1; k < 10; ++k) {
				if (dp[0][d][i+1]== -1) dp[0][d][i+1] = 0;
				now[0][d][i+1] += k;
				now[0][d][i+1] %= mod;
				cnt[d][i+1] = (cnt[d][i+1] + 1) % mod;
				cnt[d][i+1] %= mod;
			}
		}
	};
	auto dig = [&](int s, int d, int i, int k) {
		if (s == 0) {
			if (dp[s][d][i+1]== -1) dp[s][d][i+1] = 0;
			dp[s][d][i+1] += dp[s][d][i];
			dp[s][d][i+1] %= mod;
			now[s][d][i+1] += (now[s][d][i] * 10 % mod + k * cnt[d][i] % mod) % mod;
			now[s][d][i+1] %= mod;
			cnt[d][i+1] += cnt[d][i];
			cnt[d][i+1] %= mod;
		}
		else if ((s==1 || s==3) && k > 0) {
			if (dp[0][d][i+1]== -1) dp[0][d][i+1] = 0;
			dp[0][d][i+1] += dp[s][d][i];
			dp[0][d][i+1] %= mod;
			now[0][d][i+1] += (now[s][d][i] * 10 % mod + k) % mod;
			now[0][d][i+1] %= mod;
			cnt[d][i+1] = (cnt[d][i+1] + 1) % mod;
			cnt[d][i+1] %= mod;
		}
		else if (s==-1 && k > 0) {
			if (dp[0][d][i+1]== -1) dp[0][d][i+1] = 0;
			now[0][d][i+1] += k;
			now[0][d][i+1] %= mod;
			cnt[d][i+1] = (cnt[d][i+1] + 1) % mod;
			cnt[d][i+1] %= mod;
		}
	};
	auto open = [&](int s, int d, int i) {
		if ((s==1 || s==3) && d < maxD-1) {
			if (dp[1][d+1][i+1]== -1) dp[1][d+1][i+1] = 0;
			dp[1][d+1][i+1] += (dp[s][d][i] + now[s][d][i]) % mod;
			dp[1][d+1][i+1] %= mod;
			now[1][d+1][i+1] = 0;
		}
		else if (s==-1  && d < maxD-1) {
			if (dp[1][d+1][i+1]== -1) dp[1][d+1][i+1] = 0;
		}
	};
	auto close = [&](int s, int d, int i) {
		if ((s==0 || s==2) && d > 0) {
			if (dp[2][d-1][i+1]== -1) dp[2][d-1][i+1] = 0;
			dp[2][d-1][i+1] += (dp[s][d][i] + now[s][d][i]) % mod;
			dp[2][d-1][i+1] %= mod;
			now[2][d-1][i+1] = 0;
		}
	};
	auto plus = [&](int s, int d, int i) {
		if (s==0 || s==2) {
			if (dp[3][d][i+1]== -1) dp[3][d][i+1] = 0;
			dp[3][d][i+1] += (dp[s][d][i] + now[s][d][i]) % mod;
			dp[3][d][i+1] %= mod;
			now[3][d][i+1] = 0;
		}
	};
	
	{
		if (S[0]=='(') open(-1,0,0);
		else if (S[0]==')') close(-1,0,0);
		else if (S[0]=='+') plus(-1,0,0);
		else if (isdigit(S[0])) dig(-1,0,0,S[0]-'0');
		else {
			open(-1,0,0);
			digit(-1,0,0);
		}
	}
	for (int i = 1; i < N; ++i) {
		for (int s = 0; s < 4; ++s) {
			for (int d = 0; d < maxD; ++d) {
				if (dp[s][d][i] == -1) continue;
				if (S[i]=='(') open(s,d,i);
				else if (S[i]==')') close(s,d,i);
				else if (S[i]=='+') plus(s,d,i);
				else if (isdigit(S[i])) dig(s,d,i,S[i]-'0');
				else {
					open(s,d,i);
					close(s,d,i);
					plus(s,d,i);
					digit(s,d,i);
				}
			}
		}
	}
	// for (int d = 0; d < maxD; ++d) {
	// 	for (int i = 0; i <= N; ++i) {
	// 		cerr << dp[0][d][i] << " \n"[i==N];
	// 	}
	// }
	// cerr << endl;
	// for (int d = 0; d < maxD; ++d) {
	// 	for (int i = 0; i <= N; ++i) {
	// 		cerr << now[0][d][i] << " \n"[i==N];
	// 	}
	// }
	// ll x = 0;
	// for (int i = 10; i <= 99; ++i) x += i;
	// cerr << x << endl;
	ll x = dp[2][0][N] + now[2][0][N];
	ll ans = (x!=-1 ? x : 0);
	x = dp[0][0][N] + now[0][0][N];
	ans += (x!=-1 ? x : 0);
	ans %= mod;
	cout << ans << endl;
}
/*
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0

-1 -1 -29 -307 -1
-1 -1 -29 -307 -1
-1 -1 -29 -307 -1
4905
-308
*/