#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < (ll)n; ++i)

int main() {
    ll n, m; cin >> n >> m;
    vector<vector<ll>> g(n);
    rep(i, n - 1) {
        ll x, y; cin >> x >> y;
        --x, --y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    vector<bool> nuts(n, false);
    rep(i, m) {
        ll a; cin >> a;
        --a;
        nuts[a] = true;
    }

    auto dfs = [&](auto dfs, ll v, ll p, ll cnt) -> ll {
        if (nuts[v]) cnt++;
        assert(cnt <= 1);

        ll deg = g[v].size();
        ll sum = 0;
        rep(i, deg) {
            if (g[v][i] == p) continue;
            if (!nuts[g[v][i]]) sum++;
        }

        ll res = 0;
        bool ok = false;
        rep(i, deg) {
            if (g[v][i] == p) continue;
            ll ncnt = cnt;
            if (!nuts[g[v][i]]) {
                if (ncnt > 0 && sum - 1 > 0) {
                    ncnt -= 1;
                }
            }
            else {
                if (ncnt > 0 && sum > 0) {
                    ncnt -= 1;
                }
            }
            if (ncnt > 0 && nuts[g[v][i]]) continue;

            res += dfs(dfs, g[v][i], v, ncnt);
            ok = true;
        }

        if (!ok) { 
            return res + (1 - cnt);
        }
        else {
            return res + 1;
        }
    };
    ll ans = dfs(dfs, 0, -1, 0);

    cout << ans << endl;

    return 0;
}