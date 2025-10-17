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
	vll a(n + 1, 0);
	rep(i, n) cin >> a[i + 1];

	map<ll, PLL> mp;
	mp[0] = {0, 0};
	rep(i, n) {
		mp[a[i + 1]] = {a[i + 1], i + 1};
	}

	vector<PLL> ans;
	rep(i, n + 1) {
		if(mp[i].first == mp[i].second) continue;

		ll now = mp[i].second;
		ll go = mp[i].first;
		if(now < go) ans.push_back({now, go});
		else ans.push_back({go, now});

		mp[a[go]].second = now;
		swap(a[now], a[go]);
	}

	cout << ans.size() << endl;
	rep(i, ans.size()) {
		cout << ans[i].first << " " << ans[i].second << endl;
	}

	return 0;
}
