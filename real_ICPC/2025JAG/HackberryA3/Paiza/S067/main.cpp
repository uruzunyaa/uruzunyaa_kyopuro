#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using P = pair<int, int>;
using PP = pair<int, P>;
using PLL = pair<ll, ll>;
using PPLL = pair<ll, PLL>;
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define rrep(i, n) for(ll i = n - 1; i >= 0; --i)
#define loop(i, a, b) for(ll i = a; i <= b; ++i)
#define all(v) v.begin(), v.end()
#define nC2(n) n * (n - 1) / 2
constexpr ll INF = 9009009009009009009LL;
constexpr int INF32 = 2002002002;
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

template <typename Container,
          typename = std::enable_if_t<
              !std::is_same_v<Container, std::string> &&
              std::is_convertible_v<decltype(std::declval<Container>().begin()),
                                    typename Container::iterator>>>
ostream &operator<<(ostream &os, const Container &container) {
    auto it = container.begin();
    auto end = container.end();

    if (it != end) {
        os << *it;
        ++it;
    }
	for (; it != end; ++it) {
		os << " " << *it;
	}
    return os;
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
	for (size_t i = 0; i < v.size(); ++i) is >> v[i];
	return is;
}
template <typename T>
istream& operator>>(istream& is, vector<vector<T>>& vv) {
	assert(vv.size() > 0);
	for (size_t i = 0; i < vv.size(); ++i) is >> vv[i];
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




/**
* @brief トポロジカルソートO(V + E)
* @details 有向グラフの依存関係を考慮したソート
* @remark グラフが有向非巡回グラフ(DAG)の場合のみ使用可能
* @remark queueをpriority_queueに変えると、辞書順最小/最大のトポロジカルソートが得られる
* @remark 特定の頂点への最短経路を求める場合は、向きを反転したグラフに、その頂点から帰りがけ順にDFSをする
* @param graph 隣接リスト
* @return トポロジカルソートされた頂点番号 (閉路があった場合は空のvectorを返す)
*/
template <class T>
vector<int> topologicalSort(const vector<vector<T>>& graph) {
	vector<int> result;
	vector<int> in(graph.size(), 0);

	for(const auto& v : graph) {
		for(const int& to : v) {
			in[to]++;
		}
	}

	queue<int> q;
	for (int i = 0; i < in.size(); ++i) {
		if (in[i] == 0) q.push(i);
	}

	while (!q.empty()) {
		int v = q.front(); q.pop();
		result.push_back(v);

		for (const int& to : graph[v]) {
			if (--in[to] == 0) q.push(to);
		}
	}

	return result.size() == graph.size() ? result : vector<int>();
}

bool hasCycle(const vvll &G, int v, vector<bool> &seen,  vector<bool> &finished) {
    seen[v] = true;    // 行きがけ時に true になる
    for (const ll &to : G[v]) {
        // 頂点toがすでに探索済みの場合はスキップ 
        if (finished[to]) continue;

        // サイクル検出
        if (seen[to] && !finished[to]) return true;

        // 頂点 v2 を再帰的に探索
        if (hasCycle(G, to, seen, finished)) return true;
    }
    finished[v] = true;  // 帰りがけ時に true になる
    return false;
}

int solve() {
	ll n, m; cin >> n >> m;
	vvll g(n);
	unordered_set<PLL, phash> edges;
	rep(i, m) {
		ll a, b; cin >> a >> b;
		--a, --b;
		g[a].push_back(b);
		edges.insert({a, b});
	}

	rep(i, n) {
		vector<bool> seen(n, false), finished(n, false);
		if (hasCycle(g, i, seen, finished)) {
			cout << -1 << endl;
			return 0;
		}
	}

	auto sorted = topologicalSort(g);
	rep(i, sorted.size() - 1) {
		if (!edges.count({sorted[i], sorted[i + 1]})) {
			cout << -1 << endl;
			return 0;
		}
	}

	for (const int& v : sorted) {
		cout << v + 1;
		if (v != sorted.back()) cout << " ";
		else cout << endl;
	}

	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	return solve();
}
