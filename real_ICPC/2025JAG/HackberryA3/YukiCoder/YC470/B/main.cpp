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
/**
 * @brief 法がmodのときのaの逆元を求める
 * @remark aとmodが互いに素である必要がある
 */
ll inv(ll a, ll mod) {
    ll x, y;
    ext_gcd(a, mod, x, y);
    return mmod(x, mod);
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
	bool inverse = b < 0;
	if (inverse) b = -b;
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return inverse ? inv(res, mod) : res;
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
	if (modfact.count(mod) && modfact[mod].size() - 1 > size) return;

	ll oldsize = max(0, (int)modfact[mod].size() - 1);
	modfact[mod].resize(size + 1, 1);
	modinvfact[mod].resize(size + 1, 1);

    for (int i = oldsize; i < size; ++i)
        modfact[mod][i + 1] = modfact[mod][i] * (i + 1) % mod;
    modinvfact[mod][size] = inv(modfact[mod][size], mod);
    for (int i = size - 1; i >= oldsize; --i)
        modinvfact[mod][i] = modinvfact[mod][i + 1] * (i + 1) % mod;
}
ll nCr(ll n, ll r, ll mod, ll dp_size = 500000LL) {
    assert(n >= r);
    assert(n >= 0 && r >= 0);
	calc_fact(max(n, dp_size), mod);
    return modfact[mod][n] * modinvfact[mod][r] % mod * modinvfact[mod][n - r] % mod;
}
ll nHr(ll n, ll r, ll mod, ll dp_size = 500000LL) {
    return nCr(n + r - 1, r, mod, dp_size);
}

struct mint
{
  private:
    long long n;
    long long mod;

  public:
    static long long default_mod;

	mint() : n(0), mod(default_mod == 0 ? 998244353 : default_mod) {}
    mint(const mint &m) {
        n = m.n;
        mod = m.mod;
    }
    mint(long long n, long long mod = default_mod) {
        if (default_mod == 0) {
			default_mod = mod == 0 ? 998244353 : mod;
			mod = default_mod;
		}
        assert(1 <= mod);

        this->n = (n % mod + mod) % mod;
        this->mod = mod;
    }

    mint inv() const {
        assert(gcd(n, mod) == 1);
        auto ext_gcd = [&](auto f, long long a, long long b, long long &x, long long &y) -> long long {
            if (b == 0) {
                x = 1;
                y = 0;
                return a;
            }
            long long d = f(f, b, a % b, y, x);
            y -= a / b * x;
            return d;
        };

        long long x, y;
        ext_gcd(ext_gcd, n, mod, x, y);
        return mint((x % mod + mod) % mod, mod);
    }

    mint pow(long long exp) const {
        bool inverse = exp < 0;
        if (inverse) exp = -exp;

		ll a = n;
        ll res = 1;
        while (exp > 0) {
            if (exp & 1) res = res * a % mod;
            a = a * a % mod;
            exp >>= 1;
        }
        return (inverse ? mint(res, mod).inv() : mint(res, mod));
    }

	mint &operator=(const mint &o) {
		n = o.n;
		mod = o.mod;
		return *this;
	}

	mint operator+() const { return *this; }
	mint operator-() const { return 0 - *this; }

	mint &operator++() {
		n++;
		if (n == mod) n = 0;
		return *this;
	}
	mint &operator--() {
		if (n == 0) n = mod;
		n--;
		return *this;
	}
	mint operator++(int) {
		mint res = *this;
		++*this;
		return res;
	}
	mint operator--(int) {
		mint res = *this;
		--*this;
		return res;
	}

    mint &operator+=(const mint &o) {
        assert(mod == o.mod);
        n += o.n;
        if (n >= mod) n -= mod;
        return *this;
    }
    mint &operator-=(const mint &o) {
        assert(mod == o.mod);
        n += mod - o.n;
        if (n >= mod) n -= mod;
        return *this;
    }
    mint &operator*=(const mint &o) {
        assert(mod == o.mod);
        n = n * o.n % mod;
        return *this;
    }
    mint &operator/=(const mint &o) {
        assert(mod == o.mod);
        n = n * o.inv().n % mod;
        return *this;
    }
    friend mint operator+(const mint &a, const mint &b) {
        return mint(a) += b;
    }
    friend mint operator-(const mint &a, const mint &b) {
        return mint(a) -= b;
    }
    friend mint operator*(const mint &a, const mint &b) {
        return mint(a) *= b;
    }
    friend mint operator/(const mint &a, const mint &b) {
        return mint(a) /= b;
    }

	friend bool operator==(const mint &a, const mint &b) {
		return a.n == b.n && a.mod == b.mod;
	}
	friend bool operator!=(const mint &a, const mint &b) {
		return a.n != b.n || a.mod != b.mod;
	}

    friend ostream &operator<<(ostream &os, const mint &m) {
        os << m.n;
        return os;
    }
};
long long mint::default_mod = 0;

int solve() {
	string s;
	cin >> s;

	map<ll, ll> cnt;
	for (char c : s) {
		cnt[c - '0']++;
	}

	mint ans = 1;
	ll digits = s.size();
	if (cnt.begin()->first == 0) {
		ans *= nCr(digits - 1, cnt.begin()->second, MOD);
		digits -= cnt.begin()->second;
		cnt.erase(0);
	}

	for (auto [num, c] : cnt) {
		mint comb = nCr(digits, c, MOD);
		ans *= comb;
		digits -= c;
	}

	cout << ans << "\n";

	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	return solve();
}
