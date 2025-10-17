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
	ll n, m;
	cin >> n >> m;

	vll a(m);
	rep(i, m) {
		cin >> a[i];
	}
	vll today(m, 0);
	rep(i, n){
		rep(j, m){
			ll x; cin >> x;
			today[j] += x;
		}
	}

	bool ok = true;
	rep(i, m){
		if(today[i] < a[i]){
			ok = false;
			break;
		}
	}

	cout << (ok ? "Yes" : "No") << endl;

	return 0;
}
