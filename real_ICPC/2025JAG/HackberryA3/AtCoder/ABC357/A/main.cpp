#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using P = pair<int, int>;
using PP = pair<int, P>;
using PLL = pair<ll, ll>;
using PPLL = pair<ll, PLL>;
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define loop(i, a, b) for(ll i = a; i <= b; ++i)
#define all(v) v.begin(), v.end()
const ll INF = 1001001001001001001LL;
const int INF32 = 1001001001;
const ll MOD = 998244353;

// Graph /////////////////////////////////////////////////////////
template <class T>
struct Edge {
	T from;
	T to;
	ll cost;
};
template <class T>
using Graph = vector<vector<Edge<T>>>;
//////////////////////////////////////////////////////////////////

int dx[8] = {0, 1, 0, -1, 1, 1, -1, -1};
int dy[8] = {1, 0, -1, 0, 1, -1, 1, -1};

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

	rep(i, n) {
		ll h; cin >> h;
		if (m - h < 0) {
			cout << i << endl;
			return 0;
		}
		m -= h;
	}

	cout << n << endl;

	return 0;
}
