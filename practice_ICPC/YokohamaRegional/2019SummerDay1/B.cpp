#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define vl vector<ll>
#define vvl vector<vl>
#define rep(i, n) for (ll i = 0; i < n; ++i)

vector<ll> enum_divisors(ll n) {
    vector<ll> res;
    res.reserve(100);
    for (ll i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            res.push_back(i);
            if (i * i != n) res.push_back(n / i);
        }
    }
    return res;
}

int main() {
    ll n; cin >> n;
    vl a(n);
    rep(i, n) {
        cin >> a[i];
    }

    map<ll, ll> sum;
    rep(i, n) {
        vl divs = enum_divisors(a[i]);
        for (ll d : divs) {
            sum[d] += a[i];
        }
    }

    ll ans = 0;
    for (auto [d, val] : sum) {
        if (d <= 1) continue;
        ans = max(ans, val);
    }

    cout << ans << endl;
    return 0;
}