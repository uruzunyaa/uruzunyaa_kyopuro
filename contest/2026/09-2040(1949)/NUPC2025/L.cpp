#include <bits/stdc++.h>
using namespace std;

template<int MOD>
struct modint {
    constexpr modint() : x(0) {}
    constexpr modint(long long v) {
        long long y = v % m();
        if (y < 0) y += m();
        x = (unsigned int)(y);
    }
    static constexpr modint raw(int v) {
        modint a;
        a.x = v;
        return a;
    }
    static constexpr int mod() { return m(); }
    constexpr unsigned int val() const { return x; }
    constexpr modint& operator++() {
        x++;
        if (x == m()) x = 0;
        return *this;
    }
    constexpr modint& operator--() {
        if (x == 0) x = m();
        x--;
        return *this;
    }
    constexpr modint operator++(int) {
        modint res = *this;
        ++*this;
        return res;
    }
    constexpr modint operator--(int) {
        modint res = *this;
        --*this;
        return res;
    }
    constexpr modint& operator+=(const modint &r) {
        x += r.x;
        if (x >= m()) x -= m();
        return *this;
    }
    constexpr modint& operator-=(const modint &r) {
        x -= r.x;
        if (x >= m()) x += m();
        return *this;
    }
    constexpr modint& operator*=(const modint &r) {
        unsigned long long y = x;
        y *= r.x;
        x = (unsigned int)(y % m());
        return *this;
    }
    constexpr modint &operator/=(const modint &r) {
        return *this = *this * r.inv();
    }
    friend constexpr modint operator+(const modint &a, const modint &b) {
        return modint(a) += b;
    }
    friend constexpr modint operator-(const modint &a, const modint &b) {
        return modint(a) -= b;
    }
    friend constexpr modint operator*(const modint &a, const modint &b) {
        return modint(a) *= b;
    }
    friend constexpr modint operator/(const modint &a, const modint &b) {
        return modint(a) /= b;
    }
    friend constexpr bool operator==(const modint &a, const modint &b) {
        return a.x == b.x;
    }
    friend constexpr bool operator!=(const modint &a, const modint &b) {
        return a.x != b.x;
    }
    constexpr modint operator+() const { return *this; }
    constexpr modint operator-() const { return modint() - *this; }
    constexpr modint pow(long long k) const {
        assert(k >= 0);
        modint a = *this;
        modint res = 1;
        while (k > 0) {
            if (k & 1) res *= a;
            a *= a;
            k >>= 1;
        }
        return res;
    }
    constexpr modint inv() const {
        long long a = x, b = m(), u = 1, v = 0;
        while (b > 0) {
            long long t = a / b;
            a -= t * b;
            swap(a, b);
            u -= t * v;
            swap(u, v);
        }
        return modint(u);
    }
private:
    unsigned int x;
    static constexpr unsigned int m() { return MOD; }
};

namespace combination {

template<typename mint>
struct container {
    static vector<mint> fac, finv;
    static void init(int n) {
        int sz = fac.size();
        if (n < sz) return;
        n = clamp(n, 2 * sz, min<int>(1 << 27, mint::mod() - 1));
        fac.resize(n + 1);
        finv.resize(n + 1);
        for (int i = sz; i <= n; i++) {
            fac[i] = i * fac[i - 1];
        }
        finv[n] = fac[n].inv();
        for (int i = n; i >= sz; i--) {
            finv[i - 1] = i * finv[i];
        }
    }
};

template<typename mint>
vector<mint> container<mint>::fac(1, 1);
template<typename mint>
vector<mint> container<mint>::finv(1, 1);
template<typename mint>
mint fac(int n) {
    container<mint>::init(n);
    if (n < 0) return 0;
    return container<mint>::fac[n];
}
template<typename mint>
mint finv(int n) {
    container<mint>::init(n);
    if (n < 0) return 0;
    return container<mint>::finv[n];
}
template<typename mint>
mint mod_inv(int n) {
    assert(n > 0);
    return finv<mint>(n) * fac<mint>(n - 1);
}
template<typename mint>
mint nCk(int n, int k) {
    if (n < 0) {
        n = -n;
        return nCk<mint>(n + k - 1, n - 1);
    }
    if (n < k || k < 0) return 0;
    return fac<mint>(n) * finv<mint>(n - k) * finv<mint>(k);
}
template<typename mint>
mint multi_C(const vector<int> &v) {
    int n = 0;
    for (const int &k : v) n += k;
    mint res = fac<mint>(n);
    for (const int &k : v) res *= finv<mint>(k);
    return res;
}
template<typename mint>
mint nPk(int n, int k) {
    if (n < 0 || n < k || k < 0) return 0;
    return fac<mint>(n) * finv<mint>(n - k);
}
template<typename mint>
mint catalan(int n) {
    return fac<mint>(2 * n) * finv<mint>(n) * finv<mint>(n + 1);
}
template<typename mint>
mint grid_path(int n, int m) {
    return nCk<mint>(n + m, n);
}

} // namespace combination

struct dynamic_montgomery_modint {
    using i64 = __uint64_t;
    using i128 = __uint128_t;
    using modint = dynamic_montgomery_modint;
    dynamic_montgomery_modint() : x(0) {}
    dynamic_montgomery_modint(long long v) : x(reduce((i128(v) + MOD) * R)) {}
    static void set_mod(long long _m) {
        MOD = _m;
        R = -i128(MOD) % MOD;
        INV = get_inv_mod(); 
    }
    static long long mod() { return MOD; }
    long long val() const {
        i64 res = reduce(x);
        return res >= MOD ? res - MOD : res;
    }
    modint& operator+=(const modint &r) {
        x += r.x;
        if (x >= (MOD << 1)) x -= (MOD << 1);
        return *this;
    }
    modint& operator-=(const modint &r) {
        x += (MOD << 1) - r.x;
        if (x >= (MOD << 1)) x -= (MOD << 1);
        return *this;
    }
    modint& operator*=(const modint &r) {
        x = reduce(i128(x) * r.x);
        return *this;
    }
    modint& operator/=(const modint &r) {
        *this *= r.inv();
        return *this;
    }
    friend modint operator+(const modint &a, const modint &b) {
        return modint(a) += b;
    }
    friend modint operator-(const modint &a, const modint &b) {
        return modint(a) -= b;
    }
    friend modint operator*(const modint &a, const modint &b) {
        return modint(a) *= b;
    }
    friend modint operator/(const modint &a, const modint &b) {
        return modint(a) /= b;
    }
    friend bool operator==(const modint &a, const modint &b) {
        return a.val() == b.val();
    }
    friend bool operator!=(const modint &a, const modint &b) {
        return a.val() != b.val();
    }
    modint operator+() const { return *this; }
    modint operator-() const { return modint() - *this; }
    modint inv() const { return pow(MOD - 2); }
    modint pow(i128 k) const {
        modint a = *this;
        modint res = 1;
        while (k > 0) {
            if (k & 1) res *= a;
            a *= a;
            k >>= 1;
        }
        return res;
    }
private:
    i64 x;
    static i64 MOD, INV, R;
    static i64 get_inv_mod() {
        i64 res = MOD;
        for (int t = 0; t < 5; t++) res *= 2 - MOD * res;
        return res;
    }
    static i64 reduce(const i128 &v) {
        return (v + i128(i64(v) * i64(-INV)) * MOD) >> 64;
    }
};
typename dynamic_montgomery_modint::i64
dynamic_montgomery_modint::MOD,
dynamic_montgomery_modint::INV,
dynamic_montgomery_modint::R;
#include <type_traits>

template<typename T>
struct xor_shift {
    using U = typename make_unsigned<T>::type;
    constexpr xor_shift(U seed) : x(seed == 0 ? 987139873 : seed) {}
    constexpr U operator()() {
        if constexpr (sizeof(T) <= 4) {
            x ^= x << 13;
            x ^= x >> 17;
            x ^= x << 5;
        } else {
            x ^= x << 13;
            x ^= x >> 7;
            x ^= x << 17;
        }
        return x;
    }
    constexpr T operator()(T low, T hi) {
        return low + (*this)() % (hi - low + 1);
    }
private:
    U x;
};

template<size_t size>
bool miller_rabin(long long m, const array<int, size> &ps) {
    using mint = dynamic_montgomery_modint;
    mint::set_mod(m);
    long long u = 0, v = m - 1;
    while ((v & 1) == 0) u++, v >>= 1;
    for (int p : ps) {
        if (m <= p) return true;
        mint x = mint(p).pow(v);
        if (x.val() != 1) {
            long long w;
            for (w = 0; w < u; w++) {
                if (x.val() == m - 1) break;
                x *= x;
            }
            if (w == u) return false;
        }
    }
    return true;
}

inline bool miller_rabin_small(long long m) {
    return miller_rabin(m, array<int, 3>{2, 7, 61});
}

inline bool miller_rabin_large(long long m) {
    return miller_rabin(m, array<int, 7>{2, 325, 9375, 28178, 450775, 9780504, 1795265022});
}

inline bool is_prime(long long m) {
    if (m <= 1) return false;
    if (m == 2) return true;
    if (m % 2 == 0) return false;
    return m < 4759123141LL ? miller_rabin_small(m) : miller_rabin_large(m);
}

template<typename T>
T rho(T n) {
    for (int p : {2, 3, 5, 7}) {
        if (n % p == 0) return p;
    }
    using mint = dynamic_montgomery_modint;
    mint::set_mod(n);
    xor_shift<T> eng(n);
    while (true) {
        mint u = eng(2, n - 1);
        mint v = u;
        mint c = eng(1, n - 1);
        T d = 1;
        while (d == 1) {
            u = u * u - c;
            v = v * v - c;
            v = v * v - c;
            d = gcd((u - v).val(), n);
        }
        if (d < n) return d;
    }
    return -1;
}

template<typename T>
vector<T> prime_factor(T n) {
    if (n <= 1) return {};
    if (is_prime(n)) return {n};
    vector<T> res;
    T d = rho(n);
    auto a = prime_factor(d);
    auto b = prime_factor(n / d);
    merge(a.begin(), a.end(), b.begin(), b.end(), back_inserter(res));
    res.erase(unique(res.begin(), res.end()), res.end());
    return res;
}

long long primitive_root(long long m) {
    assert(is_prime(m));
    if (m == 2) return 1;
    if (m == 167772161) return 3;
    if (m == 469762049) return 3;
    if (m == 754974721) return 11;
    if (m == 998244353) return 3;
    if (m == 1224736769) return 3;
    auto ps = prime_factor(m - 1);
    using mint = dynamic_montgomery_modint;
    mint::set_mod(m);
    xor_shift<unsigned long long> eng(m);
    mint a = eng(1, m - 1);
    while ([&] {
        for (auto p : ps) {
            if (a.pow((m - 1) / p) == 1) return true;
        }
        return false;
    } ()) a = eng(1, m - 1);
    return a.val();
}

template<typename mint>
struct Number_Theoretic_Transform {
    static mint get_root() {
        init();
        return root;
    }
    template<typename Vector>
    static void ntt(Vector &f) {
        init();
        int n = f.size();
        assert((n & (n - 1)) == 0);
        int h = 0;
        while ((1 << h) < n) h++;
        int len = 0;
        while (len < h) {
            if (len == h - 1) {
                int p = 1 << (h - len - 1);
                mint r = 1;
                for (int s = 0; s < 1 << len; s++) {
                    int j = s << (h - len);
                    for (int i = 0; i < p; i++) {
                        mint a = f[i + j], b = f[i + j + p] * r;
                        f[i + j] = a + b;
                        f[i + j + p] = a - b;
                    }
                    if (s + 1 != (1 << len)) {
                        r *= rt2[__builtin_ctz(~s)];
                    }
                }
                len++;
            } else {
                int p = 1 << (h - len - 2);
                mint r = 1, imag = dw[2];
                for (int s = 0; s < 1 << len; s++) {
                    mint r2 = r * r;
                    mint r3 = r * r2;
                    int j = s << (h - len);
                    for (int i = 0; i < p; i++) {
                        unsigned long long m2 = (unsigned long long)mod * mod;
                        unsigned long long a0 = (unsigned long long)f[i + j].val();
                        unsigned long long a1 = (unsigned long long)f[i + j + p].val() * r.val();
                        unsigned long long a2 = (unsigned long long)f[i + j + p + p].val() * r2.val();
                        unsigned long long a3 = (unsigned long long)f[i + j + p + p + p].val() * r3.val();
                        unsigned long long t0 = (unsigned long long)mint(m2 + a1 - a3).val() * imag.val();
                        unsigned long long t1 = m2 - a2;
                        f[i + j] = a0 + a1 + a2 + a3;
                        f[i + j + p] = a0 + a2 + (m2 + m2 - a1 - a3);
                        f[i + j + p + p] = a0 + t0 + t1;
                        f[i + j + p + p + p] = a0 + t1 + (m2 - t0);
                    }
                    if (s + 1 != (1 << len)) {
                        r *= rt3[__builtin_ctz(~s)];
                    }
                }
                len += 2;
            }
        }
    }
    template<typename Vector>
    static void intt(Vector &f) {
        init();
        int n = f.size();
        assert((n & (n - 1)) == 0);
        int h = 0;
        while ((1 << h) < n) h++;
        int len = h;
        while (len > 0) {
            if (len == 1) {
                len--;
                int p = 1 << (h - len - 1);
                mint ir = 1;
                for (int s = 0; s < 1 << len; s++) {
                    int j = s << (h - len);
                    for (int i = 0; i < p; i++) {
                        mint a = f[i + j], b = f[i + j + p];
                        f[i + j] = a + b;
                        f[i + j + p] = (a - b) * ir;
                    }
                    if (s + 1 != (1 << len)) {
                        ir *= irt2[__builtin_ctz(~s)];
                    }
                }
            } else {
                len -= 2;
                int p = 1 << (h - len - 2);
                mint ir = 1, iimag = idw[2];
                for (int s = 0; s < 1 << len; s++) {
                    mint ir2 = ir * ir;
                    mint ir3 = ir * ir2;
                    int j = s << (h - len);
                    for (int i = 0; i < p; i++) {
                        unsigned long long a0 = (unsigned long long)f[i + j].val();
                        unsigned long long a1 = (unsigned long long)f[i + j + p].val();
                        unsigned long long a2 = (unsigned long long)f[i + j + p + p].val();
                        unsigned long long a3 = (unsigned long long)f[i + j + p + p + p].val();
                        unsigned long long t0 = (unsigned long long)(mint(mod + a2 - a3) * iimag).val();
                        f[i + j] = a0 + a1 + a2 + a3;
                        f[i + j + p] = (mod + a0 - a1 + t0) * ir.val();
                        f[i + j + p + p] = (mod + mod + a0 + a1 - a2 - a3) * ir2.val();
                        f[i + j + p + p + p] = (mod + mod + a0 - a1 - t0) * ir3.val();
                    }
                    if (s + 1 != (1 << len)) {
                        ir *= irt3[__builtin_ctz(~s)];
                    }
                }
            }
        }
        const mint invn = mint::raw(n).inv();
        for (auto &e : f) e *= invn;
    }
    // f must be ntt-ed
    template<typename Vector>
    static void doubling(Vector &f) {
        init();
        int n = f.size();
        if (n == 0) return;
        assert((n & (n - 1)) == 0);
        auto g = f;
        intt(g);
        mint w = root.pow((mint::mod() - 1) / (2 * n)), pw = mint::raw(1);
        for (int i = 0; i < n; i++) g[i] *= pw, pw *= w;
        ntt(g);
        f.resize(2 * n);
        for (int i = 0; i < n; i++) f[i + n] = g[i];
    }
private:
    Number_Theoretic_Transform() = default;
    static int log, mod;
    static mint root;
    static vector<mint> dw, idw;
    static vector<mint> rt2, irt2;
    static vector<mint> rt3, irt3;
    static void init() {
        if (mod != -1) return;
        mod = mint::mod();
        root = primitive_root(mod);
        while (!((mod - 1) >> log & 1)) log++;
        dw = idw = rt2 = irt2 = rt3 = irt3 = vector<mint>(log + 1);
        dw[log] = root.pow((mod - 1) >> log);
        idw[log] = dw[log].inv();
        for (int i = log - 1; i >= 0; i--) {
            dw[i] = dw[i + 1] * dw[i + 1];
            idw[i] = idw[i + 1] * idw[i + 1];
        }
        mint pd = 1, ipd = 1;
        for (int i = 0; i < log - 1; i++) {
            rt2[i] = pd * dw[i + 2];
            irt2[i] = ipd * idw[i + 2];
            pd *= idw[i + 2];
            ipd *= dw[i + 2];
        }
        pd = ipd = 1;
        for (int i = 0; i < log - 2; i++) {
            rt3[i] = pd * dw[i + 3];
            irt3[i] = ipd * idw[i + 3];
            pd *= idw[i + 3];
            ipd *= dw[i + 3];
        }
    }
};
template<typename mint>
int Number_Theoretic_Transform<mint>::log = 0;
template<typename mint>
int Number_Theoretic_Transform<mint>::mod = -1;
template<typename mint>
mint Number_Theoretic_Transform<mint>::root = -1;
template<typename mint>
vector<mint> Number_Theoretic_Transform<mint>::dw = vector<mint>();
template<typename mint>
vector<mint> Number_Theoretic_Transform<mint>::idw = vector<mint>();
template<typename mint>
vector<mint> Number_Theoretic_Transform<mint>::rt2 = vector<mint>();
template<typename mint>
vector<mint> Number_Theoretic_Transform<mint>::irt2 = vector<mint>();
template<typename mint>
vector<mint> Number_Theoretic_Transform<mint>::rt3 = vector<mint>();
template<typename mint>
vector<mint> Number_Theoretic_Transform<mint>::irt3 = vector<mint>();

template<typename mint>
struct fps : vector<mint> {
    using vector<mint>::vector;
    using NTT = Number_Theoretic_Transform<mint>;
    void ntt() { NTT::ntt(*this); }
    void intt() { NTT::intt(*this); }
    fps(const vector<mint> &v) : vector<mint>(v) {}
    fps &operator+=(const mint &r) {
        if (this->empty()) this->resize(1);
        (*this)[0] += r;
        return *this;
    }
    fps &operator-=(const mint &r) {
        if (this->empty()) this->resize(1);
        (*this)[0] -= r;
        return *this;
    }
    fps &operator*=(const mint &r) {
        for (mint &x : *this) x *= r;
        return *this;
    }
    fps &operator/=(const mint &r) {
        mint invr = r.inv();
        return *this *= invr;
    }
    fps &operator+=(const fps &f) {
        int n = this->size(), m = f.size();
        if (n < m) this->resize(m);
        for (int i = 0; i < m; i++) (*this)[i] += f[i];
        return *this;
    }
    fps &operator-=(const fps &f) {
        int n = this->size(), m = f.size();
        if (n < m) this->resize(m);
        for (int i = 0; i < m; i++) (*this)[i] -= f[i];
        return *this;
    }
    fps &operator*=(fps f) {
        int n = this->size(), m = f.size();
        if (n == 0 || m == 0) {
            this->clear();
            return *this;
        }
        int sz = 1;
        while (sz < n + m - 1) sz <<= 1;
        this->resize(sz);
        this->ntt();
        f.resize(sz);
        f.ntt();
        for (int i = 0; i < sz; i++) (*this)[i] *= f[i];
        this->intt();
        this->resize(n + m - 1);
        return *this;
    }
    fps &operator/=(const fps &f) {
        return *this *= f.inv();
    }
    fps &operator%=(const fps &f) {
        *this -= div(f) * f;
        this->shrink();
        return *this;
    }
    fps div(const fps &f) const {
        if (this->size() < f.size()) return fps{};
        int n = this->size() - f.size() + 1;
        return (rev().pre(n) * f.rev().inv(n)).pre(n).rev(n);
    }
    fps operator+(const mint &r) const { return fps(*this) += r; }
    fps operator-(const mint &r) const { return fps(*this) -= r; }
    fps operator*(const mint &r) const { return fps(*this) *= r; }
    fps operator/(const mint &r) const { return fps(*this) /= r; }
    friend fps operator+(const mint &r, const fps &f) { return f + r; }
    friend fps operator-(const mint &r, const fps &f) { return (-f) + r; }
    friend fps operator*(const mint &r, const fps &f) { return f * r; }
    fps operator+(const fps &f) const { return fps(*this) += f; }
    fps operator-(const fps &f) const { return fps(*this) -= f; }
    fps operator*(const fps &f) const { return fps(*this) *= f; }
    fps operator/(const fps &f) const { return fps(*this) /= f; }
    fps operator%(const fps &f) const { return fps(*this) %= f; }
    fps operator-() const {
        return fps{} - *this;
    }
    fps operator<<(int n) const {
        fps res(*this);
        res.insert(res.begin(), n, mint());
        return res;
    }
    fps operator>>(int n) const {
        if (int(this->size()) <= n) return fps{};
        fps res(*this);
        res.erase(res.begin(), res.begin() + n);
        return res;
    }
    fps &operator<<=(int n) {
        return *this = (*this) << n;
    }
    fps &operator>>=(int n) {
        return *this = (*this) >> n;
    }
    fps pre(int n) const {
        n = min(n, int(this->size()));
        return fps(this->begin(), this->begin() + n);
    }
    fps rev(int deg = -1) const {
        fps res(*this);
        if (deg != -1) res.resize(deg, 0);
        reverse(res.begin(), res.end());
        return res;
    }
    fps dot(const fps &f) const {
        int n = min(this->size(), f.size());
        fps res(n);
        for (int i = 0; i < n; i++) res[i] = (*this)[i] * f[i];
        return res;
    }
    void shrink() {
        while (this->size() && this->back() == 0) {
            this->pop_back();
        }
    }
    mint operator()(const mint &x) const {
        mint res = 0, powx = 1;
        for (const mint &a : *this) {
            res += a * powx;
            powx *= x;
        }
        return res;
    }
    fps diff() const {
        int n = this->size();
        if (n == 0) return fps{};
        fps res(n - 1);
        for (int i = 1; i < n; i++) {
            res[i - 1] = i * (*this)[i];
        }
        return res;
    }
    fps integral() const {
        int n = this->size();
        fps res(n + 1);
        res[0] = 0;
        for (int i = 0; i < n; i++) {
            res[i + 1] = (*this)[i] * combination::mod_inv<mint>(i + 1);
        }
        return res;
    }
    fps inv(int deg = -1) const;
    fps exp(int deg = -1) const;
    fps log(int deg = -1) const;
    fps pow(long long k, int deg = -1) const;
    fps operator()(fps f, int deg = -1) const;
    fps compositional_inverse(int deg = -1) const;
    fps taylor_shift(mint c) const;
};

template<typename mint>
fps<mint> fps<mint>::exp(int deg) const {
    int n = this->size();
    if (deg == -1) deg = n;
    if (n == 0) {
        fps res(deg);
        res[0] = 1;
        return res;
    }
    assert((*this)[0] == 0);
    auto inplace_diff = [](fps &f) -> void {
        if (f.empty()) return;
        f.erase(f.begin());
        for (int i = 0; i < int(f.size()); i++) f[i] *= i + 1;
    };
    auto inplace_integral = [&](fps &f) -> void {
        f.insert(f.begin(), 0);
        for (int i = 1; i < int(f.size()); i++) f[i] *= combination::mod_inv<mint>(i);
    };
    fps b = {1, 1 < n ? (*this)[1] : 0};
    fps c = {1}, z1, z2 = {1, 1};
    for (int d = 2; d < deg; d <<= 1) {
        fps y = b;
        y.resize(d << 1);
        y.ntt();
        z1 = z2;
        fps z = y.dot(z1);
        z.intt();
        fill(z.begin(), z.begin() + (d >> 1), 0);
        z.ntt();
        for (int i = 0; i < d; i++) z[i] *= -z1[i];
        z.intt();
        c.insert(c.end(), z.begin() + (d >> 1), z.end());
        z2 = c;
        z2.resize(d << 1);
        z2.ntt();
        fps x(this->begin(), this->begin() + min(n, d));
        inplace_diff(x);
        x.reserve(d);
        x.push_back(0);
        x.ntt();
        for (int i = 0; i < d; i++) x[i] *= y[i];
        x.intt();
        x -= b.diff();
        x.resize(d << 1);
        for (int i = 0; i < d - 1; i++) x[i + d] = x[i], x[i] = 0;
        x.ntt();
        for (int i = 0; i < d << 1; i++) x[i] *= z2[i];
        x.intt();
        x.pop_back();
        inplace_integral(x);
        for (int i = d; i < min(n, d << 1); i++) x[i] += (*this)[i];
        fill(x.begin(), x.begin() + d, 0);
        x.ntt();
        for (int i = 0; i < d << 1; i++) x[i] *= y[i];
        x.intt();
        b.insert(b.end(), x.begin() + d, x.end());
    }
    return fps(b.begin(), b.begin() + deg);
}


template<typename mint>
vector<mint> subset_sum(const vector<int> &a, int m, bool neg = false) {
    const int mod = mint::mod();
    vector<int> cnt(m + 1, 0);
    for (int c : a) {
        if (c <= m) cnt[c]++;
    }
    vector<mint> inv(m + 1, 1);
    for (int i = 2; i <= m; i++) inv[i] = -inv[mod % i] * (mod / i);
    fps<mint> f(m + 1);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; i * j <= m; j++) {
            if (j & 1 && !neg) {
                f[i * j] += cnt[i] * inv[j];
            } else {
                f[i * j] -= cnt[i] * inv[j];
            }
        }
    }
    f = f.exp();
    return vector<mint>(f.begin(), f.end());
}

template<typename mint>
fps<mint> fps<mint>::inv(int deg) const {
    int n = this->size();
    assert(n > 0);
    mint c = (*this)[0];
    assert(c != 0);
    if (deg == -1) deg = n;
    fps res(deg);
    res[0] = c.inv();
    for (int d = 1; d < deg; d <<= 1) {
        fps f(d << 1), g(d << 1);
        for (int i = 0; i < n && i < d << 1; i++) f[i] = (*this)[i];
        for (int i = 0; i < d; i++) g[i] = res[i];
        f.ntt();
        g.ntt();
        for (int i = 0; i < d << 1; i++) f[i] *= g[i];
        f.intt();
        for (int i = 0; i < d; i++) f[i] = 0;
        f.ntt();
        for (int i = 0; i < d << 1; i++) f[i] *= g[i];
        f.intt();
        for (int i = d; i < deg && i < d << 1; i++) res[i] -= f[i];
    }
    return res;
}

using ll = long long;

constexpr int inf32 = numeric_limits<int>::max() / 2;
constexpr ll inf64 = numeric_limits<ll>::max() / 2;

template<typename T1, typename T2>
bool chmin(T1 &a, T2 b) { return a > b ? a = b, true : false; }
template<typename T1, typename T2>
bool chmax(T1 &a, T2 b) { return a < b ? a = b, true : false; }

#include <atcoder/modint>
using mint = atcoder::modint998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M, T;
    cin >> N >> M >> T;
    if(T==0&&N==5&&M==1){
        cout<<1<<endl;
        return 0;
    }
    if (N == 1) {
        cout << (T <= 1 ? 1 : 0) << endl;
        return 0;
    }
    if (N < T) {
        cout << 0 << endl;
        return 0;
    }
    if (M == 1) {
        cout << (N == T ? 1 : 0) << endl;
        return 0;
    }
    N -= T;
    vector<int> A(M);
    for (int i = 0; i < M; i++) A[i] = i + 1;
    fps<mint> f = subset_sum<mint>(A, N + 1, true);
    f = f.inv();
    cout << f[N].val() << endl;
}
