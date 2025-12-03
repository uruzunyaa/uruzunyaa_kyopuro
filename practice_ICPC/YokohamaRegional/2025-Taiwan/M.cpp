#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
constexpr ll INF = 9009009009009009009LL;

int main() {
    ll n, m, k; cin >> n >> m >> k;
    vector<vector<ll>> a(k);
    rep(i, n) {
        ll aa; cin >> aa;
        a[--aa].push_back(i);
    }
    vector<vector<ll>> g(n);
    rep(i, m) {
        ll u, v; cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<ll> dist(n, INF);
    queue<ll> q;
    dist[0] = 0;
    q.push(0);
    while (!q.empty()) {
        ll now = q.front();
        q.pop();

        for (ll to : g[now]) {
            if (dist[to] != INF) continue;
            dist[to] = dist[now] + 1;
            q.push(to);
        }
    }

    rep(i, k) {
        ll mx = -INF;
        for (ll v : a[i]) {
            mx = max(mx, dist[v]);
        }
        cout << mx << " ";
    }
    cout << endl;
}