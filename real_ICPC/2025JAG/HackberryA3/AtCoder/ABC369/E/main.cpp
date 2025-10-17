// #ワーシャルフロイド #順列全探索 #bit全探索
// 島と橋の情報が与えられ、Q回のクエリでBiの橋を通るときの最短距離を求める問題。
// ワーシャルフロイドで全点間の最短距離を求めておき、クエリごとにどの順番で必ず通る橋を回るかを、順列全探索で決め、bit全探索で各橋をどの方向に通るかを決める。

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



void warshall_floyd(vector<vector<long long>> &dist) {
    int V = dist.size();
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

int solve() {
	ll n, m; cin >> n >> m;
	vvll dist(n, vll(n, INF));
	vector<PPLL> edges;
	rep(i, n) dist[i][i] = 0;
	rep(i, m) {
		ll u, v, t; cin >> u >> v >> t;
		--u; --v;
		edges.emplace_back(t, PLL(u, v));
		dist[u][v] = min(dist[u][v], t);
		dist[v][u] = min(dist[v][u], t);
	}
	warshall_floyd(dist);


	ll q; cin >> q;
	rep(i, q) {
		ll k; cin >> k;
		vll b(k); cin >> b;
		rep(j, k) --b[j];

		// k個で順列を全探索
		vll perm(k);
		rep(j, k) perm[j] = j;
		ll ans = INF;
		do {
			rep(dir, 1LL << k) {
				ll sum = 0;
				ll now = 0;
				rep(j, k) {
					ll next = (dir >> j) & 1 ? edges[b[perm[j]]].second.second : edges[b[perm[j]]].second.first;
					ll t = edges[b[perm[j]]].first;

					ll tnext = dist[now][next] + t;

					sum += tnext;
					now = (dir >> j) & 1 ? edges[b[perm[j]]].second.first : edges[b[perm[j]]].second.second;

					if (j == k - 1) {
						ll next = n - 1;
						tnext = dist[now][next];

						sum += tnext;
						now = next;
					}
				}
				chmin(ans, sum);
			}

		} while (next_permutation(all(perm)));

		cout << ans << endl;
	}


	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	return solve();
}
