#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using PLL = pair<ll, ll>;
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define loop(i, a, b) for(ll i = a; i <= b; ++i)

int main() {
	ll n;
	cin >> n;

	vector<PLL> a(n);

	ll minI = 0;
	rep(i, n) {
		cin >> a[i].first >> a[i].second;
		if(a[minI].second - a[minI].first <= a[i].second - a[i].first) { minI = i; }
	}

	ll height = 0;
	rep(i, n) {
		if(i == minI) height += a[i].second;
		else height += a[i].first;
	}

	cout << height << endl;

	return 0;
}
