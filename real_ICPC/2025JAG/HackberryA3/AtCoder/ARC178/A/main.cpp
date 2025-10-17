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
	set<ll> a;
	rep(i, m) {
		ll x;
		cin >> x;
		a.insert(x);

		if(x == 1) {
			cout << -1 << endl;
			return 0;
		}
	}

	if(n - *a.rbegin() == 0) {
		cout << -1 << endl;
		return 0;
	}

	queue<ll> skip;
	ll current = 1;
	ll prev = -1;
	for(int i = 1; i <= n; ++i) {
		if(a.count(i)) {
			if(i - prev != 1)
				skip.push(i);
			current++;
			cout << current << " ";
			prev = i;
		} else {
			if(skip.empty()) {
				cout << current << " ";
				current++;
			} else {
				cout << skip.front() << " ";
				skip.pop();
				current++;
			}
			prev = -1;
		}
	}

	return 0;
}
