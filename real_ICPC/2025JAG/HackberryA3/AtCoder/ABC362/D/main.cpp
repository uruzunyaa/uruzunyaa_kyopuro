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

struct DijkstraResult {
	vector<ll> dist;
	vector<int> prev;

	DijkstraResult(const vector<ll>& dist, const vector<int>& prev) : dist(dist), prev(prev) {}

	ll operator[](const int i) const { return dist[i]; }
	operator size_t() const { return dist.size(); }

	/**
	 * @brief スタート地点からgoalまでの経路を復元する O(E)
	 * @param goal 経路復元したいノード 
	 * @return vector<long long> スタート地点からgoalまでの経路
	*/
	vector<int> restore(const int goal) const {
		vector<int> path;
		for (int now = goal; now != -1; now = prev[now]) path.push_back(now);
		reverse(path.begin(), path.end());
		return path;
	}
};

/**
 * @brief グラフの最短経路を求める O(|E| log |V|)
 * @remark コストに負の値があるときは使えない
 * @remark 全ての辺がコスト1の場合はBFSで求まる
 * @param G 隣接リスト
 * @param start スタート地点のノード番号
 * @return DijkstraGridResult dist[x] にスタート地点からxまでの最短距離が格納される @n restore(long long goal)で経路復元できる
*/
template <class T>
DijkstraResult dijkstra(const vector<vector<Edge<T>>> &G, const int start, const T inf) {
	vector<T> dist(G.size(), inf);
	vector<int> prev(G.size(), -1);
	priority_queue<PLL, vector<PLL>, greater<PLL>> q;
	q.push({0, start});
	dist[start] = 0;

	while (!q.empty()) {
		auto [nowCost, now] = q.top();
		q.pop();
		if (dist[now] < nowCost) continue;

		// On visit

		for (const Edge<T>& e : G[now]) {
			if (dist[e.to] <= dist[now] + e.val) continue;
			dist[e.to] = dist[now] + e.val;
			prev[e.to] = now;
			q.push({dist[e.to], e.to});

			// On found
		}
	}

	return DijkstraResult(dist, prev);
}

int solve() {
	ll n, m; cin >> n >> m;
	vll a(n); cin >> a;
	
	Graph<ll> G(n);
	rep(i, m) {
		ll u, v, b; cin >> u >> v >> b;
		--u, --v;
		G[u].emplace_back(u, v, a[v] + b);
		G[v].emplace_back(v, u, a[u] + b);
	}

	auto res = dijkstra(G, 0, INF);

	loop(i, 1, n - 1) {
		cout << res[i] + a[0] << " ";
	}

	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	return solve();
}
