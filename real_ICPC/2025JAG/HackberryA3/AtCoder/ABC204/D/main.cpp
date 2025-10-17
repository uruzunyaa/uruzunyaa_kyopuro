// #DP
// オーブンが２つあり、料理をいくつかするときの最小時間を求める問題
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using P = pair<int, int>;
using PLL = pair<ll, ll>;
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define loop(i, a, b) for (int i = (a); i <= (b); ++i)

int main() {
	int N;
	cin >> N;
	vi T(N);
	rep(i, N) cin >> T[i];

	const int MAX = 1e3 * N + 1;
	// dp[料理iまで作ったとき][オーブン1と2で使った時間の最大値] = オーブン1と2で使った時間
	vector<vector<P>> dp(N, vector<P>(MAX, P(0, 0)));
	dp[0][T[0]] = P(T[0], 0);

	loop(i, 1, N - 1) {
		rep(j, MAX){
			int t1 = dp[i - 1][j].first;
			int t2 = dp[i - 1][j].second;
			if(t1 + t2 == 0)
				continue;

			dp[i][max(t1 + T[i], t2)] = P(t1 + T[i], t2);
			dp[i][max(t1, t2 + T[i])] = P(t1, t2 + T[i]);
		}
	}

	rep(i, MAX)
	{
		if(dp[N - 1][i].first + dp[N - 1][i].second == 0)
			continue;
		cout << i << endl;
		break;
	}

	return 0;
}
