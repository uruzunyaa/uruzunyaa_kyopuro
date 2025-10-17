#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)

int main(){
    ll l;
    string s;
    cin >> l >> s;
    vector<pair<ll, bool>> idx;
    rep(i, l){
        if(s[i] == '.'){
            idx.push_back({i, false});
        }
    }
    rep(i, idx.size()){
        bool left = true;
        bool right = true;
        for(ll j = idx[i].first + 1; j < l; j++){
            if(s[j] == '.'){
                break;
            }else if(s[j] == 'B'){
                right = false;
                break;
            }
        }
        for(ll j = (ll)idx[i].first - 1; j >= 0; j--){
            if(s[j] == '.'){
                break;
            }else if(s[j] == 'B'){
                left = false;
                break;
            }
        }
        if(left || right){
            idx[i].second = true;
        }
    }

    ll ans = 0;
    rep(i, idx.size()){
        if(!idx[i].second)continue;
        ll chain = 0;
        for(ll j = idx[i].first + 1; j < l; j++){
            if(s[j] == '.'){
                chain = 0;
                break;
            }else if(s[j] == 'B'){
                chain++;
            }else if(s[j] == 'W'){
                break;
            }
            if(j == l - 1)chain = 0;
        }
        ans = max(ans, chain);
        chain = 0;
        for(ll j = (ll)idx[i].first - 1; j >= 0; j--){
            if(s[j] == '.'){
                chain = 0;
                break;
            }else if(s[j] == 'B'){
                chain++;
            }else if(s[j] == 'W'){
                break;
            }
            if(j == 0)chain = 0;
        }
        ans = max(ans, chain);
    }

    cout << ans << endl;
    return 0;
}