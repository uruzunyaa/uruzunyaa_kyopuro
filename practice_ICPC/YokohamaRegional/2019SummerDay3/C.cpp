#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < (ll)n; ++i)

int main() {
    ll n, m; cin >> n >> m;
    vector<pair<ll, ll>> yokan(n);
    rep(i, n) {
        ll l, r; cin >> l >> r;
        yokan[i] = {l, r};
    }

    map<ll, vector<ll>> mp;
    vector<pair<ll, ll>> yokanLR;
    rep(i, n) {
        yokanLR.push_back({yokan[i].first, i});
        yokanLR.push_back({yokan[i].second, i});
    }
    sort(yokanLR.begin(), yokanLR.end());
    priority_queue<ll, vector<ll> greater<ll>> pq;
    vector<ll> groups(n, -1);
    rep(i, n) {
        pq.insert(i);
    }
    rep(i, yokanLR.size()){
        if(groups[yokanLR[i].second] == -1){
            ll group = pq.top();
            groups[yokanLR[i].second] = group;
            pq.pop();
        }else{
            pq.insert(groups[yokanLR[i].second]);
        }
    }
    set<ll> cnt;
    rep(i, groups.size()){
        set.insert(groups[i]);
    }
    ll groupcnt = cnt.size();
    if(groupcnt % 2 == 1){
        // Rが短いほうが良いのでLをとる
    }else{
        
    }
}