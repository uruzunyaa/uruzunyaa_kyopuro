#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using PLL = pair<ll, ll>;
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define loop(i, a, b) for(ll i = a; i <= b; ++i)

int main() {
	ll a = 0, b = 0;
	rep(i, 9){
		ll x; cin >> x;
		a += x;
	}
	rep(i, 8){
		ll x; cin >> x;
		b += x;
	}

	cout << a - b + 1 << endl;

	return 0;
}
