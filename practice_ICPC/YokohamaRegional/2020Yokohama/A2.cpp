#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < (ll)n; ++i)

int main() {
    ll n;
    cin >> n;
    vector<string> xy(n), yz(n), zx(n);
    rep(i, n){
        cin >> yz[i];
    }
    rep(i, n){
        cin >> zx[i];
    }
    rep(i, n){
        cin >> xy[i];
    }

	

    return 0;
}