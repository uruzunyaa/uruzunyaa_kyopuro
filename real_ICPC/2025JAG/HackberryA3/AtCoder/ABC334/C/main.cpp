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
	ll n, k; cin >> n >> k;
	vll a(k); cin >> a;

	vll socks;
	ll nowA = 0;
	rep(i, n) {
		if (a.size() && a[nowA] == i + 1) {
			nowA++;
		}
		else {
			socks.push_back(i);
		}
		if (a.size() && a[nowA] == i + 1) {
			nowA++;
		}
		else {
			socks.push_back(i);
		}
	}

	vll ldiff(socks.size() / 2, 0), rdiff(socks.size() / 2, 0);
	ll prevL = 0;
	ll prevR = 0;
	rep(i, socks.size()) {
		if (i % 2 == 0) {
			prevL = socks[i];
			prevR = socks[socks.size() - 1 - i];
		}
		else {
			ldiff[i / 2] = socks[i] - prevL;
			rdiff[i / 2] = prevR - socks[socks.size() - 1 - i];
		}
	}

	vll lsum(socks.size() / 2 + 1, 0), rsum(socks.size() / 2 + 1, 0);
	rep(i, socks.size() / 2) {
		lsum[i + 1] = lsum[i] + ldiff[i];
		rsum[i + 1] = rsum[i] + rdiff[i];
	}

	if (socks.size() % 2 == 0) {
		cout << lsum[socks.size() / 2] << endl;
		return 0;
	}

	ll ans = INF;
	rep(i, socks.size()) {
		if (i % 2 == 1) continue;

		ll sum = lsum[i / 2] + rsum[rsum.size() - 1 - i / 2];
		chmin(ans, sum);
	}

	cout << ans << endl;

	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	return solve();
}
