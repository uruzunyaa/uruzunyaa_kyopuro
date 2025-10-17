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

struct Pos
{
    PLL start;
    PLL end;
};
int solve() {
    ll n, h, w;
    cin >> n >> h >> w;
    vector<PLL> tiles(n);
    rep(i, n) {
        cin >> tiles[i].first >> tiles[i].second;
    }

    ll FULL = 0;
    rep(i, n) FULL |= (1 << i);

    auto f = [&](auto self, vector<Pos> &stack, ll used, ll sy, ll sx) -> bool {
        while (sy < h && sx < w) {
			bool filled = false;
			for (auto &p : stack) {
				if (p.start.first <= sy && sy < p.end.first &&
					p.start.second <= sx && sx < p.end.second) {
					filled = true;
					break;
				}
			}
			if (!filled) break;

            sx++;
            if (sx == w) {
                sx = 0;
                sy++;
            }
            if (sy == h) return true;
        }
		if (used == FULL) return false;

        rep(i, n) {
            if (used & (1 << i)) continue;

            ll rotCnt = tiles[i].first == tiles[i].second ? 1 : 2;
            rep(rot, rotCnt) {
                Pos pos;
                pos.start = {sy, sx};
                if (rot == 0) {
                    pos.end = {sy + tiles[i].first, sx + tiles[i].second};
                }
                else { pos.end = {sy + tiles[i].second, sx + tiles[i].first}; }

                if (pos.end.first > h || pos.end.second > w) continue;

                bool ok = true;
                for (auto &p : stack) {
                    if (pos.start.first < p.end.first &&
                        pos.start.second < p.end.second &&
                        p.start.first < pos.end.first &&
                        p.start.second < pos.end.second) {
                        ok = false;
                        break;
                    }
                }
                if (!ok) continue;

                stack.push_back(pos);
                if (self(self, stack, used | (1 << i), sy, sx)) return true;
                stack.pop_back();
            }
        }

        return false;
    };

    vector<Pos> stack;
    cout << (f(f, stack, 0, 0, 0) ? "Yes" : "No") << endl;

    return 0;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    return solve();
}
