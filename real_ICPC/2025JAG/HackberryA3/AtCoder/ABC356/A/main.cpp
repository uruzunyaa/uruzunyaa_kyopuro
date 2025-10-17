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
	ll n, l, r;
	cin >> n >> l >> r;

	for(int i = 1; i < l; ++i) {
		cout << i << " ";
	}
	for(int i = r; i >= l; --i) {
		cout << i << " ";
	}
	loop(i, r + 1, n) {
		cout << i << " ";
	}

	return 0;
}
