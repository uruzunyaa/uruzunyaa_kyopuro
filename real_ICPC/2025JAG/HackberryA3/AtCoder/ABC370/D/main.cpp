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
	ll h, w, q; cin >> h >> w >> q;
	vector<set<PLL>> row(h), col(w);
	rep(i, h) rep(j, w) row[i].insert({i, j});
	rep(j, w) rep(i, h) col[j].insert({i, j});

	rep(i, q) {
		ll r, c; cin >> r >> c;
		--r, --c;

		if (row[r].count({r, c})) {
			row[r].erase({r, c});
			col[c].erase({r, c});
		} else {
			auto nearestHor = row[r].lower_bound({r, c});
			auto nearestVer = col[c].lower_bound({r, c});
			auto nearestHorPrev = nearestHor;
			auto nearestVerPrev = nearestVer;

			PLL toErase1 = nearestHor != row[r].end() ? *nearestHor : PLL(-1, -1);
			PLL toErase2 = nearestVer != col[c].end() ? *nearestVer : PLL(-1, -1);
			PLL toErase3 = PLL(-1, -1), toErase4 = PLL(-1, -1);
			if (nearestHorPrev != row[r].begin()) {
				nearestHorPrev--;
				toErase3 = *nearestHorPrev;
			}
			if (nearestVerPrev != col[c].begin()) {
				nearestVerPrev--;
				toErase4 = *nearestVerPrev;
			}

			if (toErase1.first != -1) {
				row[toErase1.first].erase(toErase1);
				col[toErase1.second].erase(toErase1);
			}
			if (toErase2.first != -1) {
				row[toErase2.first].erase(toErase2);
				col[toErase2.second].erase(toErase2);
			}
			if (toErase3.first != -1) {
				row[toErase3.first].erase(toErase3);
				col[toErase3.second].erase(toErase3);
			}
			if (toErase4.first != -1) {
				row[toErase4.first].erase(toErase4);
				col[toErase4.second].erase(toErase4);
			}
		}
	}

	ll ans = 0;
	rep(i, h) ans += row[i].size();

	cout << ans << endl;

	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	return solve();
}
