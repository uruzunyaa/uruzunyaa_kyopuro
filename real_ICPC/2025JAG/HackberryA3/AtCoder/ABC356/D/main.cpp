#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using P = pair<int, int>;
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)
const ll INF = 1001001001001001001LL;
const ll MOD = 998244353;

template <class T> inline bool chmax(T &a, const T &b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}
template <class T> inline bool chmin(T &a, const T &b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

int main() {
    ll n, m;
    cin >> n >> m;

    vll cnt(60, 0);
    for (int power = 59; power >= 0; --power) {
        if (n < 1LL << power) continue;

        rep(i, power) {
            cnt[i] += 1LL << (power - 1);
        }

        n -= 1LL << power;
        cnt[power] += n + 1;
    }

    ll ans = 0;
    int focus = 0;
    while (1LL << focus <= m) {
        if (m & 1LL << focus) {
            ans += cnt[focus] % MOD;
            ans %= MOD;
        }

        ++focus;
    }

    cout << ans << endl;

    return 0;
}
