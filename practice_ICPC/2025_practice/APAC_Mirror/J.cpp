#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)

int main(){
    ll n, d;
    cin >> n >> d;
    vector<ll> a(n), b(n);

    // a_idx = 値a_idx[i] が aのどのインデックスか
    // b_to_a_idx = 値b_to_a_idx[i] が aのどのインデックスか
    unordered_map<ll, ll> a_idx, a_idx_to_b_idx;
    vector<ll> b_idx_to_a_idx(n);

    rep(i, n){
        cin >> a[i];
        a_idx[a[i]] = i;
    }
    rep(i, n){
        cin >> b[i];
        b_idx_to_a_idx[i] = a_idx[b[i]];
        a_idx_to_b_idx[a_idx[b[i]]] = i;
    }

    ll skips = 0;
    rep(i, n){
        ll prev_pos = i == 0 ? -1 : b_idx_to_a_idx[i - 1];
        if(prev_pos < b_idx_to_a_idx[i]) skips += abs(prev_pos - b_idx_to_a_idx[i]) - 1;
        else skips += n - prev_pos - 1 + b_idx_to_a_idx[i];
    }

    cout << skips << endl;

    d--;
    while(d--){
        ll mode, x, y;
        cin >> mode >> x >> y;
        x--, y--;

        ll b1, b2;
        if(mode == 1){
            // axとayをswap
            b1 = a_idx_to_b_idx[x];
            b2 = a_idx_to_b_idx[y];
        }else {
            // bxとbyをswap
            b1 = x;
            b2 = y;
        }

        set<ll> tochanges;
        tochanges.insert(b1);
        if (b1 != n - 1) tochanges.insert(b1 + 1);
        tochanges.insert(b2);
        if (b2 != n - 1) tochanges.insert(b2 + 1);

        for (ll c : tochanges) {
            ll prev_pos = c == 0 ? -1 : b_idx_to_a_idx[c - 1];
            if(prev_pos < b_idx_to_a_idx[c]) skips -= abs(prev_pos - b_idx_to_a_idx[c]) - 1;
            else skips -= n - prev_pos - 1 + b_idx_to_a_idx[c];
        }

        swap(b_idx_to_a_idx[b1], b_idx_to_a_idx[b2]);
        if(mode == 1){
            // axとayをswap
            swap(a_idx_to_b_idx[x], a_idx_to_b_idx[y]);
        }else {
            // bxとbyをswap
            swap(a_idx_to_b_idx[b_idx_to_a_idx[x]], a_idx_to_b_idx[b_idx_to_a_idx[y]]);    
        }

        for (ll c : tochanges) {
            ll prev_pos = c == 0 ? -1 : b_idx_to_a_idx[c - 1];
            if(prev_pos < b_idx_to_a_idx[c]) skips += abs(prev_pos - b_idx_to_a_idx[c]) - 1;
            else skips += n - prev_pos - 1 + b_idx_to_a_idx[c];
        }

        cout << skips << '\n';
    }
}