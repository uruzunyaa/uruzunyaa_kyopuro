// #UnionFind
// n個の数列aが与えられるので、回文にするために必要な最小操作回数を求めよ
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
const ll INF = 1001001001001001001LL;
const int INF32 = 1001001001;
const ll MOD = 998244353;

// Graph /////////////////////////////////////////////////////////
template <class T>
struct Edge {
	T from;
	T to;
	ll cost;
};
template <class T>
using Graph = vector<vector<Edge<T>>>;
//////////////////////////////////////////////////////////////////

// Math //////////////////////////////////////////////////////////
ll nCrDP[67][67];
ll nCr(ll n, ll r) {
    if (nCrDP[n][r] != 0) return nCrDP[n][r];
    if (r == 0 || n == r) return 1;
    return nCrDP[n][r] = nCr(n - 1, r - 1) + nCr(n - 1, r);
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
 * @details modが素数のときのみ有効
 * @details a^(p-1) ≡ 1 mod p -[両辺にa^(-1)を掛ける]-> a^(p-2) ≡ a^(-1) mod p
 * @param a 逆元を求めたい値
 * @param mod 法 
 * @return ll aの逆元
*/
ll inv(ll a, ll mod) {
	return pow(a, mod - 2, mod);
}
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

template <class T>
void printv(const vector<T>& v) {
	if (v.empty()) { cout << endl; return; }
	rep(i, v.size() - 1) cout << v[i] << " ";
	cout << v.back() << endl;
}
template <class T>
void printvv(const vector<vector<T>>& vv) {
	for (const vector<T>& v : vv) printv(v);
}

class UnionFind
{
  private:
    ll _size;
    vector<ll> _parent;

  public:
    UnionFind(ll size) {
        _size = size;
        _parent.resize(_size, -1);
    }

    ll root(ll x) {
        if (_parent[x] < 0) { return x; }
        else { return _parent[x] = root(_parent[x]); }
    }

    void unite(ll x, ll y) {
        x = root(x);
        y = root(y);
        if (x != y) {
            if (-_parent[x] < -_parent[y]) { swap(x, y); }
            _parent[x] += _parent[y];
            _parent[y] = x;
        }
    }

    bool isSame(ll x, ll y) { return root(x) == root(y); }

    ll size(ll x) { return -_parent[root(x)]; }

    vector<vector<ll>> groups() {
        vector<vector<ll>> member(_size);
        for (ll i = 0; i < _size; ++i) {
            member[root(i)].push_back(i);
        }

        vector<vector<ll>> result;
        for (ll i = 0; i < _size; ++i) {
            if (!member[i].empty()) { result.push_back(member[i]); }
        }

        return result;
    }
};





int solve() {
	ll n; cin >> n;
	vll a(n);
	rep(i, n) cin >> a[i];

	UnionFind uf(2 * 1e5 + 1);
	rep(i, n) uf.unite(a[i], a[n - i - 1]);

	ll ans = 0;
	for(auto group : uf.groups()) {
		ll size = group.size();
		ans += size - 1;
	}

	cout << ans << endl;

	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	return solve();
}
