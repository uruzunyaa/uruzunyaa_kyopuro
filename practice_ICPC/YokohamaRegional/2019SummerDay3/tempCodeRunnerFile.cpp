#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < (ll)n; ++i)

int main() {
    ll n, m; cin >> n >> m;
	map<ll, ll> imos;

    rep(i, n) {
        ll l, r; cin >> l >> r;
        imos[l]++;
		imos[r]+=0;
        imos[r + 1]--;
    }
    ll sum = 0;
    ll ma = 0;
    for(auto& p : imos){

        sum += p.second;
        p.second = sum;
        ma = max(ma, p.second);

        //cout << p.first << ":" << p.second << " ";
    }
    //cout << endl;
    if(ma % 2 == 1){
        ll ans = 0;
        for(auto& p : imos){
            if(p.second == ma){
                ans = p.first;
            }
        }
        cout << m * (ma - 1) + ans << endl;
    }else{
        ll ans = 0;
        for(auto& p : imos){
            if(p.second == ma){
                ans = p.first;
                break;
            }
        }
        cout << m * (ma - 1) + (m - ans - 1) << endl;
    }
}