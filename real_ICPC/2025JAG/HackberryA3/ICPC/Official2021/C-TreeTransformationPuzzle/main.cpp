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




struct DP
{
	ll mx;
	ll mn;

    DP(ll mx = -INF, ll mn = INF) : mx(mx), mn(mn) {}

    // 2つのDPをマージ(結合則が成り立つ必要がある)
    /* DP operator+(const DP &rhs) const { return DP(dp + rhs.dp, sum + rhs.sum); }
    DP operator-(const DP &rhs) const { return DP(dp - rhs.dp, sum - rhs.sum); } */
    // 親に辿ったときの値の更新
    // DP up() const { return DP(dp + sum, sum); }
};

DP calculate(vector<DP> children, char op) {
	DP res(-INF, INF);

	vll p;
	rep(i, children.size()) {
		p.push_back(i);
	}
	do {
		rep(ismx, 1 << children.size()) {
			ll ans;
			if (ismx & (1 << 0)) ans = children[p[0]].mx;
			else ans = children[p[0]].mn;

			loop(i, 1, children.size() - 1) {
				if (ismx & (1 << i)) {
					if (op == '+') ans += children[p[i]].mx;
					else ans -= children[p[i]].mx;
				}
				else {
					if (op == '+') ans += children[p[i]].mn;
					else ans -= children[p[i]].mn;
				}
			}

			chmax(res.mx, ans);
			chmin(res.mn, ans);
		}
	}
	while (next_permutation(all(p)));
	return res;
}

int solve() {
	string s;
	cin >> s;
	if (s == "-1") return 1;

	vector<vector<DP>> dp;
	vector<bool> isNode;
	vector<char> ops;
	vvll g;
	vector<PLL> edges;
	auto parse = [&](auto self, int& i, int idx) -> pair<ll, DP> {
		dp.push_back(vector<DP>());
		isNode.push_back(true);
		ops.push_back('\0');
		g.push_back(vll());

		ll nextidx = idx + 1;
		if (s[i] == '(') {
			g[idx].push_back(nextidx);
			edges.push_back({idx, nextidx});
			i++;
			auto [id, val] = self(self, i, nextidx);
			dp[idx].push_back(val);
			nextidx = id + 1;
		}
		else {
			assert('0' <= s[i] && s[i] <= '9');
			g.push_back(vll());
			g[idx].push_back(nextidx);
			edges.push_back({idx, nextidx});
			ll v = s[i] - '0';
			dp.push_back(vector<DP>());
			isNode.push_back(false);
			ops.push_back('\0');
			dp[idx].push_back(DP(v, v));
			nextidx++;
		}

		i++;
		assert(s[i] == '+' || s[i] == '-');
		ops[idx] = s[i];
		i++;

		if (s[i] == '(') {
			g[idx].push_back(nextidx);
			edges.push_back({idx, nextidx});
			i++;
			auto [id, val] = self(self, i, nextidx);
			dp[idx].push_back(val);
			nextidx = id + 1;
		}
		else {
			assert('0' <= s[i] && s[i] <= '9');
			g.push_back(vll());
			g[idx].push_back(nextidx);
			edges.push_back({idx, nextidx});
			ll v = s[i] - '0';
			dp.push_back(vector<DP>());
			isNode.push_back(false);
			ops.push_back('\0');
			dp[idx].push_back(DP(v, v));
			nextidx++;
		}

		i++;
		assert(s[i] == '+' || s[i] == '-' || s[i] == ')');

		if (s[i] == ')') {
			goto calc;
		}

		i++;
		if (s[i] == '(') {
			g[idx].push_back(nextidx);
			edges.push_back({idx, nextidx});
			i++;
			auto [id, val] = self(self, i, nextidx);
			dp[idx].push_back(val);
			nextidx = id + 1;
		}
		else {
			assert('0' <= s[i] && s[i] <= '9');
			g.push_back(vll());
			g[idx].push_back(nextidx);
			edges.push_back({idx, nextidx});
			ll v = s[i] - '0';
			dp.push_back(vector<DP>());
			isNode.push_back(false);
			ops.push_back('\0');
			dp[idx].push_back(DP(v, v));
			nextidx++;
		}

	calc:
		DP res = calculate(dp[idx], ops[idx]);
		return {nextidx - 1, res};
	};

	int i = 0;
	parse(parse, i, 0);

	for (auto [u, v] : edges) {
		g[v].push_back(u);
		dp[v].push_back(DP());
	}

	ll ans = -INF;
    auto bfs = [&](auto bfs, ll v, ll p, DP par) -> void {
        ll deg = g[v].size();
        rep(i, deg) if (g[v][i] == p) dp[v][i] = par;

		chmax(ans, calculate(dp[v], ops[v]).mx);

        rep(i, deg) {
            if (g[v][i] == p) continue;
			if (!isNode[g[v][i]]) continue;

			vector<DP> children;
			rep(j, deg) {
				if (i == j) continue;
				children.push_back(dp[v][j]);
			}
			DP now = calculate(children, ops[v]);
            bfs(bfs, g[v][i], v, now);
        }
    };
    bfs(bfs, 0, -1, DP());

	cout << ans << "\n";

	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	while (!solve()) { }

	return 0;
}
