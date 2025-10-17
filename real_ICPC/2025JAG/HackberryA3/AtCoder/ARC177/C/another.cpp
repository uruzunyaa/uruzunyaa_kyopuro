// #ダイクストラ
// できるだけ敵のマスを通らないように、赤と青の最短経路を求める
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
#define vlldbg(v) for(auto x : v) cout << x << " "; cout << endl;
#define vvlldbg(vv) for(auto v : vv) { vlldbg(v); }
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

struct DijkstraGridResult {
	vector<vector<ll>> dist;
	vector<vector<P>> prev;

	DijkstraGridResult(const vector<vector<ll>>& dist, const vector<vector<P>>& prev) : dist(dist), prev(prev) {}

	vector<ll> operator[](const int i) const { return dist[i]; }
	operator size_t() const { return dist.size(); }

	vector<P> restore(const P goal) const {
		vector<P> path;
		for (P now = goal; now != P(-1, -1); now = prev[now.first][now.second]) path.push_back(now);
		reverse(path.begin(), path.end());
		return path;
	}
};

template <class Iterable>
DijkstraGridResult dijkstra(const vector<Iterable> &grid, int sy, int sx) {
	vector<vector<ll>> dist(grid.size(), vector<ll>(grid[0].size(), INF));
	vector<vector<P>> prev(grid.size(), vector<P>(grid[0].size(), P(-1, -1)));
	priority_queue<PPLL, vector<PPLL>, greater<PPLL>> q;
	q.push({0, {sy, sx}});
	dist[sy][sx] = 0;

	while (!q.empty()) {
		auto [nowCost, pos] = q.top();
		auto [y, x] = pos;
		q.pop();
		if (dist[y][x] < nowCost) continue;

		// On visit

		rep(i, 4) {
			ll nx = x + dx[i];
			ll ny = y + dy[i];
			if (nx < 0 || grid[0].size() <= nx || ny < 0 || grid.size() <= ny) continue;
			if (dist[ny][nx] <= nowCost + grid[ny][nx]) continue;
			dist[ny][nx] = nowCost + grid[ny][nx];
			prev[ny][nx] = pos;
			q.push({dist[ny][nx], {ny, nx}});

			// On found
		}
	}

	return DijkstraGridResult(dist, prev);
}

int main() {
	ll n; cin >> n;
	vvll red(n, vll(n, 0)), blue(n, vll(n, 0));
	rep(i, n) {
		string s; cin >> s;
		rep(j, n) {
			if(s[j] == 'B') red[i][j] = 1;
			else if(s[j] == 'R') blue[i][j] = 1;
		}
	}

	auto redResult = dijkstra(red, 0, 0);
	auto blueResult = dijkstra(blue, 0, n - 1);

	cout << redResult[n - 1][n - 1] + blueResult[n - 1][0] << endl;

	return 0;
}
