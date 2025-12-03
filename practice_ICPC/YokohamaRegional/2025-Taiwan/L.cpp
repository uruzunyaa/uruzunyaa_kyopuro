#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
constexpr ll INF = 9009009009009009009LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m, k; cin >> n >> m >> k;
    string s; cin >> s;
    vector<ll> diff;
    diff.push_back(INF);
    rep(i, n - 1) {
        diff.push_back(s[i] == s[i + 1] ? 0 : 1);
    }
    diff.push_back(INF);

    priority_queue<pair<ll,vector<ll>>> res;
    rep(offset, k) {
        vector<vector<ll>> dp(n / k + 2, vector<ll>(2, -INF));
        if (diff[offset] == INF) {
            dp[1][0] = diff[k] == 0 ? -INF : 0;
            dp[1][1] = diff[k] == 1 ? -INF : 1;
        }
        dp[0][0] = diff[offset] == 0 ? 0 : -INF;
        dp[0][1] = diff[offset] == 1 ? 1 : -INF;

        for (ll i = diff[offset] == INF ? 1 : 0; i * k + k < diff.size(); ++i) {
            vector<vector<ll>> old(n / k + 2, vector<ll>(2, -INF));
            swap(dp, old);

            rep(j, n / k + 1) {
                rep(e, 2) {
                    if (old[j][e] == -INF) continue;

                    // このiからk個を反転するか
                    // 反転しない場合
                    // 反転しない場合、次はそのまま
                    ll next = diff[i * k + k] != INF ? diff[i * k + k] : 0;
                    // 次の値は、次が1なら+1、0ならそのまま
                    dp[j][next] = max(dp[j][e], old[j][e] + next);

                    // 反転する場合
                    // 次のインデックスは反転する
                	next = next ^ 1;
                    // 次の値は、もし今(e)が1なら-1、0なら+1。更に、次が1なら-1、0なら+1
                    dp[j + 1][next] = max(dp[j + 1][next], old[j][e] + (e == 1 ? -1 : 1) + (diff[i * k + k] != INF ? diff[i * k + k] == 1 ? -1 : 1 : 0));
                }
            }
        }

        vector<ll> dpres(n / k + 2);
        rep(j, n / k + 2) {
            dpres[j] = max(dp[j][0], dp[j][1]);
        }
        res.push({-dpres.size(),dpres});
    }

	while(res.size()!=1){
		vector<ll> tmp1=res.top().second;
		res.pop();
		vector<ll> tmp2=res.top().second;
		res.pop();

		vector<ll> tmp3(tmp1.size()+tmp2.size(),0);
		rep(i,tmp1.size()){
			rep(j,tmp2.size()){
				tmp3[i+j]=max(tmp3[i+j],tmp1[i]+tmp2[j]);
			}
		}
		res.push({-tmp3.size(),tmp3});
	}
	ll fans=0;
	rep(i,m){
		fans=max(fans,res.top().second[i]);
	}
	cout<<fans<<endl;
}