// #BFS
// 磁石の横のマスに行くと止まってしまうグリッド上で、最大の移動可能なマス数を求める問題
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)

vll dx = {1, 0, -1, 0};
vll dy = {0, 1, 0, -1};

struct phash{
    inline size_t operator()(const pair<int,int> & p) const{
        const auto h1 = hash<int>()(p.first);
        const auto h2 = hash<int>()(p.second);
        return h1 + h2 * 12345;
    }
};

int main() {
    ll h, w;
    cin >> h >> w;
    vector<string> s(h);
    rep(i, h) cin >> s[i];

    unordered_set<PLL, phash> safe;
    unordered_set<PLL, phash> dead;
    rep(i, h) rep(j, w) {
		if (s[i][j] == '#') continue;

        bool ok = true;
        rep(k, 4) {
            ll ni = i + dx[k];
            ll nj = j + dy[k];
            if ((ni < 0 || h <= ni) || (nj < 0 || w <= nj)) continue;
            if (s[ni][nj] == '#') ok = false;
        }
        if (ok) safe.insert({i, j});
        else {
            safe.insert({i, j});
            dead.insert({i, j});
        }
    }

    ll ans = 0;
    while (safe.size()) {
		unordered_set<PLL, phash> visited;
        PLL st = *safe.begin();
        queue<PLL> q;
        q.push(st);
        safe.erase(st);
		visited.insert(st);

        ll cnt = 1;
        while (q.size()) {
            PLL p = q.front();
            q.pop();

            if (dead.count(p)) continue;

            rep(k, 4) {
                ll ni = p.first + dx[k];
                ll nj = p.second + dy[k];
                if ((ni < 0 || h <= ni) || (nj < 0 || w <= nj) || s[ni][nj] == '#') continue;
                if (!visited.count({ni, nj})) {
                    q.push({ni, nj});
                    visited.insert({ni, nj});
					safe.erase({ni, nj});
                    cnt++;
                }
            }
        }

        ans = max(ans, cnt);
    }

    cout << ans << endl;

    return 0;
}
