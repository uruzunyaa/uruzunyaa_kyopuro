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

vector<string> f(ll n) {
	if (n == 0) return {"#"};

	ll sizeK = 1;
	rep(i, n - 1) sizeK *= 3;

	vector<string> mid(sizeK, string(sizeK, '.'));
	vector<string> around = f(n - 1);

	vector<string> res(3 * sizeK, string(3 * sizeK, '.'));
	// 一番上の行
	rep(i, around.size()) {
		rep(j, around.size() * 3) {
			res[i][j] = around[i][j % around.size()];
		}
	}
	// 一番下の行
	rep(i, around.size()) {
		rep(j, around.size() * 3) {
			res[i + 2 * sizeK][j] = around[i][j % around.size()];
		}
	}
	// 真ん中の左
	rep(i, around.size()) {
		rep(j, around.size()) {
			res[i + sizeK][j] = around[i][j];
		}
	}
	// 真ん中の右
	rep(i, around.size()) {
		rep(j, around.size()) {
			res[i + sizeK][j + 2 * sizeK] = around[i][j];
		}
	}
	// 真ん中
	rep(i, mid.size()) {
		rep(j, mid.size()) {
			res[i + sizeK][j + sizeK] = mid[i][j];
		}
	}

	return res;
}

int main() {
	ll n;
	cin >> n;

	vector<string> res = f(n);
	rep(i, res.size()) {
		cout << res[i] << endl;
	}

	return 0;
}
