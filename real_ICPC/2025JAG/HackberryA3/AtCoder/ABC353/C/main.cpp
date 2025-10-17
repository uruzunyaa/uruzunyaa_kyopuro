#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using P = pair<int, int>;
using PLL = pair<ll, ll>;
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define loop(i, a, b) for(ll i = a; i <= b; ++i)
const ll INF = 1001001001001001001LL;

template <class T>
inline bool chmax(T &a, const T &b) {
	if (a < b) {
		a = b;
		return true;
	}
	return false;
}
template <class T>
inline bool chmin(T &a, const T &b) {
	if (a > b) {
		a = b;
		return true;
	}
	return false;
}

int main() {
	ll n;
	cin >> n;

	vll a(n);
	ll sum = 0;
	rep(i, n){
		cin >> a[i];

		sum += a[i] * (n - 1);
	}

	sort(a.begin(), a.end());

	rep(i, n - 1){
		auto it = lower_bound(a.begin() + i + 1, a.end(), 100000000LL - a[i]);
		ll idx = it - a.begin();
		sum -= 100000000LL * (n - idx); 
	}

	cout << sum << endl;

	return 0;
}
