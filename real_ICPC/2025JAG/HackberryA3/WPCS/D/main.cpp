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
	rep(i, t) {
		ll n; cin >> n;
		vector<double> a(n);
		rep(j, n) cin >> a[j];

		double avg = accumulate(a.begin(), a.end(), 0) / (double)n;
		ll cnt = 0;
		rep(j, n) {
			if (a[j] <= avg) ++cnt;
		}

		if(cnt * 2 >= n) cout << "Yes" << endl;
		else cout << "No" << endl;
	}

	return 0;
}
