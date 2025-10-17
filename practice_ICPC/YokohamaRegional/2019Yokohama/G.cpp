#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < n; ++i)

int main(){
    ll n;
    cin >> n;
    vector<string> s(n);
    rep(i, n){
        cin >> s[i];
    }
    map<string, vector<ll>> G;
    // s[i]とs[j]の接頭辞が同じなら、辺を貼る
    rep(i, n - 1){
        for(ll j = i + 1; i < n; j++){
            bool ok = true;
            rep(k, min(s[i].length(), s[j].length())){
                if(s[i][k] != s[j][k]){
                    ok = false;
                }
            }
        }
    }
}