#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using PLL = pair<ll, ll>;
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define loop(i, a, b) for(ll i = a; i <= b; ++i)

struct point {
	ll x, y, i;
	point(ll x, ll y, ll i) : x(x), y(y), i(i) {}
};

int main() {
	ll n; cin >> n;
	vector<point> p;
	rep(i, n) {
		ll x, y; cin >> x >> y;
		p.emplace_back(x, y, i + 1);
	}

	rep(i, n){
		vector<PLL> v;
		rep(j, n){
			if(i == j) continue;
			ll dx = p[j].x - p[i].x;
			ll dy = p[j].y - p[i].y;
			v.emplace_back(dx * dx + dy * dy, p[j].i);
		}

		sort(v.begin(), v.end());

		ll mini = v.back().second;
		ll dist = v.back().first;
		for(ll j = v.size() - 1; j >= 0; --j){
			if(dist != v[j].first) break;
			mini = min(mini, v[j].second);
		}

		cout << mini << endl;
	}

	return 0;
}
