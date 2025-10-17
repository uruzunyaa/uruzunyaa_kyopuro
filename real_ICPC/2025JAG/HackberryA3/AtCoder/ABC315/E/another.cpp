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





int solve() {
	ll n;
	cin >> n;
	vvll g(n);
	rep(i, n) {
		ll c; cin >> c;
		rep(j, c) {
			ll a; cin >> a; a--;
			g[i].push_back(a);
		}
	}

	vector<bool> visited(n, false);
	vector<int> order;
	auto dfs = [&](auto dfs, int v) -> void {
		visited[v] = true;
		for (int to : g[v]) {
			if (visited[to]) continue;
			dfs(dfs, to);
		} 

		order.push_back(v);
	};
	dfs(dfs, 0);
	order.pop_back();

	transform(all(order), order.begin(), [](int x) { return x + 1; });
	printv(order);

	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	return solve();
}
