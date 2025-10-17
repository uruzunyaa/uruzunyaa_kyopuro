#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)

ll dfs(ll x, ll y, ll n) {
    if (x == n) return (y == 0 ? 1 : 0);
    ll ret1 = 0;
    ll ret2 = 0;
    if (y <= 2 * (n - x)) ret1 = dfs(x + 1, y + 1, n);
    if (-(n - x) <= y) ret2 = dfs(x + 1, y - 2, n);
    return ret1 + ret2;
}

int main() {
    ll t;
    cin >> t;
    rep(i, t) {
        ll n;
        cin >> n;

		ll deno = 1;
		deno <<= n;

        ll ans = dfs(0, 0, n);
		ll g = gcd(ans, deno);
		ans /= g;
		deno /= g;
        if (ans == 0) cout << 0 << endl;
        else if (ans == deno) cout << 1 << endl;
        else cout << ans << "/" << deno << endl;
    }

    return 0;
}
