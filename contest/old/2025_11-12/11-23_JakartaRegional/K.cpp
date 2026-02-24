#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PLL = pair<long long, long long>;
#define rep(i, n) for(ll i = 0; i < (ll)n; ++i)

int main() {
    ll n, m, k, q; cin >> n >> m >> k >> q;
    vector<map<ll, set<ll>>> g(n);
    rep(i, m) {
        ll u, v, company;
        cin >> u >> v >> company;
        --u, --v;
        g[u][company].insert(v);
    }

    unordered_map<ll, map<ll, ll>> canuse;
    unordered_set<ll> nowin;
    nowin.insert(0);
    for (auto [company, vs] : g[0]) {
        for (ll v : vs) canuse[company][v]++;
    }

    while (q--) {
        ll t; cin >> t;
        if (t == 1) {
            ll u, v, company;
            cin >> u >> v >> company;
            --u, --v;

            if (nowin.count(v)) continue;
            if (nowin.count(u)) {
                canuse[company][v]++;
            }
            else {
                g[u][company].insert(v);
            }
        }
        else if (t == 2) {
            ll u, v, company;
            cin >> u >> v >> company;
            --u, --v;

            if (nowin.count(v)) continue;
            if (nowin.count(u)) {
                canuse[company][v]--;
                if (canuse[company][v] == 0) canuse[company].erase(v);
            }
            else {
                g[u][company].erase(v);
            }
        }
        else {
            ll company; cin >> company;
            vector<ll> inserted;
            for (auto [to, _] : canuse[company]) {
                if (nowin.count(to)) continue;
                nowin.insert(to);
                inserted.push_back(to);
            }

            canuse[company] = map<ll, ll>();
            for (ll v : inserted) {
                for (auto [com, tos] : g[v]) {
                    for (ll to : tos) {
                        if (nowin.count(to)) continue;
                        canuse[com][to]++;
                    }
                }
            }

            cout << nowin.size() << "\n";
        }
    }

    return 0;
}