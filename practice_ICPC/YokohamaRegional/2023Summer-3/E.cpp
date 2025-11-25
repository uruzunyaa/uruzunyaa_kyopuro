#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PLL = pair<ll, ll>;
using PPLL = pair<ll, PLL>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i,m, n) for (ll i = m; i <= n; ++i)
const ll mod = 998244353;
const ll INF = 1LL << 60;

struct mint
{
    private:
    ll n;
    ll mod;

    public:
    static ll default_mod;

    mint() : n(0), mod(default_mod == 0 ? 998244353 : default_mod) {}
    mint(const mint &m) {
        n = m.n;
        mod = m.mod;
    }
    mint(ll n, ll mod = default_mod) {
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
        auto ext_gcd = [&](auto f, ll a, ll b, ll &x, ll &y) -> ll {
            if (b == 0) {
                x = 1;
                y = 0;
                return a;
            }
            ll d = f(f, b, a % b, y, x);
            y -= a / b * x;
            return d;
        };

        ll x, y;
        ext_gcd(ext_gcd, n, mod, x, y);
        return mint((x % mod + mod) % mod, mod);
    }

    mint pow(ll exp) const {
        bool inverse = exp < 0;
        if (inverse) exp = -exp;

        ll a = n;
        ll res = 1;
        while(exp > 0) {
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

    mint operator+() const {return *this; }
    mint operator-() const {return 0 - *this; }

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


    friend ostream &operator<<(ostream &os, const mint &m) {
        os << m.n;
        return os;
    }
};

ll mint::default_mod = 0;

ll power_mod(ll n, ll k){
    ll result = 1;
    while (k > 0){
        if ((k & 1) == 1) result = (result * n) % mod;
        n = n * n % mod;
        k >>= 1;
    }
    return result;
}

vector<ll> fact = {1};
vector<ll> factinv = {1};

ll ncrmd(ll n, ll r){
    while(fact.size() <= n){
        ll i = fact.size();
        fact.push_back((fact[i - 1] * i) % mod);
        factinv.push_back(power_mod(fact[i], mod - 2));
    }
    ll ans = fact[n];
    ans *= factinv[r];
    ans %= mod;
    ans *= factinv[n - r];
    ans %= mod;
    return ans;
}

int main() {
	ll n; cin >> n;
    vector<ll> a(n);
	ll sum=0;
    rep(i, n) cin >> a[i],sum+=a[i];

    vector<ll> lsum(n + 1, 0), rsum(n + 1, 0);
    rep(i, n) {
        lsum[i + 1] = a[i] + lsum[i];
        rsum[n - i - 1] = a[n - i - 1] + rsum[n - i];
    }

	vector<mint> lmul(n + 1, 1), rmul(n + 1, 1);
	rep(i, n) {
        lmul[i + 1] = ((mint)a[i] / lsum[i+1])*lmul[i];
		rmul[n - i - 1] = ((mint)a[n-i-1] / rsum[n-i-1])*rmul[n-i];
    }

	mint ans=1;
	rep(i,n){
		mint tmp=((mint)a[i]/sum)*lmul[i]*rmul[i+1];
		ans-=tmp;
	}
	cout<<ans<<endl;
    
    return 0;
}