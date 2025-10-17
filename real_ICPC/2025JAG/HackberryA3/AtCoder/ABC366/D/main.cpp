//#3次元累積和 #包除原理 #累積和
// 与えられた範囲の直方体の中の総和を求める問題。累積和を使って包除原理で求める。
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
constexpr ll INF = 1001001001001001001LL;
constexpr int INF32 = 1001001001;
constexpr ll MOD = 998244353;
constexpr ll MOD107 = 1000000007;

// Linear Algebra ////////////////////////////////////////////////
const double Rad2Deg = 180.0 / M_PI;
const double Deg2Rad = M_PI / 180.0;
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

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1) os << " ";
    }
    return os;
}
template <typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& vv) {
	for (size_t i = 0; i < vv.size(); ++i) {
		os << vv[i];
		if (i != vv.size() - 1) os << "\n";
    }
    return os;
}
template <typename T>
istream& operator>>(istream& is, vector<T>& v) {
	assert(v.size() > 0);
	for (int i = 0; i < v.size(); ++i) is >> v[i];
	return is;
}
template <typename T>
istream& operator>>(istream& is, vector<vector<T>>& vv) {
	assert(vv.size() > 0);
	for (int i = 0; i < vv.size(); ++i) is >> vv[i];
	return is;
}

struct phash {
	template<class T1, class T2>
    inline size_t operator()(const pair<T1, T2> & p) const {
        auto h1 = hash<T1>()(p.first);
        auto h2 = hash<T2>()(p.second);

		size_t seed = h1 + h2; 
		h1 = ((h1 >> 16) ^ h1) * 0x45d9f3b;
        h1 = ((h1 >> 16) ^ h1) * 0x45d9f3b;
        h1 = (h1 >> 16) ^ h1;
        seed ^= h1 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		h2 = ((h2 >> 16) ^ h2) * 0x45d9f3b;
        h2 = ((h2 >> 16) ^ h2) * 0x45d9f3b;
        h2 = (h2 >> 16) ^ h2;
        seed ^= h2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};





int solve() {
	ll n; cin >> n;
	vector<vvll> a(n, vvll(n, vll(n)));
	rep(x, n) rep(y, n) rep(z, n) cin >> a[x][y][z];

	// 原点から、(x, y, z)までの直方体の中の累積和を求める
	vector<vvll> dp(n, vvll(n, vll(n, 0)));
	rep(x, n) rep(y, n) rep(z, n) {
		dp[x][y][z] = a[x][y][z];
		if (x > 0) dp[x][y][z] += dp[x - 1][y][z];
		if (y > 0) dp[x][y][z] += dp[x][y - 1][z];
		if (z > 0) dp[x][y][z] += dp[x][y][z - 1];

		if (x > 0 && y > 0) dp[x][y][z] -= dp[x - 1][y - 1][z];
		if (x > 0 && z > 0) dp[x][y][z] -= dp[x - 1][y][z - 1];
		if (y > 0 && z > 0) dp[x][y][z] -= dp[x][y - 1][z - 1];

		if (x > 0 && y > 0 && z > 0) dp[x][y][z] += dp[x - 1][y - 1][z - 1];
	}

	// (x1, y1, z1)から(x2, y2, z2)までの直方体の中の総和を、dpを使って包除原理で求める
	ll q; cin >> q;
	rep(i, q) {
		ll x1, x2, y1, y2, z1, z2;
		cin >> x1 >> x2 >> y1 >> y2 >> z1 >> z2;
		--x1; --y1; --z1; --x2; --y2; --z2;
		ll ans = dp[x2][y2][z2];

		if (x1 > 0) ans -= dp[x1 - 1][y2][z2];
		if (y1 > 0) ans -= dp[x2][y1 - 1][z2];
		if (z1 > 0) ans -= dp[x2][y2][z1 - 1];

		if (x1 > 0 && y1 > 0) ans += dp[x1 - 1][y1 - 1][z2];
		if (x1 > 0 && z1 > 0) ans += dp[x1 - 1][y2][z1 - 1];
		if (y1 > 0 && z1 > 0) ans += dp[x2][y1 - 1][z1 - 1];

		if (x1 > 0 && y1 > 0 && z1 > 0) ans -= dp[x1 - 1][y1 - 1][z1 - 1];

		cout << ans << endl;
	}

	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	return solve();
}
