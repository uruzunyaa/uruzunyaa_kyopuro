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
		ll x, y, z; cin >> x >> y >> z;
		ll cost = x * 400 + y * 300 + z * 200;
		ll minCnt = min(x, min(y, z));
		cost -= minCnt * 200;
		cout << cost << endl;
	}

	return 0;
}
