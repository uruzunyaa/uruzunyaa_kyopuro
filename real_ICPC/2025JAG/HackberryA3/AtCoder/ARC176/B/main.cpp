#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)

int main() {
    const vll digit = {6, 2, 4, 8};

    ll t;
    cin >> t;
    rep(i, t) {
        ll n, m, k;
        cin >> n >> m >> k;

        if (m - k == 1 && n == k) {
            cout << 0 << endl;
            continue;
        }
        if (n < m) {
            cout << digit[n % 4] << endl;
            continue;
        }

    }

    return 0;
}
