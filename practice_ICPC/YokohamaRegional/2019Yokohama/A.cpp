#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < n; ++i)

int main(){
    ll t;
    cin >> t;
    ll ans = 0;
    vector<ll> v;
    ans++;
    t--;
    v.push_back(t);
    rep(i, v.size()){
        if(v.size() == 1){
            if(v[i] / 3 > 0){
                v.push_back(v[i] / 3);
                v[i] %= 3;
            }
        }else{
            if((v[i] - 2) / 3 > 0){
                v.push_back((v[i] - 2) / 3);
                v[i] -= 2;
                ans += 2;
                v[i] %= 3;
            }
        }
    }
    rep(i, v.size()){
        ans += v[i];
    }
    cout << ans << endl;
}