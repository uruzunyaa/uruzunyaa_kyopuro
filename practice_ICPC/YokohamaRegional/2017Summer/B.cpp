#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)
constexpr ll INF = 9009009009009009009LL;

int main(){
    ll s, t, d; cin >> s >> t >> d;
    vector<ll> w(d);
    rep(i, d) cin >> w[i];

    ll now = s;
    ll mndiff = INF;
    rep(i, d) {
        now += w[i % d];
        if (now <= t) {
            cout << i + 1 << endl;
            return 0;
        }
        mndiff = min(mndiff, now - s);
    }
    ll diff = now - s;

    if (now >= s) {
        cout << -1 << endl;
        return 0;
    }

    ll ans = 0;
    now = s;
    while (now + mndiff > t) {
        ans += d;
        now += diff;
    }

    rep(i, d) {
        now += w[i % d];
        if (now <= t) {
            cout << ans + i + 1 << endl;
            return 0;
        }
    }
    assert(false);
}