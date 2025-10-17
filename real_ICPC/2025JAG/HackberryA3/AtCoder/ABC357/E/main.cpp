#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using P = pair<int, int>;
using PP = pair<int, P>;
using PLL = pair<ll, ll>;
using PPLL = pair<ll, PLL>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)
#define all(v) v.begin(), v.end()
#define nC2(n) n *(n - 1) / 2
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

template <class T> inline bool chmax(T &a, const T &b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}
template <class T> inline bool chmin(T &a, const T &b) {
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
template <typename T> ostream &operator<<(ostream &os, const vector<T> &v) {
    for (size_t i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1) os << " ";
    }
    return os;
}
template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &vv) {
    for (size_t i = 0; i < vv.size(); ++i) {
        os << vv[i];
        if (i != vv.size() - 1) os << "\n";
    }
    return os;
}
template <typename T> istream &operator>>(istream &is, vector<T> &v) {
    assert(v.size() > 0);
    for (size_t i = 0; i < v.size(); ++i)
        is >> v[i];
    return is;
}
template <typename T> istream &operator>>(istream &is, vector<vector<T>> &vv) {
    assert(vv.size() > 0);
    for (size_t i = 0; i < vv.size(); ++i)
        is >> vv[i];
    return is;
}

struct phash
{
    template <class T1, class T2>
    inline size_t operator()(const pair<T1, T2> &p) const {
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

template <class T>
vector<vector<T>> inverseGraph(const vector<vector<T>>& G) {
	vector<vector<T>> rG(G.size());
	rep(i, G.size()) for (const T& e : G[i]) rG[e].push_back(i);
	return rG;
}
template <class T>
vector<vector<Edge<T>>> inverseGraph(const vector<vector<Edge<T>>>& G) {
	vector<vector<Edge<T>>> rG(G.size());
	rep(i, G.size()) for (const Edge<T>& e : G[i]) rG[e.to].push_back(Edge<T>(e.to, e.from, e.val));
	return rG;
}

/**
 * @brief 強連結成分分解(Strongly Connected Components)
 */
struct SCC
{
  private:
    // 元の頂点数
    long long n;
    // G: 元のグラフ, rG: 逆辺を張ったグラフ
    vector<vector<long long>> G, rG;

    // order: トポロジカルソート
    vector<long long> order;

	// component: 各頂点が属する強連結成分の番号
    vector<long long> component;
	// component_size: 強連結成分のサイズ
    vector<long long> components_size;
	// component_count: 強連結成分の数
	long long component_count = 0;

	vector<vector<long long>> rebuildedG;

	// 1度目のDFSでトポロジカルソートを行う O(|V|+|E|)
    void topological_sort() {
        vector<bool> used(n, false);
        auto dfs = [&used, this](auto dfs, long long v) -> void {
            used[v] = 1;
            for (auto nv : G[v]) {
                if (!used[nv]) dfs(dfs, nv);
            }
            order.push_back(v);
        };

        for (long long v = 0; v < n; ++v) {
            if (!used[v]) dfs(dfs, v);
        }

        reverse(order.begin(), order.end());
    }
	// 2度目のDFSで逆辺のグラフでトポロジカル順に強連結成分を探す O(|V|+|E|)
    void search_components() {
        auto dfs = [this](auto dfs, long long v, long long k) -> void {
            component[v] = k;
            components_size[k]++;
            for (auto nv : rG[v]) {
                if (component[nv] == -1) dfs(dfs, nv, k);
            }
        };

		for (auto v : order) {
			if (component[v] == -1) {
				components_size.push_back(0);
				dfs(dfs, v, component_count++);
			}
		}
    }
	/**
	* @brief 強連結成分を1つのノードとして扱うグラフを再構築する O(|V|+|E|)
	*/
    void rebuild() {
		rebuildedG.resize(component_count);

        set<pair<long long, long long>> connected;
        for (long long v = 0; v < n; v++) {
            for (auto nv : G[v]) {
				long long v_comp = component[v];
				long long nv_comp = component[nv];
				pair<long long, long long> p = {v_comp, nv_comp};
                if (!is_same(v, nv) &&
                    !connected.count(p)) {
                    rebuildedG[v_comp].push_back(nv_comp);
					connected.insert(p);
                }
            }
        }
    }

  public:
	/**
	 * @brief 強連結成分分解を行う O(3 * |V|+|E|)
	 */
    SCC(vector<vector<long long>> &_G)
        : n(_G.size()), G(_G), rG(vector<vector<long long>>(n)), component(vector<long long>(n, -1)) {
        // 逆辺を張ったグラフを作成
        for (long long v = 0; v < n; v++) {
            for (auto nv : G[v])
                rG[nv].push_back(v);
        }

        topological_sort();
		search_components();
		rebuild();
    }

	size_t size() const { return component_count; }
	/**
	 * @brief 強連結成分の番号を取得する
	 * @param v 頂点の番号
	 */
	long long get_component(long long v) const {
		assert(0 <= v && v < n);
		return component[v];
	}
	/**
	 * @brief 強連結成分のサイズを取得する
	 * @param component 強連結成分の番号
	 */
	long long get_component_size(long long component) const {
		assert(0 <= component && component < size());
		return components_size[component];
	}

	/**
	 * @brief 強連結成分のグラフを取得する
	 * @remark トポロジカル順に並んでいる
	 * @param component 強連結成分の番号
	 */
	vector<long long>& operator[](long long component) {
		assert(0 <= component && component < size());
		return rebuildedG[component];
	}
	// 暗黙的なvector<vector<long long>>への変換
	operator vector<vector<long long>>() const { return rebuildedG; }

	/**
	* @brief 2頂点が同じ強連結成分に属するかを判定する
	*/
    bool is_same(long long u, long long v) { return component[u] == component[v]; }
};

int main() {
    ll n;
    cin >> n;
    vvll g(n, vll());
    rep(i, n) {
        int a;
        cin >> a;
        a--;
        g[i].push_back(a);
    }

    SCC scc(g);
	vvll rebuildedGinv = inverseGraph((vvll)scc);

    ll ans = 0;
    vector<bool> seen(scc.size(), false);
    auto dfs = [&](auto self, int c, int sum) -> void {
        seen[c] = true;
        ans += scc.get_component_size(c) * sum;
        ans += scc.get_component_size(c) * scc.get_component_size(c);
        sum += scc.get_component_size(c);
        for (auto c : rebuildedGinv[c]) {
            if (!seen[c]) self(self, c, sum);
        }
    };
    for (ll i = scc.size() - 1; i >= 0; i--) {
        if (!seen[i]) dfs(dfs, i, 0);
    }

    cout << ans << endl;

    return 0;
}
