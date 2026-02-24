#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < (ll)n; ++i)

int main() {
    ll n; cin >> n;
    vector<ll> a(n);
    rep(i, n) {
        cin >> a[i];
    }

    ll allgcd = 0;
    rep(i, n) {
        allgcd = gcd(allgcd, a[i]);
    }

    if (allgcd == 1) {
        cout << 2 << endl;
        cout << 4 << " " << 2 << endl;
        cout << 4 << " " << 2 << endl;
    }
    else {
        cout << 1 << endl;
        cout << allgcd << " " << 1 << endl;
    }

    return 0;
}