// ゲーム
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

int solve() {
    vvll a(3, vll(3));
    cin >> a;

    ll sumScore = 0;
    rep(i, 3) rep(j, 3) sumScore += a[i][j];

    auto dfs = [&](auto dfs, vvll &g) -> bool {
		if (g[0][0] == 0 && g[0][1] == 0 && g[0][2] == 0) return false;
		if (g[1][0] == 0 && g[1][1] == 0 && g[1][2] == 0) return false;
		if (g[2][0] == 0 && g[2][1] == 0 && g[2][2] == 0) return false;
		if (g[0][0] == 0 && g[1][0] == 0 && g[2][0] == 0) return false;
		if (g[0][1] == 0 && g[1][1] == 0 && g[2][1] == 0) return false;
		if (g[0][2] == 0 && g[1][2] == 0 && g[2][2] == 0) return false;
		if (g[0][0] == 0 && g[1][1] == 0 && g[2][2] == 0) return false;
		if (g[0][2] == 0 && g[1][1] == 0 && g[2][0] == 0) return false;

        bool filled = true;
        rep(i, 3) rep(j, 3) if (g[i][j] == -1) filled = false;
        if (filled) {
			ll score1 = 0;
			ll score2 = 0;
			rep(i, 3) rep(j, 3) {
				if (g[i][j] == 0) score1 += a[i][j];
				if (g[i][j] == 1) score2 += a[i][j];
			}
			if (score1 < score2) return true;
			else return false;
        }

		rep(i, 3) rep(j, 3) if (g[i][j] != -1) g[i][j] ^= 1;

        bool canWin = false;
		rep(y, 3) rep(x, 3) {
            if (g[y][x] != -1) continue;

            g[y][x] = 0;
            if (!dfs(dfs, g)) {
                g[y][x] = -1;
				canWin = true;
                break;
            }
            g[y][x] = -1;
        }

		rep(i, 3) rep(j, 3) if (g[i][j] != -1) g[i][j] ^= 1;

        return canWin;
    };

    vvll g(3, vll(3, -1));
    cout << (dfs(dfs, g) ? "Takahashi" : "Aoki") << endl;

    return 0;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    return solve();
}
