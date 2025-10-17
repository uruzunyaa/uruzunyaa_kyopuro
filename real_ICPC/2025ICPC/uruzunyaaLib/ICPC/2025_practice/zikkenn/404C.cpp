#include <bits/stdc++.h>
#include "atcoder/dsu"
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)

int main() {
    ll n, m;
    cin >> n >> m;
    vector<ll> cnt(n,0);
    atcoder::dsu d(n);
    rep(i, m){
        ll a,b;
        cin >> a >> b;
        cnt[a - 1]++;
        cnt[b - 1]++;
        d.merge(a - 1, b - 1);
    }
    if(d.groups().size() != 1){
        cout << "No" << endl;
        return 0;
    }
    rep(i, n){
        if(cnt[i] != 2){
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
    return 0;
}