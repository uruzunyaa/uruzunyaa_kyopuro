#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < (ll)n; ++i)

int main() {
    ll n; cin >> n;
    ll odd = 0, even = 0;
    rep(i, n) {
        ll a; cin >> a;
        if (a % 2 == 0) {
            even++;
        }
        else {
            odd++;
        }
    }

    ll ans = 0;
    while (even > 0 && odd > 2) {
        ans++;
        odd -= 2;
        even++;
    }

    if (odd != 0)
        ans += even;
    cout << ans << endl;
    return 0;
}