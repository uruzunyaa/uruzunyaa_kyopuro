#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using P = pair<int, int>;
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)
const ll INF = 1001001001001001001LL;
const ll MOD = 998244353;

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

int main() {
  ll n;
  cin >> n;

  vll a(n);
  vll weights(n);
  rep(i, n) {
    cin >> a[i];
    ll x = a[i];
    ll w = 0;
    while (x > 0) {
      x /= 10;
      w++;
    }
    weights[i] = w;
  }

  vector<map<ll, ll>> weight_map(n);
  for (ll i = n - 2; i >= 0; --i) {
    weight_map[i] = weight_map[i + 1];
    weight_map[i][weights[i + 1]]++;
  }

  ull ans = 0;
  rep(i, n) {
    ans += (ull)a[i] * (ull)i;
	ans %= MOD;

    for (auto m : weight_map[i]) {
      ll p = 1;
      rep(j, m.first) p *= 10;
      ans += ((ull)p * (ull)a[i]) % MOD * (ull)m.second;
      ans %= MOD;
    }
  }

  cout << ans << endl;

  return 0;
}
