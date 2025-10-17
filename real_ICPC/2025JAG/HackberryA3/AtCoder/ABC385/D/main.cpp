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
	ll n, m, sx, sy;
	cin >> n >> m >> sx >> sy;
	vll X(n), Y(n);
	rep(i, n) cin >> X[i] >> Y[i];
	vector<char> D(m);
	vll C(m);
	rep(i, m) cin >> D[i] >> C[i];

	auto nX = X, nY = Y;
	sort(all(X));
	sort(all(Y));
    sort(nX.begin(), nX.end());
    nX.erase(unique(nX.begin(), nX.end()), nX.end());
    sort(nY.begin(), nY.end());
    nY.erase(unique(nY.begin(), nY.end()), nY.end());

	// 座標圧縮後の点のリスト
	vvll x(n), y(n);

    // ソートした座標圧縮
    for (int i = 0; i < n; ++i) {
        ll xres = lower_bound(nX.begin(), nX.end(), X[i]) - nX.begin();
        ll yres = lower_bound(nY.begin(), nY.end(), Y[i]) - nY.begin();
		x[xres].push_back(yres);
		y[yres].push_back(xres);
    }

	vector<PPLL> xpath, ypath;
	rep(i, m) {
		ll nowX = upper_bound(all(nX), sx) - nX.begin();
		nowX--;
		ll nowY = upper_bound(all(nY), sy) - nY.begin();
		nowY--;

		ll dx = 0, dy = 0;
		if (D[i] == 'L') dx = -C[i];
		if (D[i] == 'R') dx = C[i];
		if (D[i] == 'U') dy = C[i];
		if (D[i] == 'D') dy = -C[i];

		ll nx = sx + dx;
		ll ny = sy + dy;
		ll nresX = upper_bound(all(nX), nx) - nX.begin();
		nresX--;
		ll nresY = upper_bound(all(nY), ny) - nY.begin();
		nresX--;

		if (dx == 0) {
			xpath.push_back({nowY, {min(nowX, nresX), max(nowX, nresX)}});
		}
		else if (dy == 0) {
			ypath.push_back({nowX, {min(nowY, nresY), max(nowY, nresY)}});
		}
		else {
			assert(false);
		}
	}

	sort(all(xpath));
	sort(all(ypath));

	ll ans = 0;
	rep(i, xpath.size()) {
		ll y = xpath[i].first;
		ll l = xpath[i].second.first;
		ll r = xpath[i].second.second;

		ll range = r - l;
		while (i + 1 < xpath.size() && y == xpath[i + 1].first && r >= xpath[i + 1].second.first) {
			range = max(range, xpath[i + 1].second.second - l);
			r = max(r, xpath[i + 1].second.second);
			i++;
		}

		ans += range;
	}

	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	return solve();
}
