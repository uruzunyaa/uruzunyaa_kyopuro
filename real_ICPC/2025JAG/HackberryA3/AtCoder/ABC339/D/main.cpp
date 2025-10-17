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





struct Players {
	PLL p1, p2;
};
int solve() {
	ll n; cin >> n;
	vector<string> s(n); cin >> s;

	PLL p1 = {-INF, -INF}, p2 = {-INF, -INF};
	rep(y, n) rep(x, n) {
		if (s[y][x] == 'P') {
			if (p1 == PLL{-INF, -INF}) p1 = {y, x};
			else p2 = {y, x};
			s[y][x] = '.';
		}
	}

	unordered_map<PLL, unordered_map<PLL, ll, phash>, phash> dist;
	queue<Players> q;
	q.push({p1, p2});
	dist[q.front().p1][q.front().p2] = 0;

	while(!q.empty()) {
		auto [p1, p2] = q.front();
		ll x1 = p1.second, y1 = p1.first;
		ll x2 = p2.second, y2 = p2.first;
		q.pop();

		// On visit

		rep(i, 4) {
			int nx1 = x1 + dx[i];
			int ny1 = y1 + dy[i];
			int nx2 = x2 + dx[i];
			int ny2 = y2 + dy[i];
			if ((nx1 < 0 || n <= nx1 || ny1 < 0 || n <= ny1) && (nx2 < 0 || n <= nx2 || ny2 < 0 || n <= ny2)) continue;
			if (nx1 < 0 || n <= nx1 || ny1 < 0 || n <= ny1) nx1 = x1, ny1 = y1;
			if (nx2 < 0 || n <= nx2 || ny2 < 0 || n <= ny2) nx2 = x2, ny2 = y2;
			if (s[ny1][nx1] == '#' && s[ny2][nx2] == '#') continue;
			if (s[ny1][nx1] == '#') nx1 = x1, ny1 = y1;
			if (s[ny2][nx2] == '#') nx2 = x2, ny2 = y2;
			PLL np1 = {ny1, nx1};
			PLL np2 = {ny2, nx2};
			if (dist.count(np1) && dist[np1].count(np2)) continue;
			if (dist.count(np2) && dist[np2].count(np1)) continue;
			dist[np1][np2] = dist[p1][p2] + 1;
			q.push({np1, np2});

			if (np1 == np2) {
				cout << dist[np1][np2] << endl;
				return 0;
			}
			// On found
		}
	}

	cout << -1 << endl;
	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	return solve();
}
