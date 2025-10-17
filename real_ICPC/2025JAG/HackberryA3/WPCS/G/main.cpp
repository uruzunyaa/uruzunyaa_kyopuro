#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using PLL = pair<ll, ll>;
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define loop(i, a, b) for(ll i = a; i <= b; ++i)

int main() {
	ll t; cin >> t;
	rep(i, t){
		ll n, m; cin >> n >> m;
		vll a(n);
		rep(j, n) cin >> a[j];
		vll b(m);
		rep(j, m) cin >> b[j];

		sort(a.rbegin(), a.rend());
		sort(b.rbegin(), b.rend());
		bool ok = true;
		rep(j, m){
			if (a[j] < b[j]){
				ok = false;
				break;
			}
		}

		cout << (ok ? "Yes" : "No") << endl;
	}

	return 0;
}
