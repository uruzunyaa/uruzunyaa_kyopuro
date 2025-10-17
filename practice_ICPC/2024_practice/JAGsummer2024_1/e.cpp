#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for(ll i=0;i<(ll)n;i++)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define ALL(v) v.begin(),v.end()

int main() {
	int B;
	int N;
	cin >> B >> N;
	vector<ll> A(N);
	for (int i = 0; i < N; ++i) cin >> A[i];
	vector<ll> S(N+1), S2(N+1);
	for (int i = 0; i < N; ++i) {
		S[i+1] = S[i] + A[i];
		S2[i+1] = S2[i] + A[i]*A[i];
	}

	vector dp(B+1, vector<double>(N+1,1e10));
	dp[0][0] = 0;
	for (int i = 1; i <= N; ++i) {
		for (int k = 0; k < i; ++k) {
			double v = (S2[i] - S2[k]) - (S[i] - S[k]) * (S[i] - S[k]) / (double)(i-k);
			for (int j = 1; j <= B; ++j) {
				dp[j][i] = min(dp[j][i], dp[j-1][k] + v);
			}
		}
	}
	// for (int i = 0; i <= N; ++i) {
	// 	for (int j = 0; j <= B; ++j) {
	// 		cerr << dp[j][i] << " \n"[j==B];
	// 	}
	// }
	double ans = 1e10;
	for (int i = 1; i <= B; ++i) ans = min(ans, dp[i][N]);
	cout << fixed << setprecision(20) << ans << endl;
}