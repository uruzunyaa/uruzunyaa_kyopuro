#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)
constexpr ll INF = 9009009009009009009LL;

int main() {
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> G(n);
    rep(i, m) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    // visited[i][0] = i番目の奇数
    // visited[i][1] = i番目の偶数
    vector<vector<ll>> visited(n,vector<ll>(2,-1));
    //vector<ll> visited(n, -1);
    queue<pair<ll, ll>> q;
    visited[0][0] = 0;
    q.push({0, 0});
    ll ans = 0;
    while (!q.empty()) {
        ll now = q.front().first;
        ll bit = q.front().second;
        q.pop();
        for (ll next : G[now]) {
            if(visited[next][bit ^ 1] == -1){
                q.push({next,bit ^ 1});
                visited[next][bit ^ 1] = visited[now][bit] + 1;
            }
        }
    }


    bool flag0 = false;
    bool flag1 = false;
    ll mx0 = -INF, mx1 = -INF;
    rep(i, n){
        if(visited[i][0] == -1) flag0 = true;
        if(visited[i][1] == -1) flag1 = true;
        mx0 = max(mx0, visited[i][0]);
        mx1 = max(mx1, visited[i][1]);
    }
    if (flag0 && flag1) {
        cout << -1 << endl;
        return 0;
    }

    if (flag0) mx0 = INF;
    if (flag1) mx1 = INF;
    cout << min(mx0, mx1) << endl;
    return 0;
}