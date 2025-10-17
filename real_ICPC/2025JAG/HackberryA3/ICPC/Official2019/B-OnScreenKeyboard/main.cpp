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
	Edge(const int& i) : from(-1), to(i), val(T()) {} 
	Edge(int from, int to) : from(from), to(to), val(T()) {}
	Edge(int from, int to, T val) : from(from), to(to), val(val) {}
	bool operator==(const Edge &e) const { return from == e.from && to == e.to && val == e.val; }
	bool operator!=(const Edge &e) const { return from != e.from || to != e.to || val != e.val; }

	operator int() const { return to; }

	friend ostream& operator << (ostream& os, const Edge& e) {
		os << e.from << " -> " << e.to << " : " << e.val;
		return os;
	}
};
template <class T> using Graph = vector<vector<Edge<T>>>;
//////////////////////////////////////////////////////////////////

// Math //////////////////////////////////////////////////////////
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
 * @remark modが素数のときのみ有効
 * @remark aとmodが互いに素でなければいけない(割り算の代わりに使う場合は、気にしなくても大丈夫)
 * @details a^(p-1) ≡ 1 mod p -[両辺にa^(-1)を掛ける]-> a^(p-2) ≡ a^(-1) mod p
 * @param a 逆元を求めたい値
 * @param mod 法 
 * @return ll aの逆元
*/
ll inv(ll a, ll mod) {
	return pow(a, mod - 2, mod);
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

unordered_map<ll, vector<ll>> fact, invfact;
ll nCr(ll n, ll r, ll mod) {
	assert(n >= r);
	assert(n >= 0 && r >= 0);
    if (fact.count(mod) == 0 || fact[mod].size() <= max(n, r)) {
		const ll size = max(500000LL, max(n, r));
		fact[mod] = vector<ll>(size + 1, 0);
		invfact[mod] = vector<ll>(size + 1, 0);
        fact[mod][0] = 1;
        for (int i = 0; i < size; ++i) fact[mod][i + 1] = fact[mod][i] * (i + 1) % mod;
        invfact[mod][size] = inv(fact[mod][size], mod);
        for (int i = size - 1; i >= 0; --i) invfact[mod][i] = invfact[mod][i + 1] * (i + 1) % mod;
    }
    return fact[mod][n] * invfact[mod][r] % mod * invfact[mod][n - r] % mod;
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
	ll h, w; cin >> h >> w;
	if (h == 0) return 1;
	vector<vector<char>> grid(h, vector<char>(w));
	map<char, P> keymap;
	rep(y, h) {
		string r; cin >> r;
		rep(x, w) {
			grid[y][x] = r[x];
			if(r[x] != '_') {
				keymap[r[x]] = {y, x};
			}
		}
	}

	string s; cin >> s;
	char prev = grid[0][0];
	ll ans = 0;
	for (const auto next : s) {
		vector<vector<ll>> dist(h, vector<ll>(w, INF));
		queue<P> q;
		q.push(keymap[prev]);
		dist[q.front().first][q.front().second] = 0;

		while(!q.empty()) {
			auto [y, x] = q.front();
			q.pop();

			// On visit

			rep(i, 4) {
				int nx = x + dx[i];
				int ny = y + dy[i];
				if (nx < 0 || w <= nx || ny < 0 || h <= ny) continue;
				if (dist[ny][nx] != INF) continue;
				dist[ny][nx] = dist[y][x] + 1;
				q.push({ny, nx});

				// On found
			}
		}

		ans += dist[keymap[next].first][keymap[next].second] + 1;
		prev = next;
	} 

	cout << ans << endl;

	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	while (!solve()) { }

	return 0;
}
