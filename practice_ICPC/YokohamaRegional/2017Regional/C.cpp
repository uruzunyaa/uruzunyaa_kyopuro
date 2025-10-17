#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)

set<ll> enum_primes(const ll n) {
    vector<bool> is_prime(n + 1, true);
    set<ll> res;
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i <= n; ++i) {
        if (!is_prime[i]) continue;
        res.insert(i);
        for (ll j = i * i; j <= n; j += i) is_prime[j] = false;
    }
    return res;
}

int main() {
    ll l, r; cin >> l >> r;

    set<ll> primes = enum_primes(1e6);
    vector<pair<ll, ll>> prime_fact(r - l + 1, {0, 0});
    for (ll i = l; i <= r; i++) {
        prime_fact[i - l] = {i, 0};
    }

    for (ll p : primes) {
        ll a = 0, b = 1e9 / p;
        while (b - a > 1) {
            ll mid = (a + b) / 2;
            if (l <= p * mid) b = mid;
            else a = mid;
        }

        for (ll i = p * b; i <= r; i += p) {
            assert(prime_fact[i - l].first % p == 0);
            while (prime_fact[i - l].first % p == 0) {
                ++prime_fact[i - l].second;
                prime_fact[i - l].first /= p;
            }
        }
    }

    ll ans = 0;
    rep(i, prime_fact.size()) {
        if (prime_fact[i].first != 1) prime_fact[i].second++;
        if (primes.count(prime_fact[i].second)) ans++;
    }
    cout << ans << endl;
}