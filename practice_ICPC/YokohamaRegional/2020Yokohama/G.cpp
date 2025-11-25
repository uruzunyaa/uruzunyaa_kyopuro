#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < (ll)n; ++i)
constexpr ll INF = 9009009009009009009LL;

struct UnionFind {
    vector<int> par, siz;
    UnionFind(int n) : par(n, -1) , siz(n, 1) {}
    int root(int x){
        if (par[x] == -1) return x;
        else return par[x] = root(par[x]);
    }
    bool issame(int x, int y){
        return root(x) == root(y);
    }
    bool unite(int x, int y){
        x = root(x), y = root(y);
        if (x == y) return false;
        if(siz[x] < siz[y]) swap(x, y);
        par[y] = x;
        siz[x] += siz[y];
        return true;
    }
    
    int size(int x){
        return siz[root(x)];
    }
};

int main() {
    ll n, m; cin >> n >> m;
    vector<ll> l(n);
    rep(i, n) cin >> l[i];

    vector<vector<ll>> smallg(n), bigg(n);
    rep(i, m) {
        ll x, y; cin >> x >> y;
        --x, --y;
        
        if (l[x] <= l[y]) {
            smallg[y].push_back(x);
            bigg[x].push_back(y);
        }
        if (l[x] >= l[y]) {
            smallg[x].push_back(y);
            bigg[y].push_back(x);
        }
    }

    vector<pair<ll, ll>> vs;
    rep(i, n) {
        vs.push_back({l[i], i});
    }
    sort(vs.begin(), vs.end());

    map<ll, pair<ll, ll>> mnsum;
    mnsum[0] = {0, 0};
    UnionFind uf(n);
    rep(i, n) {
        ll nunites = mnsum.rbegin()->second.first;
        ll ncnt = mnsum.rbegin()->second.second;
        
        ll now = vs[i].first;
        while (i < n && vs[i].first == now) {
            ncnt++;
            for (ll to : smallg[vs[i].second]) {
                if (uf.unite(vs[i].second, to)) {
                    nunites++;
                }
            }

            i++;
        }
        i--;

        mnsum[now] = {nunites, ncnt};
    }

    sort(vs.rbegin(), vs.rend());
    map<ll, pair<ll, ll>> mxsum;
    mxsum[vs[0].first] = {0, 0};
    uf = UnionFind(n);
    rep(i, n) {
        ll nunites = mxsum.begin()->second.first;
        ll ncnt = mxsum.begin()->second.second;
        
        ll now = vs[i].first;
        while (i < n && vs[i].first == now) {
            ncnt++;
            for (ll to : bigg[vs[i].second]) {
                if (uf.unite(vs[i].second, to)) {
                    nunites++;
                }
            }

            i++;
        }
        ll next = 0;
        if (i != n) next = vs[i].first; 
        i--;

        mxsum[next] = {nunites, ncnt};
    }

    // for (auto [t, val] : mnsum) {
    //     cout << t << " : " << val.first << " " << val.second << endl;
    // }
    // cout << "-------------" << endl;
    // for (auto [t, val] : mxsum) {
    //     cout << t << " : " << val.first << " " << val.second << endl;
    // }

    for (auto [threshold, val] : mnsum) {
        pair<ll, ll> mxval = mxsum[threshold];
        ll components = val.second - val.first;
        components += mxval.second - mxval.first;
        ll mnv = min(val.second, mxval.second);

        if (mnv == 0) continue;

        if (components - mnv <= 1) {
            cout << threshold << endl;
            return 0;
        }
    }

    cout << -1 << endl;

    return 0;
}