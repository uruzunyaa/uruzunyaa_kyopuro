#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using PLL = pair<ll, ll>;
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define loop(i, a, b) for(ll i = a; i <= b; ++i)

int main() {
	ll n; cin >> n;
	vll a(n, 1);
	ll q; cin >> q;
	rep(i, q) {
		ll t; cin >> t;
		a[t - 1] = a[t-1] == 1 ? 0 : 1;
	}

	ll ans = 0;
	rep(i, n) {
		ans += a[i];
	}

	cout << ans << endl;

	return 0;
}
