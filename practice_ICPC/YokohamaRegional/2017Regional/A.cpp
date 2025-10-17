#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)

int main(){
    ll n,h,w;
    cin >> n >> h >> w;
    vector<ll> x(n);
    rep(i, n){
        cin >> x[i];
    }
    vector<ll> imos(n * w + 1,0);
    rep(i, n){
        if((i + 1) % 2 == 1){
            imos[i * w + x[i]]++;
            imos[(i + 1) * w + x[i]]--;
        }else{
            imos[i * w - x[i]]++;
            imos[(i + 1) * w - x[i]]--;
        }
    }
    ll sum = 0;
    rep(i, n * w){
        sum += imos[i];
        imos[i] = sum;
    }
    ll ans = 0;
    rep(i, n * w){
        if(imos[i] == 0){
            ans++;
        }
    }
    cout << ans * h << endl;
}