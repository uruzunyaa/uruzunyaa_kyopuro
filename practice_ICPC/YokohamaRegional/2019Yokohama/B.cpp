#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < (ll)n; ++i)
constexpr ll INF = 9009009009009009009LL;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

int main() {
    ll w, d, n; cin >> w >> d >> n;
    vector<pair<ll, pair<ll, ll>>> p;
    rep(i, n) {
        ll x, y, z;
        cin >> x >> y >> z;
        --x, --y;
        p.push_back({z, {x, y}});
    }
    sort(p.begin(), p.end());

    vector<vector<ll>> ans(w, vector<ll>(d, -INF));
    rep(i, n) {
        vector<vector<ll>> now(w, vector<ll>(d, INF));
        queue<pair<ll, ll>> q;
        q.push(p[i].second);
        now[p[i].second.first][p[i].second.second] = p[i].first;

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            rep(dir, 4) {
                ll nx = x + dx[dir];
                ll ny = y + dy[dir];
                if (nx < 0 || w <= nx || ny < 0 || d <= ny) continue;
                if (now[nx][ny] != INF) continue;
                now[nx][ny] = now[x][y] - 1;
                q.push({nx, ny});
            }
        }

        rep(x, w) {
            rep(y, d) {
                ans[x][y] = max(ans[x][y], now[x][y]);
            }
        }
    }

    rep(i, n) {
        ans[p[i].second.first][p[i].second.second] = p[i].first;
    }

    ll res = 0;
    rep(x, w) {
        rep(y, d) {
            rep(dir, 4) {
                ll nx = x + dx[dir];
                ll ny = y + dy[dir];
                if (nx < 0 || w <= nx || ny < 0 || d <= ny) continue;
                if (abs(ans[x][y] - ans[nx][ny]) > 1) {
                    cout << "No" << endl;
                    return 0;
                }
            }
            res += ans[x][y];
        }
    }

    cout << res << endl;
}
