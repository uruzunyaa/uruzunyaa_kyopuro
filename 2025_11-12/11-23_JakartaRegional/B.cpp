#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < (ll)n; ++i)

int main() {
    ll n; cin >> n;
    vector<ll> w(n);
    rep(i, n) {
        cin >> w[i];
    }

    vector<ll> sum(n);
    rep(i, n) {
        if (i == 0) {
            sum[i] = min(1LL, w[i]);
        }
        else {
            sum[i] = min(sum[i - 1] + 1, w[i]);
        }
    }

    for (ll i = n - 1; i >= 0; --i) {
        if (i == n - 1) {
            sum[i] = min(sum[i], min(1LL, w[i]));
        }
        else {
            sum[i] = min(sum[i], min(sum[i + 1] + 1, w[i]));
        }
    }

    ll ans = 0;
    rep(i, n) {
        ans = max(ans, sum[i]);
    }
    cout << ans << endl;
    return 0;
}