#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
template <typename T>
using v = vector<T>;
template <typename T>
using vv = v<v<T>>;
using vll = vector<ll>;
using vvll = vector<vll>;
using P = pair<int, int>;
using PP = pair<int, P>;
using PLL = pair<ll, ll>;
using PPLL = pair<ll, PLL>;
#define rep(i, n) for(ll i = 0; i < (ll)n; ++i)
#define rrep(i, n) for(ll i = n - 1; i >= 0; --i)
#define loop(i, a, b) for(ll i = a; i <= b; ++i)
#define all(v) v.begin(), v.end()
#define nC2(n) n * (n - 1) / 2
constexpr ll INF = 1001001001001001001LL;
constexpr int INF32 = 2002002002;
constexpr ll MOD = 998244353;
constexpr ll MOD107 = 1000000007;

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





int solve() {
	ll n, m, q; 
	cin >> n >> m >> q;
	vvll d(n, vll(n, INF));
	vector<PPLL> edges;
	rep(i, m) {
		ll a, b, c; 
		cin >> a >> b >> c;
		a--; b--;
		edges.emplace_back(c, PLL(a, b));
	}
	
	unordered_set<ll> qi;
	vector<PPLL> queries;
	rep(i, q) {
		ll t; cin >> t;
		if (t == 1) {
			ll x; cin >> x;
			x--;
			qi.insert(x);
			queries.emplace_back(1, PLL(x, -1));
		}
		else {
			ll x, y; cin >> x >> y;
			x--; y--;
			queries.emplace_back(2, PLL(x, y));
		}
	}

	rep(i, n) {
		d[i][i] = 0;
	}
	rep(i, m) {
		if (qi.count(i)) continue;
		chmin(d[edges[i].second.first][edges[i].second.second], edges[i].first);
		chmin(d[edges[i].second.second][edges[i].second.first], edges[i].first);
	}

	for (int k = 0; k < n; k++){ // 経由する頂点
		for (int i = 0; i < n; i++) { // 始点
			for (int j = 0; j < n; j++) { // 終点
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
			}
		}
	}

	reverse(all(queries));

	vll ans;
	for (const auto& q : queries) {
		if (q.first == 1) {
			ll x = q.second.first;
			ll from = edges[x].second.first;
			ll to = edges[x].second.second;
			ll c = edges[x].first;
			chmin(d[from][to], c);
			chmin(d[to][from], c);
			rep(i, n) rep(j, n) {
				d[i][j] = min(d[i][j], d[i][from] + c + d[to][j]);
				d[i][j] = min(d[i][j], d[i][to] + c + d[from][j]);
			}
		}
		else if (q.first == 2) {
			ll x = q.second.first;
			ll y = q.second.second;
			if (d[x][y] == INF) {
				ans.push_back(-1);
			} else {
				ans.push_back(d[x][y]);
			}
		}
	}

	reverse(all(ans));
	for (const auto& a : ans) {
		cout << a << "\n";
	}

	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	return solve();
}
