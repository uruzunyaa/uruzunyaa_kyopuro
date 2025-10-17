#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
#define rep(i, n) for(ll i = 0; i < (ll)n; ++i)
#define loop(i, a, b) for(ll i = a; i <= b; ++i)
constexpr ll INF = 9009009009009009009LL;

int main() {
    ll l, k; cin >> l >> k;
    vll dp(l + k * 2, 0);

    dp[1] = 1;
    dp[k] = 1;
    rep(i, l) {
        dp[i + 2] += dp[i];
        dp[i + 1 + k] += dp[i];
    }

    ll ans = 0;
    loop(i, 0, l) {
        ans += dp[i];
    }

    cout << ans << endl;
}