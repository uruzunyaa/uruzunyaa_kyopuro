#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PLL = pair<ll, ll>;
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)

int main() {
    ll n, m; cin >> n >> m;
    vector<map<ll, ll>> g(n);
    rep(i, m) {
        ll u, v; cin >> u >> v;
        u--, v--;
        g[u][v] = i;
        g[v][u] = i;
    }
    vector<ll> s(n);
    rep(i, n) cin >> s[i], s[i]--;


    vector<ll> ans(m, 1);
    ll nowcost = 1e8;
    ll nows = 0;
    vector<bool> visited(n, false);
    auto dfs = [&](auto dfs, ll v) -> bool {
        // assert(visited[v] == false);
        visited[v] = true;
        if (v == s[nows]) nows++;
        
        while (nows < n && g[v].count(s[nows])) {
            // assert(visited[s[nows]] == false);
            ans[g[v][s[nows]]] = nowcost;
            --nowcost;
            if (!dfs(dfs, s[nows])) return false;
        }
        if (nows == n) return true;
        
        bool ok = true;
        for (auto [to, edgeid] : g[v]) {
            if (!visited[to]) {
                ok = false;
                break;
            }
        }

        return ok;
    };

    if(dfs(dfs, 0)) {
        rep(i, m) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
    else {
        cout << "impossible" << endl;
    }

    return 0;
}