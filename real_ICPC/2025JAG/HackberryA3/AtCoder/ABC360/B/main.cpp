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

// Graph /////////////////////////////////////////////////////////
template <class T> struct Edge
{
    int from;
    int to;
    T val;

    Edge() : from(-1), to(-1), val(T()) {}
    Edge(const int &i) : from(-1), to(i), val(T()) {}
    Edge(int from, int to) : from(from), to(to), val(T()) {}
    Edge(int from, int to, T val) : from(from), to(to), val(val) {}
    bool operator==(const Edge &e) const {
        return from == e.from && to == e.to && val == e.val;
    }
    bool operator!=(const Edge &e) const {
        return from != e.from || to != e.to || val != e.val;
    }

    operator int() const { return to; }

    friend ostream &operator<<(ostream &os, const Edge &e) {
        os << e.from << " -> " << e.to << " : " << e.val;
        return os;
    }
};
template <class T> using Graph = vector<vector<Edge<T>>>;
//////////////////////////////////////////////////////////////////

// Math //////////////////////////////////////////////////////////
/**
 * @brief 拡張ユークリッドの互除法
 */
ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll d = ext_gcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
/**
 * @brief 負に対応した mod
 */
inline ll mmod(ll a, ll mod) {
    return (a % mod + mod) % mod;
}

ll pow(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
ll pow(ll a, ll b, ll mod) {
    if (b < 0) return pow(a, mod - 1 + b, mod);
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
/**
 * @brief 法がmodのときのaの逆元を求める
 * @remark aとmodが互いに素である必要がある
 */
ll inv(ll a, ll mod) {
    ll x, y;
    ext_gcd(a, mod, x, y);
    return mmod(x, mod);
}

ll nCrDP[67][67];
ll nCr(ll n, ll r) {
    assert(n < 67 && r < 67);
    assert(n >= r);
    assert(n >= 0 && r >= 0);
    if (nCrDP[n][r] != 0) return nCrDP[n][r];
    if (r == 0 || n == r) return 1;
    return nCrDP[n][r] = nCr(n - 1, r - 1) + nCr(n - 1, r);
}
ll nHr(ll n, ll r) {
    return nCr(n + r - 1, r);
}

vector<ll> fact;
void calc_fact(ll size) {
    assert(size <= 20);
    fact = vector<ll>(size + 1, 0);
    fact[0] = 1;
    for (int i = 0; i < size; ++i)
        fact[i + 1] = fact[i] * (i + 1);
}
unordered_map<ll, vector<ll>> modfact, modinvfact;
void calc_fact(ll size, ll mod) {
    modfact[mod] = vector<ll>(size + 1, 0);
    modinvfact[mod] = vector<ll>(size + 1, 0);
    modfact[mod][0] = 1;
    for (int i = 0; i < size; ++i)
        modfact[mod][i + 1] = modfact[mod][i] * (i + 1) % mod;
    modinvfact[mod][size] = inv(modfact[mod][size], mod);
    for (int i = size - 1; i >= 0; --i)
        modinvfact[mod][i] = modinvfact[mod][i + 1] * (i + 1) % mod;
}
ll nCr(ll n, ll r, ll mod) {
    assert(n >= r);
    assert(n >= 0 && r >= 0);
    if (modfact.count(mod) == 0 || modfact[mod].size() <= max(n, r)) {
        const ll size = max(500000LL, max(n, r));
        calc_fact(size, mod);
    }
    return modfact[mod][n] * modinvfact[mod][r] % mod * modinvfact[mod][n - r] %
           mod;
}
ll nHr(ll n, ll r, ll mod) {
    return nCr(n + r - 1, r, mod);
}
//////////////////////////////////////////////////////////////////

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
    string s, t;
    cin >> s >> t;

    loop(i, 1, s.size() - 1) {
        vector<string> split;
        ll pos = 0;
        while (pos < s.size()) {
            ll leftSize = min(i, (int)s.size() - pos);
            split.push_back(s.substr(pos, leftSize));
            pos += leftSize;
        }

        loop(j, 1, i) {
			string tmp = "";
			for (auto &str : split) {
				if (str.size() < j) continue;
				tmp += str[j - 1];
			}

            if (tmp == t) {
                cout << "Yes" << endl;
                return 0;
            }
        }
    }

    cout << "No" << endl;

    return 0;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    return solve();
}
