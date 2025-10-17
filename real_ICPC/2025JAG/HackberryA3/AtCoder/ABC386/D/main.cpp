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
	ll n, m; cin >> n >> m;
	vector<PLL> b_sortX, b_sortY;
	vector<PLL> w_sortX, w_sortY;
	rep(i, m) {
		ll x, y; cin >> x >> y;
		char c; cin >> c;

		if (c == 'B') {
			b_sortX.emplace_back(x, y);
			b_sortY.emplace_back(y, x);
		} else {
			w_sortX.emplace_back(x, y);
			w_sortY.emplace_back(y, x);
		}
	}

	sort(all(b_sortX));
	sort(all(b_sortY));
	sort(all(w_sortX));
	sort(all(w_sortY));

	ll bi = 0, wi = 0;
	ll wmn = INF;
	while (wi < w_sortX.size()) {
		ll wx = w_sortX[wi].first;
		while (bi < b_sortX.size() && b_sortX[bi].first < wx) {
			if (b_sortX[bi].second > wmn) {
				cout << "No" << endl;
				return 0;
			}
			++bi;
		}

		chmin(wmn, w_sortX[wi].second);
		++wi;
	}
	while (bi < b_sortX.size()) {
		if (b_sortX[bi].second > wmn) {
			cout << "No" << endl;
			return 0;
		}
		++bi;
	}

	bi = 0, wi = 0;
	wmn = INF;
	while (wi < w_sortY.size()) {
		ll wy = w_sortY[wi].first;
		while (bi < b_sortY.size() && b_sortY[bi].first < wy) {
			if (b_sortY[bi].second > wmn) {
				cout << "No" << endl;
				return 0;
			}
			++bi;
		}

		chmin(wmn, w_sortY[wi].second);
		++wi;
	}
	while (bi < b_sortY.size()) {
		if (b_sortY[bi].second > wmn) {
			cout << "No" << endl;
			return 0;
		}
		++bi;
	}

	cout << "Yes" << endl;

	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	return solve();
}
