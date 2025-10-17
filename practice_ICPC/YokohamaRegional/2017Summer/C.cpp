#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)
constexpr ll INF = 9009009009009009009LL;

int main() {
    ll n; cin >> n;
    vector<set<ll>> g(n * n, set<ll>());
    rep(i, 2 * n * n - 2 * n) {
        ll a, b; cin >> a >> b;
        --a, --b;
        g[a].insert(b);
        g[b].insert(a);
    }

    vector<vector<ll>> grid(n, vector<ll>(n + n - 1, -INF));
    rep(r, n) {
        loop(c, r, r + n - 1) {
            grid[r][c] = INF;
        }
    }

    set<ll> used;
    rep(i, n * n) {
        if (g[i].size() == 2) {
            grid[0][0] = i;
            used.insert(i);
            break;
        }
    }

    set<ll> all;
    rep(i, n * n) {
        all.insert(i);
    }

    loop(c, 1, n + n - 2) {
        loop(r, 1, n - 1) {
            if (grid[r][c] == -INF) continue;

            set<ll> a, b;
            a = (grid[r][c - 1] == -INF ? all : g[grid[r][c - 1]]);
            b = (grid[r - 1][c - 1] == -INF ? all : g[grid[r - 1][c - 1]]);

            if (a.size() > b.size()) {
                swap(a, b);
            }

            set<ll> intersect;
            for (ll av : a) {
                if (b.count(av) && !used.count(av)) intersect.insert(av);
            }
            assert(intersect.size() != 0);

            grid[r][c] = *intersect.begin();
            used.insert(*intersect.begin());
        }

        if (grid[0][c] == -INF) continue;
        for (ll unused : g[grid[0][c - 1]]) {
            if (!used.count(unused)) {
                grid[0][c] = unused;
                used.insert(unused);
            }
        }
    }

    rep(r, n) {
        loop(c, r, r + n - 1) {
            cout << grid[r][c] + 1 << " ";
        }
        cout << endl;
    }
}