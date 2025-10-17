// #トポロジカルソート
// 動物の捕食関係が与えられ、ヒエラルキー順に周囲のマスの動物を食べたときの結果を出力する
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using P = pair<int, int>;
using PLL = pair<ll, ll>;
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define loop(i, a, b) for(ll i = a; i <= b; ++i)
#define all(v) v.begin(), v.end()
const ll INF = 1001001001001001001LL;

template <class T> struct Edge
{
    int from;
    int to;
    T val;

	Edge() : from(-1), to(-1), val(1) {}
	Edge(const int& i) { from = -1, to = i; val = 1; }
	Edge(int from, int to) : from(from), to(to), val(1) {}
	Edge(int from, int to, T val) : from(from), to(to), val(val) {}
	bool operator<(const Edge &e) const { return val < e.val; }
	bool operator<=(const Edge &e) const { return val <= e.val; }
	bool operator>(const Edge &e) const { return val > e.val; }
	bool operator>=(const Edge &e) const { return val >= e.val; }
	bool operator==(const Edge &e) const { return from == e.from && to == e.to && val == e.val; }
	bool operator!=(const Edge &e) const { return from != e.from || to != e.to || val != e.val; }

	operator int() const { return to; }

	friend ostream& operator << (ostream& os, const Edge& e) {
		os << e.from << " -> " << e.to << " : " << e.val;
		return os;
	}
};
template <class T> using Graph = vector<vector<Edge<T>>>;

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

int dx[8] = {0, 1, 0, -1, 1, 1, -1, -1};
int dy[8] = {-1, 0, 1, 0, -1, 1, 1, -1};

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

int main() {
	ll h, w; cin >> h >> w;
	vector<vector<char>> grid(h, vector<char>(w));
	map<char, vector<P>> animalMap;
	rep(i, h)rep(j, w) {
		cin >> grid[i][j];
		animalMap[grid[i][j]].push_back({i, j});
	}
	
	ll n; cin >> n;
	vector<vector<int>> g(26, vector<int>());
	rep(i, n) {
		char p, v;
		cin >> p >> v;
		g[p - 'a'].emplace_back(v - 'a');
	}

	vector<int> order = topologicalSort(g);

	rep(i, order.size()) {
		int animal = order[i];

		for(const auto& [y, x] : animalMap[animal + 'a']){
			if (grid[y][x] == '-') continue;
			rep(j, 8) {
				int nx = x + dx[j];
				int ny = y + dy[j];
				if (nx < 0 || w <= nx || ny < 0 || h <= ny) continue;
				bool canEat = false;
				for(const auto& eatlist : g[animal]){
					if(grid[ny][nx] == eatlist + 'a'){
						canEat = true;
						break;
					}
				}
				if (!canEat) continue;
				grid[ny][nx] = '-';
			}
		}
	}

	rep(i, h){
		rep(j, w){
			cout << grid[i][j];
			if(j != w - 1) cout << " ";
		}
		cout << endl;
	}

	return 0;
}
