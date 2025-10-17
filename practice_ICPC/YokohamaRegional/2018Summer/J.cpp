#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PLL = pair<ll, ll>;
#define vl vector<ll>
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i ,m, n) for (ll i = m; i <= n; ++i)
constexpr ll INF = 9009009009009009009LL;

vector<ll> primes(const ll n) {
    vector<bool> is_prime(n + 1, true);
    vector<ll> res;
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i <= n; ++i) {
        if (!is_prime[i]) continue;
        if (i != 2) res.push_back(i);
        for (ll j = i * i; j <= n; j += i) is_prime[j] = false;
    }
    return res;
}

int main() {
    ll n, m, s, t; cin >> n >> m >> s >> t;
    --s, --t;
    vector<vector<ll>> g(n, vector<ll>());
    rep(i, m) {
        ll a, b; cin >> a >> b;
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<vector<ll>> dist(n, vector<ll>(2, INF));
    queue<PLL> q;
    q.push({s, 0});
    dist[s][0] = 0;
    while (!q.empty()) {
        auto [v, c] = q.front();
        q.pop();

        for (const int& nv : g[v]) {
            if (dist[nv][c ^ 1] != INF) continue;
            dist[nv][c ^ 1] = dist[v][c] + 1;
            q.push({nv, c ^ 1});
        }
    }

    if (dist[t][0] == 2) {
        cout << 2 << endl;
        return 0;
    }
    if (dist[t][1] == INF) {
        cout << -1 << endl;
        return 0;
    }

    vector<ll> prime = primes(1e6);
    cout << *lower_bound(prime.begin(), prime.end(), dist[t][1]) << endl;
    return 0;
}