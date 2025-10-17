#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define MOD1 999999929LL
#define MOD2 999999937LL
constexpr ll INF = 9009009009009009009LL;

// nのk乗をmodで割ったで余りを計算
ll power_mod(ll n, ll k, ll mod){
    long long result = 1;
    while(k > 0){
        if((k & 1) == 1)result = (result * n) % mod;
        n = n * n % mod;
        k >>= 1;
    }
    return result;
}
ll inv(ll n, ll mod) {
    return power_mod(n, mod - 2, mod);
}

int main(){
    ll n, m; cin >> n >> m;
    vector<vector<PLL>> g(n);
    rep(i, m) {
        ll a, b, x; cin >> a >> b >> x;
        --a, --b;
        g[a].push_back({b, x});
        g[b].push_back({a, -x});
    }

    vector<bool> visited(n, false);
    vector<PLL> dp(n, {INF, INF});
    auto dfs = [&](auto dfs, ll v, ll from, PLL val) -> bool {
        if (visited[v]) {
            return dp[v] == val;
        }
        visited[v] = true;
        dp[v] = val;

        bool ok = true;
        for (auto [to, mul] : g[v]) {
            if (from == to) continue;
            ll nval1 = val.first * (mul < 0 ? inv(-mul, MOD1) : mul) % MOD1;
            ll nval2 = val.second * (mul < 0 ? inv(-mul, MOD2) : mul) % MOD2;
            if (!dfs(dfs, to, v, {nval1, nval2})) {
                ok = false;
                break;
            }
        }

        return ok;
    };
    rep(i, n) {
        if (!visited[i]) {
            if (!dfs(dfs, i, -1, {1, 1})) {
                cout << "No" << endl;
                return 0;
            }
        }
    }

    cout << "Yes" << endl;
    return 0;
}