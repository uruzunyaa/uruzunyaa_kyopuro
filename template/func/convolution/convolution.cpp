#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define mod 998244353LL

// nのk乗をmodで割った余りを計算(modはdefineで定義想定)
ll power_mod(ll n, ll k){
	ll ans = 1;
	while (k > 0){
		if ((k&1) ==1)ans=(ans*n)%mod;
		n=n*n%mod;
		k >>= 1;
	}
	return ans;
}

inline void ntt_998(vector<ll> &a, bool invert){
    int n = (int)a.size();
    if (n == 0) return;

    // bit reversal
    for (int i = 1, j = 0; i < n; i++){
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }

    const ll g = 3; // primitive root for 998244353

    for (int len = 2; len <= n; len <<= 1){
        ll wlen = power_mod(g, (mod - 1) / len);
        if (invert){
            wlen = power_mod(wlen, mod - 2); // wlen^{-1}
        }
        for (int i = 0; i < n; i += len){
            ll w = 1;
            int half = len >> 1;
            for (int j = 0; j < half; j++){
                ll u = a[i + j];
                ll v = a[i + j + half] * w % mod;
                ll x = u + v;
                if (x >= mod) x -= mod;
                ll y = u - v;
                if (y < 0) y += mod;
                a[i + j]         = x;
                a[i + j + half]  = y;
                w = w * wlen % mod;
            }
        }
    }

    if (invert){
        ll inv_n = power_mod(n, mod - 2);
        for (int i = 0; i < n; i++){
            a[i] = a[i] * inv_n % mod;
        }
    }
}

// ----------------- 998244353 用 convolution -----------------

inline vector<ll> convolution(const vector<ll> &a, const vector<ll> &b){
    int n = (int)a.size(), m = (int)b.size();
    if (!n || !m) return {};

    // 小さい場合は愚直 O(nm)
    if (min(n, m) <= 60){
        vector<ll> c(n + m - 1, 0);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                ll x = (a[i] % mod + mod) % mod;
                ll y = (b[j] % mod + mod) % mod;
                c[i + j] = (c[i + j] + x * y) % mod;
            }
        }
        return c;
    }

    int sz = 1;
    while (sz < n + m - 1) sz <<= 1;
    vector<ll> fa(sz), fb(sz);
    for (int i = 0; i < n; i++){
        fa[i] = (a[i] % mod + mod) % mod;
    }
    for (int i = 0; i < m; i++){
        fb[i] = (b[i] % mod + mod) % mod;
    }

    ntt_998(fa, false);
    ntt_998(fb, false);
    for (int i = 0; i < sz; i++){
        fa[i] = fa[i] * fb[i] % mod;
    }
    ntt_998(fa, true);

    fa.resize(n + m - 1);
    return fa;
}

int main(){
	return 0;
}