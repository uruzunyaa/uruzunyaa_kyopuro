#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)

int main() {
    while(1){
        ll n,l,r;
        cin >> n >> l >> r;
        if(n == 0)break;
        vector<ll> a(n);
        rep(i, n){
            cin >> a[i];
        }
        ll ans = 0;
        for(ll i = l; i <= r; i++){
            bool flag = false;
            rep(j, n){
                if(i % a[j] == 0){
                    if((j + 1) % 2 == 1)ans++;
                    flag = true;
                    break;
                }
            }
            if(!flag){
                if(n % 2 == 0)ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}