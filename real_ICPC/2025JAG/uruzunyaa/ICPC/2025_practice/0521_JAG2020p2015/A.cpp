#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)

int main() {
    while(1){
        ll n,m;
        cin >> n >> m;
        if(n == 0 || m == 0)break;
        vector<ll> a(n),b(m);
        rep(i, n){
            cin >> a[i];
        }
        rep(i, m){
            cin >> b[i];
        }
        vector<ll> cnt(10,0);
        rep(i, n){
            rep(j, m){
                ll temp = a[i] * b[j];
                string digit = to_string(temp);
                rep(i, digit.size()){
                    cnt[digit[i] - '0']++;
                }
            }
        }
        rep(i, cnt.size()){
            cout << cnt[i];
            if(i != cnt.size() - 1)cout << " ";
        }
        cout << endl;
    }
    return 0;
}