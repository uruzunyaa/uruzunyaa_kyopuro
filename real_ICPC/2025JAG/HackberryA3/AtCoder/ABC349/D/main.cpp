#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)

int main() {
    ll l, r;
    cin >> l >> r;

	vector<PLL> ans;

	auto dfs = [&](auto dfs, ll l, ll r, ll a, ll b) -> void {
		if (l <= a && b <= r) {
			ans.emplace_back(a, b);
		}
		else if (b <= l || r <= a) {
			return;
		}
		else {
			ll m = (a + b) / 2;
			dfs(dfs, l, r, a, m);
			dfs(dfs, l, r, m, b);
		}
	};
	dfs(dfs, l, r, 0, 1LL << 60);

	cout << ans.size() << endl;
	for (auto [a, b] : ans) {
		cout << a << " " << b << endl;
	}

    return 0;
}
