#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define mod 998244353LL

// a^e mod MOD（MOD はテンプレ引数）
template<ll MOD>
inline ll pow_mod_ll(ll a, ll e){
    a %= MOD;
    if (a < 0) a += MOD;
    ll r = 1 % MOD;
    while (e > 0){
        if (e & 1) r = (__int128)r * a % MOD;
        a = (__int128)a * a % MOD;
        e >>= 1;
    }
    return r;
}

// 拡張 Euclid での逆元
inline ll inv_mod_any(ll a, ll md){
    ll b = md, u = 1, v = 0;
    while (b){
        ll t = a / b;
        a -= t * b; swap(a, b);
        u -= t * v; swap(u, v);
    }
    if (u < 0) u += md;
    return u;
}

// safe_mod (ACL と互換な動き)
inline long long safe_mod_ll(long long x, long long m){
    x %= m;
    if (x < 0) x += m;
    return x;
}

// in-place NTT for given MOD, primitive root G
template<ll MOD, int G>
void ntt_mod(vector<ll> &a, bool invert){
    int n = (int)a.size();
    if (!n) return;

    // bit-reverse
    for (int i = 1, j = 0; i < n; i++){
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1){
        ll wlen = pow_mod_ll<MOD>(G, (MOD - 1) / len);
        if (invert){
            wlen = pow_mod_ll<MOD>(wlen, MOD - 2);
        }
        for (int i = 0; i < n; i += len){
            ll w = 1;
            int half = len >> 1;
            for (int j = 0; j < half; j++){
                ll u = a[i + j];
                ll v = (__int128)a[i + j + half] * w % MOD;
                ll x = u + v;
                if (x >= MOD) x -= MOD;
                ll y = u - v;
                if (y < 0) y += MOD;
                a[i + j]        = x;
                a[i + j + half] = y;
                w = (__int128)w * wlen % MOD;
            }
        }
    }

    if (invert){
        ll inv_n = pow_mod_ll<MOD>(n, MOD - 2);
        for (int i = 0; i < n; i++){
            a[i] = (__int128)a[i] * inv_n % MOD;
        }
    }
}

// 1つの素数 MOD での畳み込み
template<ll MOD, int G>
vector<ll> conv_mod(const vector<ll> &a, const vector<ll> &b){
    int n = (int)a.size(), m = (int)b.size();
    if (!n || !m) return {};
    if (min(n, m) <= 60){
        vector<ll> c(n + m - 1);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                ll x = (a[i] % MOD + MOD) % MOD;
                ll y = (b[j] % MOD + MOD) % MOD;
                c[i + j] = (c[i + j] + (__int128)x * y) % MOD;
            }
        }
        return c;
    }

    int sz = 1;
    while (sz < n + m - 1) sz <<= 1;
    vector<ll> fa(sz), fb(sz);
    for (int i = 0; i < n; i++) fa[i] = (a[i] % MOD + MOD) % MOD;
    for (int i = 0; i < m; i++) fb[i] = (b[i] % MOD + MOD) % MOD;

    ntt_mod<MOD,G>(fa, false);
    ntt_mod<MOD,G>(fb, false);
    for (int i = 0; i < sz; i++){
        fa[i] = (__int128)fa[i] * fb[i] % MOD;
    }
    ntt_mod<MOD,G>(fa, true);
    fa.resize(n + m - 1);
    return fa;
}

// --------- 公開: convolution_ll (ACL の CRT 部分をほぼそのまま) ---------

inline vector<ll> convolution_ll(const vector<ll> &a, const vector<ll> &b){
    int n = (int)a.size(), m = (int)b.size();
    if (!n || !m) return {};

    // 3つの NTT-friendly 素数
    static constexpr unsigned long long MOD1 = 754974721;  // g = 11
    static constexpr unsigned long long MOD2 = 167772161;  // g = 3
    static constexpr unsigned long long MOD3 = 469762049;  // g = 3
    static constexpr unsigned long long M2M3 = MOD2 * MOD3;
    static constexpr unsigned long long M1M3 = MOD1 * MOD3;
    static constexpr unsigned long long M1M2 = MOD1 * MOD2;
    static constexpr unsigned long long M123 = MOD1 * MOD2 * MOD3;

    static const unsigned long long i1 =
        (unsigned long long)inv_mod_any((long long)(M2M3 % MOD1), (long long)MOD1);
    static const unsigned long long i2 =
        (unsigned long long)inv_mod_any((long long)(M1M3 % MOD2), (long long)MOD2);
    static const unsigned long long i3 =
        (unsigned long long)inv_mod_any((long long)(M1M2 % MOD3), (long long)MOD3);

    // 各 mod で畳み込み
    auto c1 = conv_mod<(ll)MOD1, 11>(a, b);
    auto c2 = conv_mod<(ll)MOD2,  3>(a, b);
    auto c3 = conv_mod<(ll)MOD3,  3>(a, b);

    vector<ll> c(n + m - 1);
    for (int i = 0; i < n + m - 1; i++){
        unsigned long long x = 0;
        x += (c1[i] * i1) % MOD1 * M2M3;
        x += (c2[i] * i2) % MOD2 * M1M3;
        x += (c3[i] * i3) % MOD3 * M1M2;

        long long diff =
            (long long)c1[i] - safe_mod_ll((long long)x, (long long)MOD1);
        if (diff < 0) diff += MOD1;

        static constexpr unsigned long long offset[5] = {
            0, 0, M123, 2 * M123, 3 * M123
        };
        x -= offset[diff % 5];
        c[i] = (long long)x;
    }
    return c;
}

//メイン
int main(){
	return 0;
}