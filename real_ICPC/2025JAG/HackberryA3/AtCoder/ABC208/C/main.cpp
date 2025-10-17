#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using PLL = pair<ll, ll>;
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define loop(i, a, b) for(ll i = a; i <= b; ++i)

int main() {
	ll n, k; cin >> n >> k;
	vll a(n);
	vll sorted_a(n);
	rep(i, n) cin >> a[i];
	sorted_a = vll(a);
	sort(sorted_a.begin(), sorted_a.end());
	
	ll ans = k / n;
	rep(i, n){
		if (lower_bound(sorted_a.begin(), sorted_a.end(), a[i]) - sorted_a.begin() < k % n) cout << ans + 1 << endl;
		else cout << ans << endl;
	}

	return 0;
}
