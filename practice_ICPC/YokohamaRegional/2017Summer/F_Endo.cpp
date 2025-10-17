#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)
constexpr ll INF = 9009009009009009009LL;

int main() {
    ll n,m;
    cin >> n >> m;
    vector<vector<ll>> G(n);
    rep(i, m){
        ll u,v;
        cin >> u >> v;
        u--, v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    // Endo's program
    set<set<ll>> ans;
    set<ll> current;
    current = {0};
    while(current.size() != n){
        set<ll> found;
        for(ll i : current){
            cout << i << " ";
            for(ll j : G[i]){
                found.insert(j);
            }
        }
        cout << endl;
        current = found;
        ans.insert(current);
    }
    cout << ans.size() << endl;
}