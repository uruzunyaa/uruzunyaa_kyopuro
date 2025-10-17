#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define vl vector<ll>
#define rep(i, n) for (ll i = 0; i < n; ++i)
constexpr ll MOD107 = 1000000007;

template <typename T>
struct RollingHash {
private:
    vector<int64_t> pow_bases;
    vector<int64_t> hashes;

    const int64_t MASK30 = (1ULL << 30) - 1;
    const int64_t MASK31 = (1ULL << 31) - 1;

    const int64_t MASK61 = mod;


    int64_t calc_mod(int64_t x){
        int64_t xu = x >> 61;
        int64_t xd = x & MASK61;
        int64_t res = xu + xd;
        if(res >= mod) res -= mod;
        return res;
    }

    int64_t mul(int64_t a, int64_t b){
        int64_t au = a >> 31;
        int64_t ad = a & MASK31;
        int64_t bu = b >> 31;
        int64_t bd = b & MASK31;
        int64_t mid = ad * bu + au * bd;
        int64_t midu = mid >> 30;
        int64_t midd = mid & MASK30;
        return calc_mod(au * bu * 2 + midu + (midd << 31) + ad * bd);
    }

public:
    const int64_t base;
    static const int64_t mod = (1LL << 61) - 1;

    static int64_t generate_base() {
        mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
        return uniform_int_distribution<int64_t>(1, mod - 1)(rnd);
    }

    RollingHash(int64_t base) : base(base) {
        pow_bases.push_back(1);
        hashes.push_back(0);
    }
    template <typename Iterable>
    RollingHash(Iterable s, int64_t base) : RollingHash(base) {
        pow_bases.reserve(s.size() + 1);
        hashes.reserve(s.size() + 1);
        for (int i = 0; i < static_cast<int>(s.size()); ++i) {
            push_back(s[i]);
        }
    }

    void push_back(T c) {
        hashes.push_back(calc_mod(mul(hashes.back(), base) + (int64_t)c));
        if (pow_bases.size() < hashes.size()) pow_bases.push_back(mul(pow_bases.back(), base));
    }

    int64_t get(int l, int r) {
        int64_t hash = calc_mod(hashes[r] - calc_mod(mul(hashes[l], pow_bases[r - l])));
        return hash;
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll n; cin >> n;
    unordered_set<ll> hashes;
    set<ll> sizes_set;
    ll base = RollingHash<char>::generate_base();
    rep(i, n) {
        string s; cin >> s;
        RollingHash<char> rh(s, base);
        hashes.insert(rh.get(0, s.size()));
        sizes_set.insert(s.size());
    }
    vector<ll> sizes;
    for (ll size : sizes_set) {
        sizes.push_back(size);
    }

    string t; cin >> t;
    RollingHash<char> trh(t, base);
    vector<ll> dp(t.size() + 1, 0);
    dp[0] = 1;
    rep(i, t.size()) {
        for (ll& len : sizes) {
            if (t.size() < i + len) break;
            if (hashes.count(trh.get(i, i + len))) {
                dp[i + len] += dp[i];
                dp[i + len] %= MOD107;
            }
        }
    }

    cout << dp[t.size()] << endl;
}