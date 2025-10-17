#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < n; i++)

int main(){
    ll n;
    cin >> n;
    vector<ll> v(n);
    unordered_set<ll> s;
    rep(i, n){
        cin >> v[i];
        s.insert(v[i]);
    }
    sort(v.begin(), v.end());
    ll ans = 1;
    for(ll i = 0; i < n - 1; i++){
        for(ll j = i + 1; j < n; j++){
            ll diff = v[j] - v[i];
            ll cnt = 1;
            while(s.count(v[i] + diff * cnt)){
                cnt++;
            }
            ans = max(cnt, ans);
        }
    }
    cout << ans << endl;
    return 0;
}