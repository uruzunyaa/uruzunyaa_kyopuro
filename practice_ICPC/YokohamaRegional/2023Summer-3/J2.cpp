#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PLL = pair<ll, ll>;
using PPLL = pair<ll, PLL>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
const ll MOD = 998244353;
const ll INF = 1LL << 60;

ll dy[] = {0, 1, 0, -1};
ll dx[] = {1, 0, -1, 0};

int main() {
    ll h, w; cin >> h >> w;
    vector<string> g(h);
    rep(i, h) cin >> g[i];
    string t; cin >> t;

    vector<vector<ll>> cost(h, vector<ll>(w, 0));
    rep(i, t.size()) {
        vector<vector<ll>> old(h, vector<ll>(w, 0));
        swap(cost, old);

        rep(y, h) rep(x, w) {
            if (g[y][x] != t[i]) old[y][x]++;
        }

        vector<vector<PLL>> dp(i+2);
        rep(y, h) rep(x, w) {
            ll mn = old[y][x];
            if (g[y][x] == t[i]) mn++;
            rep(dir, 4) {
                ll ny = y + dy[dir];
                ll nx = x + dx[dir];
                if (ny < 0 || h <= ny || nx < 0 || w <= nx) continue;
                mn = min(mn, old[ny][nx]);
            }
            cost[y][x] = mn;
            dp[mn].push_back({y, x});
        }

		
        rep (j,dp.size()) {
            rep(k,dp[j].size()){
				ll y=dp[j][k].first;
				ll x=dp[j][k].second;
				rep(dir, 4) {
					ll ny = y + dy[dir];
					ll nx = x + dx[dir];
					ll nc = cost[y][x] + 1;
					if (ny < 0 || h <= ny || nx < 0 || w <= nx) continue;
					if (cost[ny][nx] <= nc) continue;
					cost[ny][nx] = nc;
					dp[nc].push_back({ny, nx});
				}
			}
        }

        // rep(y, h) {
        //     rep(x, w) {
        //         cout << cost[y][x] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << "-----" << endl;
    }

    ll ans = INF;
    rep(y, h) rep(x, w) {
        ans = min(ans, cost[y][x]);
    }
    cout << ans << endl;

    return 0;
}