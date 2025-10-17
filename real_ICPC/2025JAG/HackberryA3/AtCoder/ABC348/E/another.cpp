// 全方位木DP
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
    for (int i = 0; i < v.size(); ++i)
        is >> v[i];
    return is;
}
template <typename T> istream &operator>>(istream &is, vector<vector<T>> &vv) {
    assert(vv.size() > 0);
    for (int i = 0; i < vv.size(); ++i)
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

struct DP
{
    ll dp;
    ll sum;

    DP(ll dp = 0, ll sum = 0) : dp(dp), sum(sum) {}

    // 2つのDPをマージ(結合則が成り立つ必要がある)
    DP operator+(const DP &rhs) const { return DP(dp + rhs.dp, sum + rhs.sum); }
    DP operator-(const DP &rhs) const { return DP(dp - rhs.dp, sum - rhs.sum); }
    // 親に辿ったときの値の更新
    DP up() const { return DP(dp + sum, sum); }
};

int solve() {
    ll n;
    cin >> n;
    vvll g(n);
    rep(i, n - 1) {
        ll a, b;
        cin >> a >> b;
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
	vll c(n);
	cin >> c;

    vector<DP> dp(n);

    auto dfs = [&](auto dfs, ll v, ll p) -> void {
		dp[v] = DP(0, c[v]);
		for (ll to : g[v]) {
            if (to == p) continue;
            dfs(dfs, to, v);
			dp[v] = dp[v] + dp[to].up();
        }
    };
	dfs(dfs, 0, -1);

	auto bfs = [&](auto bfs, ll v, ll p) -> void {
		for (ll to : g[v]) {
			if (to == p) continue;
			DP d = dp[v] - dp[to].up();
			dp[to] = dp[to] + d.up();
			bfs(bfs, to, v);
		}
	};
	bfs(bfs, 0, -1);

	ll min_ans = LLONG_MAX;
	rep(i, n) chmin(min_ans, dp[i].dp);
	cout << min_ans << endl;

    return 0;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    return solve();
}
