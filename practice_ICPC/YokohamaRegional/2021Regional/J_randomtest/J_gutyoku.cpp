#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)
constexpr ll INF = 9009009009009009009LL;

int main() {
    ll n; cin >> n;
    vector<PLL> pos(n);
    rep(i, n) {
        cin >> pos[i].first >> pos[i].second;
    }

    sort(pos.begin(), pos.end());

    ll ans = 0;
    rep(l, n) {
        loop(r, l + 1, n - 1) {
            bool ok = true;
            rep(i, l) {
                if (pos[i].second < min(pos[l].second, pos[r].second)) {
                    ok = false;
                    break;
                }
                if (pos[i].second > max(pos[l].second, pos[r].second)) {
                    ok = false;
                    break;
                }
            }
            loop(i, r + 1, n - 1) {
                 if (pos[i].second < min(pos[l].second, pos[r].second)) {
                    ok = false;
                    break;
                }
                if (pos[i].second > max(pos[l].second, pos[r].second)) {
                    ok = false;
                    break;
                }
            }
            if (ok) ans++;
        }
    }

    cout << ans << endl;
}