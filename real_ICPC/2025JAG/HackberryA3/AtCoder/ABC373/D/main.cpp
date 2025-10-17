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

template <class T> struct Edge
{
    int from;
    int to;
    T val;

	Edge() : from(-1), to(-1), val(T()) {}
	Edge(const int& i) : from(-1), to(i), val(T()) {} 
	Edge(int from, int to) : from(from), to(to), val(T()) {}
	Edge(int from, int to, T val) : from(from), to(to), val(val) {}
	bool operator==(const Edge &e) const { return from == e.from && to == e.to && val == e.val; }
	bool operator!=(const Edge &e) const { return from != e.from || to != e.to || val != e.val; }
	bool operator<(const Edge &e) const { return val < e.val; }
	bool operator>(const Edge &e) const { return val > e.val; }
	bool operator<=(const Edge &e) const { return val <= e.val; }
	bool operator>=(const Edge &e) const { return val >= e.val; }

	operator int() const { return to; }

	friend ostream& operator << (ostream& os, const Edge& e) {
		os << e.from << " -> " << e.to << " : " << e.val;
		return os;
	}
};
template <class T> using Graph = vector<vector<Edge<T>>>;




int solve() {
	ll n, m; cin >> n >> m;
	Graph<ll> g(n);
	Graph<ll> invg(n);
	rep(i, m) {
		ll u, v, w; cin >> u >> v >> w;
		--u; --v;
		g[u].emplace_back(u, v, w);
		invg[v].emplace_back(v, u, w);
	}

	vll dist(n, 0);
	vll seen(n, 0);
	rep(i, n) {
		if (seen[i]) continue;
		seen[i] = 1;
		queue<ll> q;
		q.push(i);
		while (!q.empty()) {
			ll now = q.front(); q.pop();
			for (auto e : g[now]) {
				if (seen[e.to]) continue;
				seen[e.to] = 1;
				dist[e.to] = dist[now] + e.val;
				q.push(e.to);
			}
			for (auto e : invg[now]) {
				if (seen[e.to]) continue;
				seen[e.to] = 1;
				dist[e.to] = dist[now] - e.val;
				q.push(e.to);
			}
		}
	}

	cout << dist << endl;

	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	return solve();
}
