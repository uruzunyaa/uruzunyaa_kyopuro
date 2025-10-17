#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll c, n, m;
    cin >> c >> n >> m;
    vector<pair<ll,ll>> s_p(n);
    rep(i, n){
        cin >> s_p[i].first >> s_p[i].second;
    }

    vector<ll> dp(10000 + 1LL, 0);

    rep(i, n){
        for(ll j = 10000LL; j >= 0; j--){
            if(j - s_p[i].first >= 0){
                dp[j] = max(dp[j], dp[j - s_p[i].first] + s_p[i].second);
            }
        }
        // dp[s_p[i].first] = max(dp[s_p[i].first], s_p[i].second);
    }

    ll ma = 0;
    rep(i, 10001){
        ma = max(ma, dp[i]);
        dp[i] = ma;
    }

    rep(i, m){
        ll temp = c / (i + 1);
        cout << dp[temp] * (i + 1) << '\n';
    }
    return 0;
}