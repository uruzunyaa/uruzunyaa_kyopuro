// #トポロジカルソート #DFS
// 依存関係グラフ上で特定のノードに到達するための最短経路
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
const ll INF = 1001001001001001001LL;
const int INF32 = 1001001001;
const ll MOD = 998244353;

// Graph /////////////////////////////////////////////////////////
template <class T>
struct Edge {
	T from;
	T to;
	ll cost;
};
template <class T>
using Graph = vector<vector<Edge<T>>>;
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

template <class T>
void printv(const vector<T>& v) {
	if (v.empty()) { cout << endl; return; }
	rep(i, v.size() - 1) cout << v[i] << " ";
	cout << v.back() << endl;
}
template <class T>
void printvv(const vector<vector<T>>& vv) {
	for (const vector<T>& v : vv) printv(v);
}


/**
* @brief トポロジカルソートO(V + E)
* @details 有向グラフの依存関係を考慮したソート
* @remark グラフが有向非巡回グラフ(DAG)の場合のみ使用可能
* @remark queueをpriority_queueに変えると、辞書順最小/最大のトポロジカルソートが得られる
* @param graph 隣接リスト
* @return トポロジカルソートされた頂点番号 (閉路があった場合は空のvectorを返す)
*/
template <class Iterable>
vector<int> topologicalSort(const vector<Iterable>& graph) {
	vector<int> result;
	vector<int> in(graph.size(), 0);

	for(const Iterable& v : graph) {
		for(const auto& to : v) {
			in[to]++;
		}
	}

	queue<int> q;
	for (int i = 0; i < in.size(); ++i) {
		if (in[i] == 0) q.push(i);
	}

	while (!q.empty()) {
		int v = q.front(); q.pop();
		result.push_back((int)v);

		for (const auto& to : graph[v]) {
			if (--in[to] == 0) q.push(to);
		}
	}

	return result.size() == graph.size() ? result : vector<int>();
}


int solve() {
	ll n; cin >> n;
	vvll g(n, vll(0));
	rep(i, n) {
		ll c; cin >> c;
		rep(j, c) {
			ll a; cin >> a;
			--a;
			g[a].push_back(i);
		}
	}
	vvll invG(n, vll(0));
	rep(i, n) {
		for (ll to : g[i]) {
			invG[to].push_back(i);
		}
	}

	vector<int> order = topologicalSort(g);

	unordered_set<ll> sub;
	auto dfs = [&](auto self, ll v) -> void {
		sub.insert(v);
		for (ll to : invG[v]) {
			if (sub.count(to)) continue;
			self(self, to);
		}
	};
	dfs(dfs, 0);

	for(int v : order) {
		if (sub.count(v) && v != 0) {
			cout << v + 1 << " ";
		}
	}
	cout << endl;

	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	return solve();
}
