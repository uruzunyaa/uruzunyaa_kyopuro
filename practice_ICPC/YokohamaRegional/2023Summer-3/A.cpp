#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)
const ll MOD = 998244353;

int main(){
    ll n, m;
    cin >> n >> m;
    vector<ll> a(n);
    ll now = 0;
    ll nowtime = 0;
    rep(i, n){
        cin >> a[i];
        if(now + a[i] <= m){
            cout << nowtime << '\n';
            now += a[i];
        }else{
            now = a[i];
            nowtime++;
            cout << nowtime << '\n';
        }
    }
}