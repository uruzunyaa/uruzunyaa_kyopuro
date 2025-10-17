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
	map<ll, ll> m;

	rep(i, n){
		ll a, c; cin >> a >> c;
		if(m.count(c) == 0) m[c] = a;
		else m[c] = min(m[c], a);
	}

	ll ans = 0;
	for(auto v : m){
		ans = max(ans, v.second);
	}

	cout << ans << endl;

	return 0;
}
