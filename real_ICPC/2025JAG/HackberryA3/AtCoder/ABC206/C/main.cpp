#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using P = pair<int, int>;
using PLL = pair<ll, ll>;
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define loop(i, a, b) for (int i = (a); i <= (b); ++i)

int main() {
	int n;
	cin >> n;
	vl a(n);
	rep(i, n) cin >> a[i];

	map<ll, ll> mp;

	ll ans = 0;
	rep(i, n) {
		ll aj = a[i];
		ans += i - mp[aj];
		mp[aj]++;
	}

	cout << ans << endl;

	return 0;
}