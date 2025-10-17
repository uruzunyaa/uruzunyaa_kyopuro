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
	rep(i, n) {
		ll s; cin >> s;
		if (s <= 2) cout << "Contestant" << endl;
		else cout << "Writer" << endl;
	}

	return 0;
}
