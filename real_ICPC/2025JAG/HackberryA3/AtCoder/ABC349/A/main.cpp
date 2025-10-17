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
	ll sum = 0;
	rep(i, n - 1) {
		ll a; cin >> a;
		sum += a;
	}

	cout << -sum << endl;

	return 0;
}
