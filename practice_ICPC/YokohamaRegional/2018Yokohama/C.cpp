#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < n; i++)

int main(){
    ll r, s, p;
    cin >> r >> s >> p;
    vector<ll> v;
    rep(_, p){
        ll i, j;
        cin >> i >> j;
        if(j <= s){
            v.push_back(r - i + 2 + (s - j));
        }else {
            v.push_back(r - i + 2 + (j - s - 1));
        }
    }
    sort(v.begin(), v.end());
    ll m = 0;
    rep(i, v.size()){
        if(v[i] <= m){
            v[i] = ++m;
        }
        else m = v[i];
    }
    cout << *max_element(v.begin(), v.end()) << endl;
    return 0;
}